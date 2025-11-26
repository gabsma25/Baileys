#include "Database/DatabaseManager.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cstring>
#include <cstdlib>

namespace Database {

DatabaseManager::DatabaseManager() 
    : conn(nullptr)
    , connected(false) {
}

DatabaseManager::~DatabaseManager() {
    disconnect();
}

bool DatabaseManager::connect(const std::string& host, 
                              const std::string& port,
                              const std::string& dbname,
                              const std::string& user,
                              const std::string& password) {
    std::ostringstream oss;
    oss << "host=" << host 
        << " port=" << port 
        << " dbname=" << dbname 
        << " user=" << user
        << " client_encoding=UTF8";
    
    if (!password.empty()) {
        oss << " password=" << password;
    }
    
    connection_string = oss.str();
    conn = PQconnectdb(connection_string.c_str());
    
    if (PQstatus(conn) != CONNECTION_OK) {
        lastError = PQerrorMessage(conn);
        std::cerr << "[Database] Erro ao conectar: " << lastError << std::endl;
        PQfinish(conn);
        conn = nullptr;
        connected = false;
        return false;
    }
    
    // Forçar encoding UTF-8 para o cliente
    PGresult* res = PQexec(conn, "SET CLIENT_ENCODING TO 'UTF8'");
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "[Database] Aviso: Não foi possível definir UTF-8: " << PQerrorMessage(conn) << std::endl;
    }
    PQclear(res);
    
    connected = true;
    std::cout << "[Database] Conectado ao banco: " << dbname << " (UTF-8)" << std::endl;
    return true;
}

void DatabaseManager::disconnect() {
    if (conn) {
        PQfinish(conn);
        conn = nullptr;
        std::cout << "[Database] Desconectado do banco de dados" << std::endl;
    }
    connected = false;
}

bool DatabaseManager::executeQuery(const std::string& query) {
    if (!isConnected()) {
        lastError = "Não conectado ao banco de dados";
        return false;
    }
    
    PGresult* res = PQexec(conn, query.c_str());
    ExecStatusType status = PQresultStatus(res);
    
    if (status != PGRES_COMMAND_OK && status != PGRES_TUPLES_OK) {
        lastError = PQerrorMessage(conn);
        std::cerr << "[Database] Erro na query: " << lastError << std::endl;
        PQclear(res);
        return false;
    }
    
    PQclear(res);
    return true;
}

PGresult* DatabaseManager::executeQueryWithResult(const std::string& query) {
    if (!isConnected()) {
        lastError = "Não conectado ao banco de dados";
        return nullptr;
    }
    
    PGresult* res = PQexec(conn, query.c_str());
    ExecStatusType status = PQresultStatus(res);
    
    if (status != PGRES_TUPLES_OK && status != PGRES_COMMAND_OK) {
        lastError = PQerrorMessage(conn);
        std::cerr << "[Database] Erro na query: " << lastError << std::endl;
        PQclear(res);
        return nullptr;
    }
    
    return res;
}

std::string DatabaseManager::escapeString(const std::string& str) {
    if (!conn) return str;
    
    char* escaped = new char[str.length() * 2 + 1];
    PQescapeStringConn(conn, escaped, str.c_str(), str.length(), nullptr);
    std::string result(escaped);
    delete[] escaped;
    return result;
}

Questao DatabaseManager::buildQuestaoFromResult(PGresult* res, int row) {
    Questao q;
    
    int idQuestaoCol = PQfnumber(res, "id_questao");
    int idCategoriaCol = PQfnumber(res, "id_categoria");
    int perguntaCol = PQfnumber(res, "pergunta");
    int dificuldadeCol = PQfnumber(res, "dificuldade");
    int pontosCol = PQfnumber(res, "pontos");
    
    if (idQuestaoCol >= 0) q.id_questao = atoi(PQgetvalue(res, row, idQuestaoCol));
    if (idCategoriaCol >= 0) q.id_categoria = atoi(PQgetvalue(res, row, idCategoriaCol));
    if (perguntaCol >= 0) q.pergunta = PQgetvalue(res, row, perguntaCol);
    if (dificuldadeCol >= 0) q.dificuldade = PQgetvalue(res, row, dificuldadeCol);
    if (pontosCol >= 0) q.pontos = atoi(PQgetvalue(res, row, pontosCol));
    
    int catCol = PQfnumber(res, "categoria");
    if (catCol >= 0 && !PQgetisnull(res, row, catCol)) {
        q.categoria_nome = PQgetvalue(res, row, catCol);
    }
    
    int corCol = PQfnumber(res, "cor_hex");
    if (corCol >= 0 && !PQgetisnull(res, row, corCol)) {
        q.cor_hex = PQgetvalue(res, row, corCol);
    }
    
    // Buscar alternativas
    q.alternativas = getAlternativasPorQuestao(q.id_questao);
    
    return q;
}

// ========================================
// CRUD - Questões
// ========================================

std::vector<Questao> DatabaseManager::getAllQuestoes(bool apenasAtivas) {
    std::vector<Questao> questoes;
    
    if (!connected) {
        std::cerr << "[Database] Não conectado ao banco" << std::endl;
        return questoes;
    }
    
    std::string sql = R"(
        SELECT q.*, c.nome AS categoria, c.cor_hex 
        FROM questoes q 
        INNER JOIN categorias c ON q.id_categoria = c.id_categoria
    )";
    
    if (apenasAtivas) {
        sql += " WHERE q.ativo = TRUE";
    }
    
    sql += " ORDER BY q.id_questao";
    
    PGresult* res = executeQueryWithResult(sql);
    if (!res) return questoes;
    
    int rows = PQntuples(res);
    for (int i = 0; i < rows; i++) {
        questoes.push_back(buildQuestaoFromResult(res, i));
    }
    
    PQclear(res);
    return questoes;
}

std::vector<Questao> DatabaseManager::getQuestoesPorCategoria(int id_categoria, bool apenasAtivas) {
    std::vector<Questao> questoes;
    
    if (!connected) return questoes;
    
    try {
        std::string sql = R"(
            SELECT q.*, c.nome AS categoria, c.cor_hex 
            FROM questoes q 
            INNER JOIN categorias c ON q.id_categoria = c.id_categoria
            WHERE q.id_categoria = $1
        )";
        
        if (apenasAtivas) {
            sql += " AND q.ativo = TRUE";
        }
        
        sql += " ORDER BY q.id_questao";
        
        std::string idStr = std::to_string(id_categoria);
        const char* paramValues[] = { idStr.c_str() };
        
        PGresult* res = PQexecParams(conn, sql.c_str(), 1, nullptr, paramValues, nullptr, nullptr, 0);
        
        if (PQresultStatus(res) == PGRES_TUPLES_OK) {
            int nRows = PQntuples(res);
            for (int i = 0; i < nRows; i++) {
                questoes.push_back(buildQuestaoFromResult(res, i));
            }
        }
        
        PQclear(res);
    }
    catch (const std::exception& e) {
        std::cerr << "[Database] Erro ao buscar questões por categoria: " << e.what() << std::endl;
    }
    
    return questoes;
}

std::vector<Questao> DatabaseManager::getQuestoesAleatorias(int limite, bool apenasAtivas) {
    std::vector<Questao> questoes;
    
    if (!connected) return questoes;
    
    try {
        // Usar seed baseada em timestamp com microsegundos para verdadeira aleatoriedade
        PGresult* seedRes = PQexec(conn, "SELECT setseed((extract(epoch from clock_timestamp()) - floor(extract(epoch from clock_timestamp()))))");
        PQclear(seedRes);
        
        std::string sql = R"(
            SELECT q.*, c.nome AS categoria, c.cor_hex 
            FROM questoes q 
            INNER JOIN categorias c ON q.id_categoria = c.id_categoria
        )";
        
        if (apenasAtivas) {
            sql += " WHERE q.ativo = TRUE";
        }
        
        sql += " ORDER BY RANDOM() LIMIT $1";
        
        std::string limiteStr = std::to_string(limite);
        const char* paramValues[] = { limiteStr.c_str() };
        
        PGresult* res = PQexecParams(conn, sql.c_str(), 1, nullptr, paramValues, nullptr, nullptr, 0);
        
        if (PQresultStatus(res) == PGRES_TUPLES_OK) {
            int nRows = PQntuples(res);
            for (int i = 0; i < nRows; i++) {
                questoes.push_back(buildQuestaoFromResult(res, i));
            }
        }
        
        PQclear(res);
    }
    catch (const std::exception& e) {
        std::cerr << "[Database] Erro ao buscar questões aleatórias: " << e.what() << std::endl;
    }
    
    return questoes;
}

std::vector<Questao> DatabaseManager::getQuestoesAleatoriasCategoria(int id_categoria, int limite) {
    std::vector<Questao> questoes;
    
    if (!connected) return questoes;
    
    try {
        // Usar seed baseada em timestamp com microsegundos para verdadeira aleatoriedade
        PGresult* seedRes = PQexec(conn, "SELECT setseed((extract(epoch from clock_timestamp()) - floor(extract(epoch from clock_timestamp()))))");
        PQclear(seedRes);
        
        std::string sql = R"(
            SELECT q.*, c.nome AS categoria, c.cor_hex 
            FROM questoes q 
            INNER JOIN categorias c ON q.id_categoria = c.id_categoria
            WHERE q.id_categoria = $1 AND q.ativo = TRUE
            ORDER BY RANDOM() 
            LIMIT $2
        )";
        
        const char* paramValues[2];
        std::string catStr = std::to_string(id_categoria);
        std::string limStr = std::to_string(limite);
        paramValues[0] = catStr.c_str();
        paramValues[1] = limStr.c_str();
        
        PGresult* res = PQexecParams(conn, sql.c_str(), 2, nullptr, paramValues, nullptr, nullptr, 0);
        
        if (PQresultStatus(res) == PGRES_TUPLES_OK) {
            int rows = PQntuples(res);
            for (int i = 0; i < rows; i++) {
                questoes.push_back(buildQuestaoFromResult(res, i));
            }
        } else {
            std::cerr << "[Database] Erro ao buscar questões: " << PQerrorMessage(conn) << std::endl;
        }
        
        PQclear(res);
    }
    catch (const std::exception& e) {
        std::cerr << "[Database] Erro ao buscar questões aleatórias da categoria: " << e.what() << std::endl;
    }
    
    return questoes;
}

std::optional<Questao> DatabaseManager::getQuestaoPorId(int id_questao) {
    if (!connected) return std::nullopt;
    
    try {
        std::string sql = R"(
            SELECT q.*, c.nome AS categoria, c.cor_hex 
            FROM questoes q 
            INNER JOIN categorias c ON q.id_categoria = c.id_categoria
            WHERE q.id_questao = $1
        )";
        
        const char* paramValues[1];
        std::string idStr = std::to_string(id_questao);
        paramValues[0] = idStr.c_str();
        
        PGresult* res = PQexecParams(conn, sql.c_str(), 1, nullptr, paramValues, nullptr, nullptr, 0);
        
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res) > 0) {
            Questao q = buildQuestaoFromResult(res, 0);
            PQclear(res);
            return q;
        }
        
        PQclear(res);
        return std::nullopt;
    }
    catch (const std::exception& e) {
        std::cerr << "[Database] Erro ao buscar questão: " << e.what() << std::endl;
        return std::nullopt;
    }
}

int DatabaseManager::insertQuestao(const std::string& pergunta, int id_categoria, 
                                   const std::string& dificuldade, int pontos) {
    if (!connected) return -1;
    
    try {
        std::string sql = R"(
            INSERT INTO questoes (pergunta, id_categoria, dificuldade, pontos) 
            VALUES ($1, $2, $3, $4) 
            RETURNING id_questao
        )";
        
        const char* paramValues[4];
        std::string catStr = std::to_string(id_categoria);
        std::string ptsStr = std::to_string(pontos);
        paramValues[0] = pergunta.c_str();
        paramValues[1] = catStr.c_str();
        paramValues[2] = dificuldade.c_str();
        paramValues[3] = ptsStr.c_str();
        
        PGresult* res = PQexecParams(conn, sql.c_str(), 4, nullptr, paramValues, nullptr, nullptr, 0);
        
        int id = -1;
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res) > 0) {
            id = std::atoi(PQgetvalue(res, 0, 0));
            std::cout << "[Database] Questão inserida com ID: " << id << std::endl;
        } else {
            std::cerr << "[Database] Erro ao inserir questão: " << PQerrorMessage(conn) << std::endl;
        }
        
        PQclear(res);
        return id;
    }
    catch (const std::exception& e) {
        std::cerr << "[Database] Erro ao inserir questão: " << e.what() << std::endl;
        return -1;
    }
}

bool DatabaseManager::updateQuestao(int id_questao, const std::string& pergunta, 
                                    const std::string& dificuldade, int pontos) {
    if (!connected) return false;
    
    try {
        std::string sql = R"(
            UPDATE questoes 
            SET pergunta = $1, dificuldade = $2, pontos = $3, data_atualizacao = CURRENT_TIMESTAMP
            WHERE id_questao = $4
        )";
        
        const char* paramValues[4];
        std::string ptsStr = std::to_string(pontos);
        std::string idStr = std::to_string(id_questao);
        paramValues[0] = pergunta.c_str();
        paramValues[1] = dificuldade.c_str();
        paramValues[2] = ptsStr.c_str();
        paramValues[3] = idStr.c_str();
        
        PGresult* res = PQexecParams(conn, sql.c_str(), 4, nullptr, paramValues, nullptr, nullptr, 0);
        
        bool success = (PQresultStatus(res) == PGRES_COMMAND_OK);
        if (success) {
            std::cout << "[Database] Questão atualizada: " << id_questao << std::endl;
        } else {
            std::cerr << "[Database] Erro ao atualizar questão: " << PQerrorMessage(conn) << std::endl;
        }
        
        PQclear(res);
        return success;
    }
    catch (const std::exception& e) {
        std::cerr << "[Database] Erro ao atualizar questão: " << e.what() << std::endl;
        return false;
    }
}

bool DatabaseManager::deleteQuestao(int id_questao) {
    if (!connected) return false;
    
    try {
        std::string sql = "DELETE FROM questoes WHERE id_questao = $1";
        
        const char* paramValues[1];
        std::string idStr = std::to_string(id_questao);
        paramValues[0] = idStr.c_str();
        
        PGresult* res = PQexecParams(conn, sql.c_str(), 1, nullptr, paramValues, nullptr, nullptr, 0);
        
        bool success = (PQresultStatus(res) == PGRES_COMMAND_OK);
        if (success) {
            std::cout << "[Database] Questão deletada: " << id_questao << std::endl;
        } else {
            std::cerr << "[Database] Erro ao deletar questão: " << PQerrorMessage(conn) << std::endl;
        }
        
        PQclear(res);
        return success;
    }
    catch (const std::exception& e) {
        std::cerr << "[Database] Erro ao deletar questão: " << e.what() << std::endl;
        return false;
    }
}

bool DatabaseManager::toggleQuestaoAtiva(int id_questao) {
    if (!connected) return false;
    
    try {
        std::string sql = R"(
            UPDATE questoes 
            SET ativo = NOT ativo 
            WHERE id_questao = $1
        )";
        
        const char* paramValues[1];
        std::string idStr = std::to_string(id_questao);
        paramValues[0] = idStr.c_str();
        
        PGresult* res = PQexecParams(conn, sql.c_str(), 1, nullptr, paramValues, nullptr, nullptr, 0);
        
        bool success = (PQresultStatus(res) == PGRES_COMMAND_OK);
        if (!success) {
            std::cerr << "[Database] Erro ao alternar status: " << PQerrorMessage(conn) << std::endl;
        }
        
        PQclear(res);
        return success;
    }
    catch (const std::exception& e) {
        std::cerr << "[Database] Erro ao alternar status da questão: " << e.what() << std::endl;
        return false;
    }
}

// ========================================
// CRUD - Alternativas
// ========================================

std::vector<Alternativa> DatabaseManager::getAlternativasPorQuestao(int id_questao) {
    std::vector<Alternativa> alternativas;
    
    if (!connected) return alternativas;
    
    try {
        // Buscar resposta correta da questão
        std::string sqlResposta = "SELECT resposta_correta FROM questoes WHERE id_questao = $1";
        std::string idStr = std::to_string(id_questao);
        const char* paramValuesResp[1] = { idStr.c_str() };
        
        PGresult* resResp = PQexecParams(conn, sqlResposta.c_str(), 1, nullptr, paramValuesResp, nullptr, nullptr, 0);
        int respostaCorreta = -1;
        
        if (PQresultStatus(resResp) == PGRES_TUPLES_OK && PQntuples(resResp) > 0) {
            respostaCorreta = std::atoi(PQgetvalue(resResp, 0, 0));
        }
        PQclear(resResp);
        
        // Buscar opções de resposta
        std::string sql = R"(
            SELECT id_opcao, id_questao, texto_opcao, ordem 
            FROM opcoes_resposta 
            WHERE id_questao = $1 
            ORDER BY ordem
        )";
        
        const char* paramValues[1] = { idStr.c_str() };
        PGresult* res = PQexecParams(conn, sql.c_str(), 1, nullptr, paramValues, nullptr, nullptr, 0);
        
        if (PQresultStatus(res) == PGRES_TUPLES_OK) {
            int rows = PQntuples(res);
            for (int i = 0; i < rows; i++) {
                Alternativa a;
                a.id_alternativa = std::atoi(PQgetvalue(res, i, PQfnumber(res, "id_opcao")));
                a.id_questao = std::atoi(PQgetvalue(res, i, PQfnumber(res, "id_questao")));
                a.texto = PQgetvalue(res, i, PQfnumber(res, "texto_opcao"));
                a.ordem = std::atoi(PQgetvalue(res, i, PQfnumber(res, "ordem")));
                a.correta = (a.ordem == respostaCorreta);
                alternativas.push_back(a);
            }
        } else {
            std::cerr << "[Database] Erro ao buscar alternativas: " << PQerrorMessage(conn) << std::endl;
        }
        
        PQclear(res);
    }
    catch (const std::exception& e) {
        std::cerr << "[Database] Erro ao buscar alternativas: " << e.what() << std::endl;
    }
    
    return alternativas;
}

int DatabaseManager::insertAlternativa(int id_questao, const std::string& texto, 
                                       bool correta, int ordem) {
    if (!connected) return -1;
    
    try {
        std::string sql = R"(
            INSERT INTO alternativas (id_questao, texto_alternativa, correta, ordem) 
            VALUES ($1, $2, $3, $4) 
            RETURNING id_alternativa
        )";
        
        const char* paramValues[4];
        std::string idStr = std::to_string(id_questao);
        std::string corrStr = correta ? "true" : "false";
        std::string ordStr = std::to_string(ordem);
        paramValues[0] = idStr.c_str();
        paramValues[1] = texto.c_str();
        paramValues[2] = corrStr.c_str();
        paramValues[3] = ordStr.c_str();
        
        PGresult* res = PQexecParams(conn, sql.c_str(), 4, nullptr, paramValues, nullptr, nullptr, 0);
        
        int id = -1;
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res) > 0) {
            id = std::atoi(PQgetvalue(res, 0, 0));
            std::cout << "[Database] Alternativa inserida com ID: " << id << std::endl;
        } else {
            std::cerr << "[Database] Erro ao inserir alternativa: " << PQerrorMessage(conn) << std::endl;
        }
        
        PQclear(res);
        return id;
    }
    catch (const std::exception& e) {
        std::cerr << "[Database] Erro ao inserir alternativa: " << e.what() << std::endl;
        return -1;
    }
}

bool DatabaseManager::updateAlternativa(int id_alternativa, const std::string& texto, bool correta) {
    if (!connected) return false;
    
    try {
        std::string sql = R"(
            UPDATE alternativas 
            SET texto_alternativa = $1, correta = $2
            WHERE id_alternativa = $3
        )";
        
        const char* paramValues[3];
        std::string corrStr = correta ? "true" : "false";
        std::string idStr = std::to_string(id_alternativa);
        paramValues[0] = texto.c_str();
        paramValues[1] = corrStr.c_str();
        paramValues[2] = idStr.c_str();
        
        PGresult* res = PQexecParams(conn, sql.c_str(), 3, nullptr, paramValues, nullptr, nullptr, 0);
        
        bool success = (PQresultStatus(res) == PGRES_COMMAND_OK);
        if (!success) {
            std::cerr << "[Database] Erro ao atualizar alternativa: " << PQerrorMessage(conn) << std::endl;
        }
        
        PQclear(res);
        return success;
    }
    catch (const std::exception& e) {
        std::cerr << "[Database] Erro ao atualizar alternativa: " << e.what() << std::endl;
        return false;
    }
}

bool DatabaseManager::deleteAlternativa(int id_alternativa) {
    if (!connected) return false;
    
    try {
        std::string sql = "DELETE FROM alternativas WHERE id_alternativa = $1";
        
        const char* paramValues[1];
        std::string idStr = std::to_string(id_alternativa);
        paramValues[0] = idStr.c_str();
        
        PGresult* res = PQexecParams(conn, sql.c_str(), 1, nullptr, paramValues, nullptr, nullptr, 0);
        
        bool success = (PQresultStatus(res) == PGRES_COMMAND_OK);
        if (!success) {
            std::cerr << "[Database] Erro ao deletar alternativa: " << PQerrorMessage(conn) << std::endl;
        }
        
        PQclear(res);
        return success;
    }
    catch (const std::exception& e) {
        std::cerr << "[Database] Erro ao deletar alternativa: " << e.what() << std::endl;
        return false;
    }
}

// ========================================
// CRUD - Categorias
// ========================================

std::vector<Categoria> DatabaseManager::getAllCategorias(bool apenasAtivas) {
    std::vector<Categoria> categorias;
    
    if (!connected) return categorias;
    
    try {
        std::string sql = "SELECT * FROM categorias";
        
        if (apenasAtivas) {
            sql += " WHERE ativo = TRUE";
        }
        
        sql += " ORDER BY nome";
        
        PGresult* res = PQexec(conn, sql.c_str());
        
        if (PQresultStatus(res) == PGRES_TUPLES_OK) {
            int rows = PQntuples(res);
            for (int i = 0; i < rows; i++) {
                Categoria c;
                c.id_categoria = std::atoi(PQgetvalue(res, i, PQfnumber(res, "id_categoria")));
                c.nome = PQgetvalue(res, i, PQfnumber(res, "nome"));
                
                int descIdx = PQfnumber(res, "descricao");
                c.descricao = PQgetisnull(res, i, descIdx) ? "" : PQgetvalue(res, i, descIdx);
                
                int corIdx = PQfnumber(res, "cor_hex");
                c.cor_hex = PQgetisnull(res, i, corIdx) ? "" : PQgetvalue(res, i, corIdx);
                
                c.ativo = (std::string(PQgetvalue(res, i, PQfnumber(res, "ativo"))) == "t");
                categorias.push_back(c);
            }
        } else {
            std::cerr << "[Database] Erro ao buscar categorias: " << PQerrorMessage(conn) << std::endl;
        }
        
        PQclear(res);
    }
    catch (const std::exception& e) {
        std::cerr << "[Database] Erro ao buscar categorias: " << e.what() << std::endl;
    }
    
    return categorias;
}

std::optional<Categoria> DatabaseManager::getCategoriaPorId(int id_categoria) {
    if (!connected) return std::nullopt;
    
    try {
        std::string sql = "SELECT * FROM categorias WHERE id_categoria = $1";
        
        const char* paramValues[1];
        std::string idStr = std::to_string(id_categoria);
        paramValues[0] = idStr.c_str();
        
        PGresult* res = PQexecParams(conn, sql.c_str(), 1, nullptr, paramValues, nullptr, nullptr, 0);
        
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res) > 0) {
            Categoria c;
            c.id_categoria = std::atoi(PQgetvalue(res, 0, PQfnumber(res, "id_categoria")));
            c.nome = PQgetvalue(res, 0, PQfnumber(res, "nome"));
            
            int descIdx = PQfnumber(res, "descricao");
            c.descricao = PQgetisnull(res, 0, descIdx) ? "" : PQgetvalue(res, 0, descIdx);
            
            int corIdx = PQfnumber(res, "cor_hex");
            c.cor_hex = PQgetisnull(res, 0, corIdx) ? "" : PQgetvalue(res, 0, corIdx);
            
            c.ativo = (std::string(PQgetvalue(res, 0, PQfnumber(res, "ativo"))) == "t");
            
            PQclear(res);
            return c;
        }
        
        PQclear(res);
        return std::nullopt;
    }
    catch (const std::exception& e) {
        std::cerr << "[Database] Erro ao buscar categoria: " << e.what() << std::endl;
        return std::nullopt;
    }
}

int DatabaseManager::insertCategoria(const std::string& nome, const std::string& descricao, 
                                     const std::string& cor_hex) {
    if (!connected) return -1;
    
    try {
        std::string sql = R"(
            INSERT INTO categorias (nome, descricao, cor_hex) 
            VALUES ($1, $2, $3) 
            RETURNING id_categoria
        )";
        
        const char* paramValues[3];
        paramValues[0] = nome.c_str();
        paramValues[1] = descricao.c_str();
        paramValues[2] = cor_hex.c_str();
        
        PGresult* res = PQexecParams(conn, sql.c_str(), 3, nullptr, paramValues, nullptr, nullptr, 0);
        
        int id = -1;
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res) > 0) {
            id = std::atoi(PQgetvalue(res, 0, 0));
            std::cout << "[Database] Categoria inserida com ID: " << id << std::endl;
        } else {
            std::cerr << "[Database] Erro ao inserir categoria: " << PQerrorMessage(conn) << std::endl;
        }
        
        PQclear(res);
        return id;
    }
    catch (const std::exception& e) {
        std::cerr << "[Database] Erro ao inserir categoria: " << e.what() << std::endl;
        return -1;
    }
}

bool DatabaseManager::updateCategoria(int id_categoria, const std::string& nome, 
                                      const std::string& descricao, const std::string& cor_hex) {
    if (!connected) return false;
    
    try {
        std::string sql = R"(
            UPDATE categorias 
            SET nome = $1, descricao = $2, cor_hex = $3
            WHERE id_categoria = $4
        )";
        
        const char* paramValues[4];
        std::string idStr = std::to_string(id_categoria);
        paramValues[0] = nome.c_str();
        paramValues[1] = descricao.c_str();
        paramValues[2] = cor_hex.c_str();
        paramValues[3] = idStr.c_str();
        
        PGresult* res = PQexecParams(conn, sql.c_str(), 4, nullptr, paramValues, nullptr, nullptr, 0);
        bool success = (PQresultStatus(res) == PGRES_COMMAND_OK);
        PQclear(res);
        return success;
    }
    catch (const std::exception& e) {
        std::cerr << "[Database] Erro ao atualizar categoria: " << e.what() << std::endl;
        return false;
    }
}

bool DatabaseManager::deleteCategoria(int id_categoria) {
    if (!connected) return false;
    
    try {
        std::string sql = "DELETE FROM categorias WHERE id_categoria = $1";
        
        const char* paramValues[1];
        std::string idStr = std::to_string(id_categoria);
        paramValues[0] = idStr.c_str();
        
        PGresult* res = PQexecParams(conn, sql.c_str(), 1, nullptr, paramValues, nullptr, nullptr, 0);
        bool success = (PQresultStatus(res) == PGRES_COMMAND_OK);
        PQclear(res);
        return success;
    }
    catch (const std::exception& e) {
        std::cerr << "[Database] Erro ao deletar categoria: " << e.what() << std::endl;
        return false;
    }
}

// ========================================
// Utilitários
// ========================================

int DatabaseManager::getContagemQuestoes(int id_categoria) {
    if (!connected) return 0;
    
    try {
        std::string sql;
        PGresult* res;
        
        if (id_categoria > 0) {
            sql = "SELECT COUNT(*) FROM questoes WHERE id_categoria = $1 AND ativo = TRUE";
            const char* paramValues[1];
            std::string idStr = std::to_string(id_categoria);
            paramValues[0] = idStr.c_str();
            res = PQexecParams(conn, sql.c_str(), 1, nullptr, paramValues, nullptr, nullptr, 0);
        } else {
            sql = "SELECT COUNT(*) FROM questoes WHERE ativo = TRUE";
            res = PQexec(conn, sql.c_str());
        }
        
        int count = 0;
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res) > 0) {
            count = std::atoi(PQgetvalue(res, 0, 0));
        } else {
            std::cerr << "[Database] Erro ao contar questões: " << PQerrorMessage(conn) << std::endl;
        }
        
        PQclear(res);
        return count;
    }
    catch (const std::exception& e) {
        std::cerr << "[Database] Erro ao contar questões: " << e.what() << std::endl;
        return 0;
    }
}

} // namespace Database

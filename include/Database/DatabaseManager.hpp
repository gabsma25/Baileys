#ifndef DATABASE_MANAGER_HPP
#define DATABASE_MANAGER_HPP

#include <libpq-fe.h>
#include <string>
#include <vector>
#include <memory>
#include <optional>

namespace Database {

struct Alternativa {
    int id_alternativa;
    int id_questao;
    std::string texto;
    bool correta;
    int ordem;
};

struct Questao {
    int id_questao;
    int id_categoria;
    std::string pergunta;
    std::string dificuldade;
    int pontos;
    std::string categoria_nome;
    std::string cor_hex;
    std::vector<Alternativa> alternativas;
};

struct Categoria {
    int id_categoria;
    std::string nome;
    std::string descricao;
    std::string cor_hex;
    bool ativo;
};



class DatabaseManager {
private:
    PGconn* conn;
    std::string connection_string;
    bool connected;
    std::string lastError;

    // Métodos auxiliares
    bool executeQuery(const std::string& query);
    PGresult* executeQueryWithResult(const std::string& query);
    std::string escapeString(const std::string& str);
    Questao buildQuestaoFromResult(PGresult* res, int row);

public:
    DatabaseManager();
    ~DatabaseManager();

    // Conexão
    bool connect(const std::string& host = "localhost", 
                 const std::string& port = "5432",
                 const std::string& dbname = "face_quiz_db",
                 const std::string& user = "postgres",
                 const std::string& password = "");
    void disconnect();
    bool isConnected() const { return connected; }
    std::string getLastError() const { return lastError; }

    // CRUD - Questões
    std::vector<Questao> getAllQuestoes(bool apenasAtivas = true);
    std::vector<Questao> getQuestoesPorCategoria(int id_categoria, bool apenasAtivas = true);
    std::vector<Questao> getQuestoesAleatorias(int limite = 10, bool apenasAtivas = true);
    std::vector<Questao> getQuestoesAleatoriasCategoria(int id_categoria, int limite = 10);
    std::optional<Questao> getQuestaoPorId(int id_questao);
    int insertQuestao(const std::string& pergunta, int id_categoria, 
                      const std::string& dificuldade, int pontos);
    bool updateQuestao(int id_questao, const std::string& pergunta, 
                       const std::string& dificuldade, int pontos);
    bool deleteQuestao(int id_questao);
    bool toggleQuestaoAtiva(int id_questao);

    // CRUD - Alternativas
    std::vector<Alternativa> getAlternativasPorQuestao(int id_questao);
    int insertAlternativa(int id_questao, const std::string& texto, bool correta, int ordem);
    bool updateAlternativa(int id_alternativa, const std::string& texto, bool correta);
    bool deleteAlternativa(int id_alternativa);

    // CRUD - Categorias
    std::vector<Categoria> getAllCategorias(bool apenasAtivas = true);
    std::optional<Categoria> getCategoriaPorId(int id_categoria);
    int insertCategoria(const std::string& nome, const std::string& descricao, 
                        const std::string& cor_hex);
    bool updateCategoria(int id_categoria, const std::string& nome, 
                         const std::string& descricao, const std::string& cor_hex);
    bool deleteCategoria(int id_categoria);

    // Utilitários
    int getContagemQuestoes(int id_categoria = -1);
};

} // namespace Database

#endif // DATABASE_MANAGER_HPP

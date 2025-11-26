-- ============================================
-- FACE GAME - SCHEMA SIMPLIFICADO
-- 30 Questões balanceadas por categoria
-- ============================================

\c face_game_db;

-- Limpar tabelas existentes
DROP TABLE IF EXISTS opcoes_resposta CASCADE;
DROP TABLE IF EXISTS questoes CASCADE;
DROP TABLE IF EXISTS categorias CASCADE;

-- ============================================
-- ESTRUTURA DAS TABELAS
-- ============================================

CREATE TABLE categorias (
    id_categoria SERIAL PRIMARY KEY,
    nome VARCHAR(50) NOT NULL UNIQUE,
    descricao TEXT,
    cor_hex VARCHAR(7) DEFAULT '#3A5469',
    ativo BOOLEAN DEFAULT TRUE,
    data_criacao TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE questoes (
    id_questao SERIAL PRIMARY KEY,
    pergunta TEXT NOT NULL,
    id_categoria INTEGER REFERENCES categorias(id_categoria) ON DELETE SET NULL,
    resposta_correta INTEGER NOT NULL CHECK (resposta_correta BETWEEN 0 AND 3),
    explicacao TEXT,
    ativo BOOLEAN DEFAULT TRUE,
    data_criacao TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    data_atualizacao TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE opcoes_resposta (
    id_opcao SERIAL PRIMARY KEY,
    id_questao INTEGER NOT NULL REFERENCES questoes(id_questao) ON DELETE CASCADE,
    texto_opcao TEXT NOT NULL,
    ordem INTEGER NOT NULL CHECK (ordem BETWEEN 0 AND 3),
    UNIQUE(id_questao, ordem)
);

-- Índices
CREATE INDEX idx_questoes_categoria ON questoes(id_categoria);
CREATE INDEX idx_questoes_ativo ON questoes(ativo);
CREATE INDEX idx_opcoes_questao ON opcoes_resposta(id_questao);

-- Trigger para atualizar timestamp
CREATE OR REPLACE FUNCTION atualizar_timestamp()
RETURNS TRIGGER AS $$
BEGIN
    NEW.data_atualizacao = CURRENT_TIMESTAMP;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trigger_atualizar_questao
    BEFORE UPDATE ON questoes
    FOR EACH ROW
    EXECUTE FUNCTION atualizar_timestamp();

-- View para consultas
CREATE VIEW vw_questoes_completas AS
SELECT 
    q.id_questao,
    q.pergunta,
    c.nome AS categoria,
    q.resposta_correta,
    q.explicacao,
    q.ativo,
    ARRAY_AGG(o.texto_opcao ORDER BY o.ordem) AS opcoes
FROM questoes q
LEFT JOIN categorias c ON q.id_categoria = c.id_categoria
LEFT JOIN opcoes_resposta o ON q.id_questao = o.id_questao
GROUP BY q.id_questao, c.nome;

-- ============================================
-- INSERIR CATEGORIAS
-- ============================================

INSERT INTO categorias (nome, descricao, cor_hex) VALUES
('Geografia', 'Países, capitais e geografia mundial', '#F07F0F'),
('História', 'Eventos históricos e personalidades', '#D85824'),
('Ciências', 'Biologia, Química e Física', '#9F361E'),
('Matemática', 'Cálculos e lógica matemática', '#646C2D'),
('Tecnologia', 'Computação e inovações', '#3A5469');

-- ============================================
-- GEOGRAFIA (6 questões)
-- ============================================

INSERT INTO questoes (pergunta, id_categoria, resposta_correta, explicacao) VALUES
('Qual é a capital do Brasil?', 1, 2, 'Brasília, inaugurada em 1960.');
INSERT INTO opcoes_resposta (id_questao, texto_opcao, ordem) VALUES
(currval('questoes_id_questao_seq'), 'Rio de Janeiro', 0),
(currval('questoes_id_questao_seq'), 'São Paulo', 1),
(currval('questoes_id_questao_seq'), 'Brasília', 2),
(currval('questoes_id_questao_seq'), 'Salvador', 3);

INSERT INTO questoes (pergunta, id_categoria, resposta_correta, explicacao) VALUES
('Qual o maior país do mundo em extensão territorial?', 1, 1, 'Rússia com 17,1 milhões de km².');
INSERT INTO opcoes_resposta (id_questao, texto_opcao, ordem) VALUES
(currval('questoes_id_questao_seq'), 'Canadá', 0),
(currval('questoes_id_questao_seq'), 'Rússia', 1),
(currval('questoes_id_questao_seq'), 'China', 2),
(currval('questoes_id_questao_seq'), 'Estados Unidos', 3);

INSERT INTO questoes (pergunta, id_categoria, resposta_correta, explicacao) VALUES
('Em qual continente está o Egito?', 1, 0, 'Maior parte na África.');
INSERT INTO opcoes_resposta (id_questao, texto_opcao, ordem) VALUES
(currval('questoes_id_questao_seq'), 'África', 0),
(currval('questoes_id_questao_seq'), 'Ásia', 1),
(currval('questoes_id_questao_seq'), 'Europa', 2),
(currval('questoes_id_questao_seq'), 'Oceania', 3);

INSERT INTO questoes (pergunta, id_categoria, resposta_correta, explicacao) VALUES
('Qual é o rio mais extenso do mundo?', 1, 1, 'Amazonas com 6.992 km.');
INSERT INTO opcoes_resposta (id_questao, texto_opcao, ordem) VALUES
(currval('questoes_id_questao_seq'), 'Rio Nilo', 0),
(currval('questoes_id_questao_seq'), 'Rio Amazonas', 1),
(currval('questoes_id_questao_seq'), 'Rio Yangtzé', 2),
(currval('questoes_id_questao_seq'), 'Rio Mississipi', 3);

INSERT INTO questoes (pergunta, id_categoria, resposta_correta, explicacao) VALUES
('Qual é a capital da Austrália?', 1, 2, 'Canberra, não Sydney.');
INSERT INTO opcoes_resposta (id_questao, texto_opcao, ordem) VALUES
(currval('questoes_id_questao_seq'), 'Sydney', 0),
(currval('questoes_id_questao_seq'), 'Melbourne', 1),
(currval('questoes_id_questao_seq'), 'Canberra', 2),
(currval('questoes_id_questao_seq'), 'Perth', 3);

INSERT INTO questoes (pergunta, id_categoria, resposta_correta, explicacao) VALUES
('Quantos estados possui o Brasil?', 1, 2, '26 estados + DF = 27 UFs.');
INSERT INTO opcoes_resposta (id_questao, texto_opcao, ordem) VALUES
(currval('questoes_id_questao_seq'), '25', 0),
(currval('questoes_id_questao_seq'), '24', 1),
(currval('questoes_id_questao_seq'), '27', 2),
(currval('questoes_id_questao_seq'), '26', 3);

-- ============================================
-- CIÊNCIAS (6 questões)
-- ============================================

INSERT INTO questoes (pergunta, id_categoria, resposta_correta, explicacao) VALUES
('Qual planeta está mais próximo do Sol?', 3, 0, 'Mercúrio é o primeiro.');
INSERT INTO opcoes_resposta (id_questao, texto_opcao, ordem) VALUES
(currval('questoes_id_questao_seq'), 'Mercúrio', 0),
(currval('questoes_id_questao_seq'), 'Vênus', 1),
(currval('questoes_id_questao_seq'), 'Terra', 2),
(currval('questoes_id_questao_seq'), 'Marte', 3);

INSERT INTO questoes (pergunta, id_categoria, resposta_correta, explicacao) VALUES
('Qual é o maior planeta do Sistema Solar?', 3, 2, 'Júpiter com 142.984 km de diâmetro.');
INSERT INTO opcoes_resposta (id_questao, texto_opcao, ordem) VALUES
(currval('questoes_id_questao_seq'), 'Saturno', 0),
(currval('questoes_id_questao_seq'), 'Urano', 1),
(currval('questoes_id_questao_seq'), 'Júpiter', 2),
(currval('questoes_id_questao_seq'), 'Netuno', 3);

INSERT INTO questoes (pergunta, id_categoria, resposta_correta, explicacao) VALUES
('Qual gás é mais abundante na atmosfera?', 3, 1, 'Nitrogênio com 78%.');
INSERT INTO opcoes_resposta (id_questao, texto_opcao, ordem) VALUES
(currval('questoes_id_questao_seq'), 'Oxigênio', 0),
(currval('questoes_id_questao_seq'), 'Nitrogênio', 1),
(currval('questoes_id_questao_seq'), 'Carbono', 2),
(currval('questoes_id_questao_seq'), 'Hidrogênio', 3);

INSERT INTO questoes (pergunta, id_categoria, resposta_correta, explicacao) VALUES
('Quantos ossos tem o corpo humano adulto?', 3, 3, '206 ossos no adulto.');
INSERT INTO opcoes_resposta (id_questao, texto_opcao, ordem) VALUES
(currval('questoes_id_questao_seq'), '198', 0),
(currval('questoes_id_questao_seq'), '201', 1),
(currval('questoes_id_questao_seq'), '212', 2),
(currval('questoes_id_questao_seq'), '206', 3);

INSERT INTO questoes (pergunta, id_categoria, resposta_correta, explicacao) VALUES
('Qual é a fórmula química da água?', 3, 1, 'H2O: 2 hidrogênios + 1 oxigênio.');
INSERT INTO opcoes_resposta (id_questao, texto_opcao, ordem) VALUES
(currval('questoes_id_questao_seq'), 'HO2', 0),
(currval('questoes_id_questao_seq'), 'H2O', 1),
(currval('questoes_id_questao_seq'), 'H3O', 2),
(currval('questoes_id_questao_seq'), 'HO', 3);

INSERT INTO questoes (pergunta, id_categoria, resposta_correta, explicacao) VALUES
('Qual o menor osso do corpo humano?', 3, 0, 'Estribo no ouvido, 2,5mm.');
INSERT INTO opcoes_resposta (id_questao, texto_opcao, ordem) VALUES
(currval('questoes_id_questao_seq'), 'Estribo', 0),
(currval('questoes_id_questao_seq'), 'Martelo', 1),
(currval('questoes_id_questao_seq'), 'Bigorna', 2),
(currval('questoes_id_questao_seq'), 'Patela', 3);

-- ============================================
-- MATEMÁTICA (6 questões)
-- ============================================

INSERT INTO questoes (pergunta, id_categoria, resposta_correta, explicacao) VALUES
('Quanto é 2 + 2?', 4, 1, 'Adição básica.');
INSERT INTO opcoes_resposta (id_questao, texto_opcao, ordem) VALUES
(currval('questoes_id_questao_seq'), '3', 0),
(currval('questoes_id_questao_seq'), '4', 1),
(currval('questoes_id_questao_seq'), '5', 2),
(currval('questoes_id_questao_seq'), '6', 3);

INSERT INTO questoes (pergunta, id_categoria, resposta_correta, explicacao) VALUES
('Quanto é 10 × 10?', 4, 2, 'Multiplicação básica.');
INSERT INTO opcoes_resposta (id_questao, texto_opcao, ordem) VALUES
(currval('questoes_id_questao_seq'), '50', 0),
(currval('questoes_id_questao_seq'), '90', 1),
(currval('questoes_id_questao_seq'), '100', 2),
(currval('questoes_id_questao_seq'), '110', 3);

INSERT INTO questoes (pergunta, id_categoria, resposta_correta, explicacao) VALUES
('Qual é a metade de 50?', 4, 0, 'Dividir por 2.');
INSERT INTO opcoes_resposta (id_questao, texto_opcao, ordem) VALUES
(currval('questoes_id_questao_seq'), '25', 0),
(currval('questoes_id_questao_seq'), '20', 1),
(currval('questoes_id_questao_seq'), '30', 2),
(currval('questoes_id_questao_seq'), '15', 3);

INSERT INTO questoes (pergunta, id_categoria, resposta_correta, explicacao) VALUES
('Quantos lados tem um triângulo?', 4, 3, 'Tri = três lados.');
INSERT INTO opcoes_resposta (id_questao, texto_opcao, ordem) VALUES
(currval('questoes_id_questao_seq'), '2', 0),
(currval('questoes_id_questao_seq'), '4', 1),
(currval('questoes_id_questao_seq'), '5', 2),
(currval('questoes_id_questao_seq'), '3', 3);

INSERT INTO questoes (pergunta, id_categoria, resposta_correta, explicacao) VALUES
('Qual é o valor de π aproximadamente?', 4, 2, 'Pi ≈ 3,14159.');
INSERT INTO opcoes_resposta (id_questao, texto_opcao, ordem) VALUES
(currval('questoes_id_questao_seq'), '2,14', 0),
(currval('questoes_id_questao_seq'), '3,00', 1),
(currval('questoes_id_questao_seq'), '3,14', 2),
(currval('questoes_id_questao_seq'), '3,50', 3);

INSERT INTO questoes (pergunta, id_categoria, resposta_correta, explicacao) VALUES
('Qual é a raiz quadrada de 64?', 4, 0, '8 × 8 = 64.');
INSERT INTO opcoes_resposta (id_questao, texto_opcao, ordem) VALUES
(currval('questoes_id_questao_seq'), '8', 0),
(currval('questoes_id_questao_seq'), '6', 1),
(currval('questoes_id_questao_seq'), '7', 2),
(currval('questoes_id_questao_seq'), '9', 3);

-- ============================================
-- HISTÓRIA (6 questões)
-- ============================================

INSERT INTO questoes (pergunta, id_categoria, resposta_correta, explicacao) VALUES
('Em que ano foi a Independência do Brasil?', 2, 1, '7 de setembro de 1822.');
INSERT INTO opcoes_resposta (id_questao, texto_opcao, ordem) VALUES
(currval('questoes_id_questao_seq'), '1808', 0),
(currval('questoes_id_questao_seq'), '1822', 1),
(currval('questoes_id_questao_seq'), '1889', 2),
(currval('questoes_id_questao_seq'), '1500', 3);

INSERT INTO questoes (pergunta, id_categoria, resposta_correta, explicacao) VALUES
('Quem foi o primeiro presidente do Brasil?', 2, 0, 'Deodoro da Fonseca em 1889.');
INSERT INTO opcoes_resposta (id_questao, texto_opcao, ordem) VALUES
(currval('questoes_id_questao_seq'), 'Deodoro da Fonseca', 0),
(currval('questoes_id_questao_seq'), 'Floriano Peixoto', 1),
(currval('questoes_id_questao_seq'), 'Getúlio Vargas', 2),
(currval('questoes_id_questao_seq'), 'Juscelino Kubitschek', 3);

INSERT INTO questoes (pergunta, id_categoria, resposta_correta, explicacao) VALUES
('Quando terminou a Segunda Guerra Mundial?', 2, 2, 'Rendição do Japão em 1945.');
INSERT INTO opcoes_resposta (id_questao, texto_opcao, ordem) VALUES
(currval('questoes_id_questao_seq'), '1939', 0),
(currval('questoes_id_questao_seq'), '1944', 1),
(currval('questoes_id_questao_seq'), '1945', 2),
(currval('questoes_id_questao_seq'), '1946', 3);

INSERT INTO questoes (pergunta, id_categoria, resposta_correta, explicacao) VALUES
('Quem pintou o teto da Capela Sistina?', 2, 1, 'Michelangelo (1508-1512).');
INSERT INTO opcoes_resposta (id_questao, texto_opcao, ordem) VALUES
(currval('questoes_id_questao_seq'), 'Leonardo da Vinci', 0),
(currval('questoes_id_questao_seq'), 'Michelangelo', 1),
(currval('questoes_id_questao_seq'), 'Rafael', 2),
(currval('questoes_id_questao_seq'), 'Donatello', 3);

INSERT INTO questoes (pergunta, id_categoria, resposta_correta, explicacao) VALUES
('Em que século foi a Revolução Francesa?', 2, 2, 'Começou em 1789, século XVIII.');
INSERT INTO opcoes_resposta (id_questao, texto_opcao, ordem) VALUES
(currval('questoes_id_questao_seq'), 'XVII', 0),
(currval('questoes_id_questao_seq'), 'XIX', 1),
(currval('questoes_id_questao_seq'), 'XVIII', 2),
(currval('questoes_id_questao_seq'), 'XVI', 3);

INSERT INTO questoes (pergunta, id_categoria, resposta_correta, explicacao) VALUES
('Qual civilização construiu Machu Picchu?', 2, 3, 'Incas no século XV.');
INSERT INTO opcoes_resposta (id_questao, texto_opcao, ordem) VALUES
(currval('questoes_id_questao_seq'), 'Astecas', 0),
(currval('questoes_id_questao_seq'), 'Maias', 1),
(currval('questoes_id_questao_seq'), 'Toltecas', 2),
(currval('questoes_id_questao_seq'), 'Incas', 3);

-- ============================================
-- TECNOLOGIA (6 questões)
-- ============================================

INSERT INTO questoes (pergunta, id_categoria, resposta_correta, explicacao) VALUES
('Quem fundou a Microsoft?', 5, 0, 'Bill Gates com Paul Allen em 1975.');
INSERT INTO opcoes_resposta (id_questao, texto_opcao, ordem) VALUES
(currval('questoes_id_questao_seq'), 'Bill Gates', 0),
(currval('questoes_id_questao_seq'), 'Steve Jobs', 1),
(currval('questoes_id_questao_seq'), 'Mark Zuckerberg', 2),
(currval('questoes_id_questao_seq'), 'Elon Musk', 3);

INSERT INTO questoes (pergunta, id_categoria, resposta_correta, explicacao) VALUES
('O que significa CPU?', 5, 2, 'Central Processing Unit.');
INSERT INTO opcoes_resposta (id_questao, texto_opcao, ordem) VALUES
(currval('questoes_id_questao_seq'), 'Computer Personal Unit', 0),
(currval('questoes_id_questao_seq'), 'Central Power Unit', 1),
(currval('questoes_id_questao_seq'), 'Central Processing Unit', 2),
(currval('questoes_id_questao_seq'), 'Core Processing Unit', 3);

INSERT INTO questoes (pergunta, id_categoria, resposta_correta, explicacao) VALUES
('Qual empresa criou o Android?', 5, 3, 'Google adquiriu em 2005.');
INSERT INTO opcoes_resposta (id_questao, texto_opcao, ordem) VALUES
(currval('questoes_id_questao_seq'), 'Apple', 0),
(currval('questoes_id_questao_seq'), 'Microsoft', 1),
(currval('questoes_id_questao_seq'), 'Samsung', 2),
(currval('questoes_id_questao_seq'), 'Google', 3);

INSERT INTO questoes (pergunta, id_categoria, resposta_correta, explicacao) VALUES
('O que é RAM?', 5, 0, 'Random Access Memory.');
INSERT INTO opcoes_resposta (id_questao, texto_opcao, ordem) VALUES
(currval('questoes_id_questao_seq'), 'Memória de acesso aleatório', 0),
(currval('questoes_id_questao_seq'), 'Memória permanente', 1),
(currval('questoes_id_questao_seq'), 'Processador', 2),
(currval('questoes_id_questao_seq'), 'Disco rígido', 3);

INSERT INTO questoes (pergunta, id_categoria, resposta_correta, explicacao) VALUES
('O que significa HTML?', 5, 2, 'HyperText Markup Language.');
INSERT INTO opcoes_resposta (id_questao, texto_opcao, ordem) VALUES
(currval('questoes_id_questao_seq'), 'High Tech Modern Language', 0),
(currval('questoes_id_questao_seq'), 'Home Tool Markup Language', 1),
(currval('questoes_id_questao_seq'), 'HyperText Markup Language', 2),
(currval('questoes_id_questao_seq'), 'Hyper Transfer Markup Language', 3);

INSERT INTO questoes (pergunta, id_categoria, resposta_correta, explicacao) VALUES
('O que é SQL?', 5, 1, 'Structured Query Language.');
INSERT INTO opcoes_resposta (id_questao, texto_opcao, ordem) VALUES
(currval('questoes_id_questao_seq'), 'Sistema de consulta linear', 0),
(currval('questoes_id_questao_seq'), 'Linguagem de consulta estruturada', 1),
(currval('questoes_id_questao_seq'), 'Software de qualidade', 2),
(currval('questoes_id_questao_seq'), 'Servidor de qualidade', 3);

-- ============================================
-- CONSULTAS ÚTEIS
-- ============================================

-- Ver todas as questões
-- SELECT * FROM vw_questoes_completas;

-- Buscar 10 questões aleatórias
-- SELECT * FROM vw_questoes_completas 
-- WHERE ativo = TRUE 
-- ORDER BY RANDOM() 
-- LIMIT 10;

-- Contar questões por categoria
-- SELECT c.nome, COUNT(q.id_questao) as total
-- FROM categorias c
-- LEFT JOIN questoes q ON c.id_categoria = q.id_categoria
-- GROUP BY c.nome;
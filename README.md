# 🎮 FACE - O Teste de Conhecimento

## 📋 Sobre o Projeto

**FACE** é um jogo educacional com integração PostgreSQL que combina dois modos de jogo:

### 🎯 Modo Quiz
- Perguntas de múltipla escolha **carregadas do banco de dados PostgreSQL**
- 10 questões aleatórias por partida
- 4 opções de resposta
- Controle via teclado (teclas 1-4)
- Categorias: Geografia, Matemática, Ciências, História, Tecnologia, etc.

### 🔍 Modo Face (Dicas Progressivas)
- Sistema de dicas reveladas progressivamente
- Digitação livre da resposta
- Pontuação baseada no número de dicas usadas
- Quanto menos dicas, mais pontos!

## 🗄️ Banco de Dados

O jogo utiliza **PostgreSQL 16** para armazenar:
- ✅ 61 questões ativas em 10 categorias
- ✅ Sistema de aleatorização por sessão
- ✅ Estrutura completa com questões e opções de resposta

---

## 🏗️ Arquitetura do Projeto

### Estrutura Modular

```
face-game/
├── include/              # Headers (.hpp)
│   ├── Core/            # Sistema principal
│   │   ├── Game.hpp
│   │   └── SceneManager.hpp
│   ├── Scenes/          # Cenas do jogo
│   │   ├── Scene.hpp
│   │   ├── MenuScene.hpp
│   │   ├── QuizScene.hpp
│   │   └── FaceScene.hpp
│   ├── Utils/           # Utilitários
│   │   ├── Colors.hpp
│   │   └── FontManager.hpp
│   └── Config.hpp       # Configurações globais
│
├── src/                 # Implementações (.cpp)
│   ├── Core/
│   ├── Scenes/
│   └── Utils/
│
├── assets/              # Recursos
│   ├── fonts/          
│   └── sounds/         
│
├── .vscode/             # Configurações VSCode
├── main.cpp             # Ponto de entrada
└── compile.bat          # Script de compilação
```


## ⚙️ Configuração e Compilação

### Pré-requisitos

✅ MinGW64 instalado em `C:/mingw64/`  
✅ SFML 3.0.0 instalado em `C:/SFML-3.0.0/`  
✅ **PostgreSQL 16** instalado em `C:/Program Files/PostgreSQL/16/`  
✅ Banco de dados `face_quiz_db` configurado (veja `database/DATABASE_SETUP.md`)  
✅ Visual Studio Code (opcional)

### Configuração do Banco de Dados

1. Instale PostgreSQL 16
2. Configure senha: `1234` para usuário `postgres`
3. Execute o script SQL:
```bash
psql -U postgres -d face_quiz_db -f database/quiz_questions.sql
```

### Compilação Rápida 
```batch
compile.bat
```

O script automaticamente:
1. Configura PATH do MinGW, SFML e PostgreSQL
2. Compila todos os arquivos (incluindo DatabaseManager)
3. Linka libpq (PostgreSQL C API)
4. Cria `face-game.exe`
5. Copia `libpq.dll` necessária
4. Executa automaticamente se bem-sucedido

---

## 🎮 Como Jogar

### Menu Principal

- **Clique em QUIZ:** Inicia modo Quiz
- **Clique em FACE:** Inicia modo Face (dicas)
- **Clique em SAIR:** Fecha o jogo

### Modo Quiz

1. Leia a pergunta
2. Pressione **1, 2, 3 ou 4** para responder
3. Veja o feedback
4. Pressione **ESC** para voltar ao menu

### Modo Face

1. Veja a categoria do perfil
2. Leia a primeira dica
3. **ESPAÇO:** Revelar próxima dica
4. **Digite** sua resposta
5. **ENTER:** Confirmar resposta
6. **ESC:** Voltar ao menu

---

**Desenvolvido para:** Disciplina de Sistemas Multimídia Universidade Estadual de Roraima
**Tecnologias:** C++17 + SFML 3.0.0


🎮 **Divirta-se jogando FACE!** 🎮

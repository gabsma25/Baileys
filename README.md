# 🎮 FACE - O Jogo das Dicas

## 📋 Sobre o Projeto

**FACE** é um jogo educacional híbrido que combina dois modos de jogo:

### 🎯 Modo Quiz
- Perguntas de múltipla escolha
- 4 opções de resposta
- Controle via teclado (teclas 1-4)
- Categorias variadas

### 🔍 Modo Face (Dicas Progressivas)
- Sistema de dicas reveladas progressivamente
- Digitação livre da resposta
- Pontuação baseada no número de dicas usadas
- Quanto menos dicas, mais pontos!

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
│   ├── fonts/          (preparado)
│   └── sounds/         (preparado)
│
├── .vscode/             # Configurações VSCode
├── main.cpp             # Ponto de entrada
└── compile.bat          # Script de compilação
```

### 🎨 Paleta de Cores - Vibrante Outono

- **Fundo:** Tons marrons quentes
- **Destaques:** Amarelo, Laranja, Verde
- **Botões:** Azul marinho
- **Feedback:** Verde (correto), Vermelho (errado)

---

## ⚙️ Configuração e Compilação

### Pré-requisitos

✅ MinGW64 instalado em `C:/mingw64/`
✅ SFML 3.0.0 instalado em `C:/SFML-3.0.0/`
✅ Visual Studio Code (opcional)

### Método 1: Compilação Rápida (Recomendado)

```batch
compile.bat
```

O script:
1. Configura o PATH automaticamente
2. Compila todos os arquivos
3. Cria `face-game.exe`
4. Executa automaticamente se bem-sucedido

### Método 2: VSCode

1. Abra a pasta no VSCode
2. Pressione `Ctrl+Shift+B`
3. Selecione "Build FACE Game"
4. Execute com `F5`

### Método 3: Linha de Comando Manual

```bash
g++ -std=c++17 ^
    main.cpp ^
    src/Core/Game.cpp ^
    src/Core/SceneManager.cpp ^
    src/Scenes/MenuScene.cpp ^
    src/Scenes/QuizScene.cpp ^
    src/Scenes/FaceScene.cpp ^
    src/Utils/FontManager.cpp ^
    -o face-game.exe ^
    -I include ^
    -I C:/SFML-3.0.0/include ^
    -L C:/SFML-3.0.0/lib ^
    -lsfml-graphics -lsfml-window -lsfml-system ^
    -O2
```

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

## 🔧 Personalização

### Mudar Cores

Edite `include/Config.hpp`:

```cpp
namespace Colors {
    const unsigned int BG_R = 45;      // Fundo - Red
    const unsigned int BG_G = 35;      // Fundo - Green
    const unsigned int BG_B = 25;      // Fundo - Blue
    // ...
}
```

### Adicionar Perguntas (Quiz)

Edite `src/Scenes/QuizScene.cpp` no método `loadQuestions()`:

```cpp
questions.push_back({
    "Sua pergunta aqui?",
    {"Opção 1", "Opção 2", "Opção 3", "Opção 4"},
    2,  // Índice da resposta correta (0-3)
    "CATEGORIA"
});
```

### Adicionar Perfis (Face)

Edite `src/Scenes/FaceScene.cpp` no método `loadProfiles()`:

```cpp
profiles.push_back({
    "RESPOSTA CORRETA",
    {
        "Dica 1 genérica",
        "Dica 2 mais específica",
        "Dica 3 mais específica ainda",
        "Dica 4 bem específica",
        "Dica 5 óbvia"
    },
    "CATEGORIA"
});
```

---

## 📦 Estrutura de Dependências

```
main.cpp
  └─> Game.hpp
        ├─> SceneManager.hpp
        │     └─> Scene.hpp (interface)
        │           ├─> MenuScene.hpp
        │           ├─> QuizScene.hpp
        │           └─> FaceScene.hpp
        ├─> FontManager.hpp
        └─> Config.hpp
              └─> Colors.hpp
```

---

## 🚀 Funcionalidades Futuras (Preparadas)

- [ ] **Timer/Cronômetro** - Estrutura pronta em Config.hpp
- [ ] **Efeitos Sonoros** - Pasta `assets/sounds/` preparada
- [ ] **Diferentes Dificuldades** - Sistema de pontuação escalável
- [ ] **Ranking de Pontuação** - Sistema de score implementado
- [ ] **Mais Categorias** - Estrutura modular facilita expansão

---

## 🐛 Troubleshooting

### Problema: "cannot find -lsfml-graphics"

**Solução:** Verifique se SFML está em `C:/SFML-3.0.0/` e as DLLs em `C:/SFML-3.0.0/bin/`

### Problema: Fonte não carrega

**Solução:** O jogo tenta múltiplos caminhos automaticamente:
- `C:/Windows/Fonts/arial.ttf`
- `C:/Windows/Fonts/calibri.ttf`
- `C:/Windows/Fonts/verdana.ttf`

Se nenhum funcionar, coloque uma fonte .ttf em `assets/fonts/`

### Problema: DLLs não encontradas ao executar

**Solução:** Copie as DLLs de `C:/SFML-3.0.0/bin/` para a pasta do executável:
- `sfml-graphics-3.dll`
- `sfml-window-3.dll`
- `sfml-system-3.dll`

---

## 📚 Recursos Utilizados

- **SFML 3.0.0** - Framework multimídia
- **C++17** - Recursos modernos da linguagem
- **MinGW64** - Compilador GCC para Windows
- **Design Patterns:**
  - Singleton (FontManager)
  - State (SceneManager)
  - Template Method (Scene interface)

---

## ✅ Checklist de Requisitos

### TODOS os 10 requisitos implementados:

1. ✅ **Carregamento de Texturas** - Config.hpp + FontManager
2. ✅ **Exibição de Sprites** - Todas as cenas
3. ✅ **Definição de Shapes** - Botões, indicadores, caixas
4. ✅ **Exibição de Shapes** - render() em todas as cenas
5. ✅ **Definição de Textos** - Headers das cenas
6. ✅ **Exibição de Textos** - render() em todas as cenas
7. ✅ **Leitura de Inputs** - Mouse (Menu) + Teclado (Quiz/Face)
8. ✅ **Interação baseada nos inputs** - handleInput() implementado
9. ✅ **Lógica completa** - SceneManager + Game loop
10. ✅ **Mínimo 2 cenas** - Menu, Quiz e Face (3 cenas!)

### Inputs DIFERENTES por cena:
- **Menu:** MOUSE (cliques)
- **Quiz:** TECLADO (teclas 1-4, ESC)
- **Face:** TECLADO (letras, Space, Enter, ESC)

---

## 👨‍💻 Arquitetura de Código

### Princípios Aplicados

- **SOLID:**
  - Single Responsibility
  - Open/Closed
  - Liskov Substitution (Scene interface)
  - Interface Segregation
  - Dependency Inversion

- **Separação de Conceitos:**
  - Lógica de negócio (Core/)
  - Apresentação (Scenes/)
  - Utilidades (Utils/)
  - Configuração (Config.hpp)

- **Gerenciamento de Memória:**
  - Smart pointers (unique_ptr)
  - RAII
  - Sem memory leaks

---

## 📞 Suporte

- **Documentação SFML:** https://www.sfml-dev.org/documentation/
- **C++17 Reference:** https://en.cppreference.com/

---

**Desenvolvido para:** Disciplina de Sistemas Multimídia
**Tecnologias:** C++17 + SFML 3.0.0
**Arquitetura:** Modular e escalável

🎮 **Divirta-se jogando FACE!** 🎮

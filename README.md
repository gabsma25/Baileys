# Projeto Quiz Educacional - SFML

## 📋 Requisitos Atendidos

### ✅ Recursos Implementados (Presentes nas 2 Cenas)

#### 1. Carregamento de Texturas
- **Menu**: Textura de fundo criada programaticamente
- **Quiz**: Textura para ícone de feedback

#### 2. Exibição de Sprites
- **Menu**: Sprite de fundo
- **Quiz**: Sprite de feedback visual

#### 3. Definição de Shapes
- **Menu**: 
  - 2 Retângulos (botões)
  - 2 Círculos (decoração)
- **Quiz**: 
  - 1 Retângulo (caixa de pergunta)
  - 4 Círculos (indicadores de opções)
  - 1 Retângulo (barra de pontuação)

#### 4. Exibição de Shapes
- Todos os shapes são renderizados em ambas as cenas

#### 5. Definição de Textos
- **Menu**: Título, 2 botões
- **Quiz**: Pergunta, 4 opções, pontuação, feedback, instruções

#### 6. Exibição de Textos
- Todos os textos são renderizados em ambas as cenas

#### 7. Leitura de Inputs
- **Menu**: Mouse (clique)
- **Quiz**: Teclado (teclas 1-4 e ESC)

#### 8. Interação Baseada nos Inputs
- **Menu**: Botões respondem ao clique (mudam cor ao passar mouse)
- **Quiz**: Respostas são processadas e feedback é dado

#### 9. Lógica
- **Menu**: Iniciar quiz, sair do programa
- **Quiz**: Verificar respostas, calcular pontuação, avançar questões, voltar ao menu

#### 10. Mínimo 2 Cenas
- ✅ Cena 1: Menu Principal
- ✅ Cena 2: Quiz Interativo

### 🎮 Inputs Diferentes em Cada Cena
- **Menu**: Usa MOUSE (clique)
- **Quiz**: Usa TECLADO (teclas numéricas e ESC)

---

## 🛠️ Como Compilar

### No Linux (Ubuntu/Debian):

```bash
# Instalar SFML
sudo apt-get update
sudo apt-get install libsfml-dev

# Compilar o projeto
g++ -std=c++11 quiz_completo.cpp -o quiz -lsfml-graphics -lsfml-window -lsfml-system

# Executar
./quiz
```

### No Windows (MinGW):

```bash
# Após instalar SFML e configurar paths
g++ -std=c++11 quiz_completo.cpp -o quiz.exe -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -DSFML_STATIC

# Executar
quiz.exe
```

### Usando CMake (Multiplataforma):

Crie um arquivo `CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.10)
project(QuizEducacional)

set(CMAKE_CXX_STANDARD 11)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(quiz quiz_completo.cpp)
target_link_libraries(quiz sfml-graphics sfml-window sfml-system)
```

Então compile:
```bash
mkdir build
cd build
cmake ..
make
./quiz
```

---

## 🎯 Como Usar

### Menu Principal:
- Clique em "INICIAR QUIZ" para começar
- Clique em "SAIR" para fechar o programa
- Os botões mudam de cor ao passar o mouse

### Quiz:
- Leia a pergunta
- Pressione as teclas **1, 2, 3 ou 4** para selecionar a resposta
- Veja o feedback (CORRETO/ERRADO)
- Pressione **ESC** para voltar ao menu
- A pontuação aparece no canto superior direito

---

## 📝 Notas sobre o Código

### Fonte Utilizada:
O código usa `/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf` (disponível em sistemas Linux).

**Para Windows**, altere para uma fonte disponível:
```cpp
font.loadFromFile("C:/Windows/Fonts/arial.ttf")
```

**Ou coloque uma fonte .ttf na pasta do projeto** e use:
```cpp
font.loadFromFile("arial.ttf")
```

### Estrutura do Código:
- **MenuScene**: Gerencia o menu principal
- **QuizScene**: Gerencia o quiz e lógica de perguntas
- **main()**: Loop principal e gerenciamento de cenas

---

## 🚀 Melhorias Possíveis (Se Tiver Tempo)

1. Adicionar mais perguntas
2. Carregar imagens externas para o fundo
3. Adicionar efeitos sonoros
4. Animações de transição entre cenas
5. Tela de resultado final com estatísticas

---

## 📚 Recursos Úteis

- Documentação SFML: https://www.sfml-dev.org/documentation/
- Tutorial de Cenas: https://github.com/SFML/SFML/wiki/Tutorial:-Manage-different-Screens
- Exemplos de Jogos: https://github.com/suraj95/16-Games-in-SFML

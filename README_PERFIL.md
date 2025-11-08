# 🎮 PERFIL - O Jogo das Dicas

## 📝 Descrição do Projeto

Jogo inspirado no clássico **Perfil**, onde o jogador recebe dicas progressivas e precisa adivinhar personagens históricos, cientistas, artistas e inventores famosos!

---

## ✅ CHECKLIST - Requisitos Atendidos

### Recursos Implementados (Presentes nas 2 Cenas)

#### 1. ✅ Carregamento de Texturas
- **Menu**: Textura de fundo personalizada
- **Jogo**: Textura para ícones de feedback

#### 2. ✅ Exibição de Sprites
- **Menu**: Sprite de fundo
- **Jogo**: Sprite de feedback visual

#### 3. ✅ Definição de Shapes
- **Menu**: 
  - 3 Retângulos (botões: Jogar, Regras, Sair)
  - 3 Círculos (decoração visual)
  - 1 Retângulo (painel de regras)
- **Jogo**: 
  - 4 Retângulos (categoria, dicas, entrada, pontuação)
  - 5 Círculos (indicadores de dicas reveladas)

#### 4. ✅ Exibição de Shapes
- Todos os shapes são renderizados corretamente

#### 5. ✅ Definição de Textos
- **Menu**: Título, subtítulo, 3 botões, regras do jogo
- **Jogo**: Categoria, dicas, prompt, resposta digitada, pontuação, feedback, instruções

#### 6. ✅ Exibição de Textos
- Todos os textos são renderizados com formatação adequada

#### 7. ✅ Leitura de Inputs
- **Menu**: MOUSE (clique nos botões)
- **Jogo**: TECLADO (digitação, Space, Enter, ESC)

#### 8. ✅ Interação Baseada nos Inputs
- **Menu**: Botões mudam de cor ao passar o mouse, cliques navegam entre telas
- **Jogo**: Revelar dicas, digitar resposta, submeter resposta, voltar ao menu

#### 9. ✅ Lógica Completa
- **Menu**: Iniciar jogo, mostrar regras, sair
- **Jogo**: 
  - Revelar dicas progressivamente
  - Verificar resposta (case-insensitive)
  - Calcular pontuação dinâmica (menos dicas = mais pontos)
  - Avançar para próximo perfil
  - Sistema de feedback visual

#### 10. ✅ Mínimo 2 Cenas
- **Cena 1**: Menu Principal (com sub-cena de regras)
- **Cena 2**: Jogo Perfil

### 🎮 Inputs DIFERENTES em Cada Cena
- **Menu**: Usa **MOUSE** (cliques)
- **Jogo**: Usa **TECLADO** (letras, Space, Enter, ESC)

---

## 🎯 Como Jogar

### Menu Principal:
1. **Clique em "JOGAR"** para iniciar o jogo
2. **Clique em "COMO JOGAR"** para ver as regras
3. **Clique em "SAIR"** para fechar o programa
4. Observe os botões mudando de cor ao passar o mouse!

### Durante o Jogo:
1. Leia a **categoria** do perfil misterioso
2. Leia a primeira **dica** revelada
3. Pressione **ESPAÇO** para revelar mais dicas (se necessário)
4. **Digite sua resposta** quando achar que sabe quem é
5. Pressione **ENTER** para confirmar
6. Veja o feedback e sua pontuação!
7. Pressione **ESC** para voltar ao menu

### Sistema de Pontuação:
- **1 dica**: 100 pontos
- **2 dicas**: 80 pontos
- **3 dicas**: 60 pontos
- **4 dicas**: 40 pontos
- **5 dicas**: 20 pontos

*Quanto menos dicas usar, mais pontos você ganha!*

---

## 🛠️ Compilação

### Linux (Ubuntu/Debian):
```bash
# Instalar SFML
sudo apt-get update
sudo apt-get install libsfml-dev

# Compilar
g++ -std=c++11 perfil_game.cpp -o perfil -lsfml-graphics -lsfml-window -lsfml-system

# Executar
./perfil
```

### Windows (MinGW):
```bash
g++ -std=c++11 perfil_game.cpp -o perfil.exe -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -DSFML_STATIC

# Executar
perfil.exe
```

### CMake (Multiplataforma):
```cmake
cmake_minimum_required(VERSION 3.10)
project(PerfilGame)

set(CMAKE_CXX_STANDARD 11)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(perfil perfil_game.cpp)
target_link_libraries(perfil sfml-graphics sfml-window sfml-system)
```

```bash
mkdir build && cd build
cmake ..
make
./perfil
```

---

## 🎨 Perfis Incluídos

1. **Albert Einstein** (Cientista)
   - Físico teórico alemão
   - Criador da Teoria da Relatividade

2. **Leonardo da Vinci** (Artista)
   - Gênio do Renascimento
   - Pintor da Mona Lisa

3. **Santos Dumont** (Inventor)
   - Pioneiro brasileiro da aviação
   - Criador do 14-Bis

---

## 🚀 Como Personalizar

### Adicionar Novos Perfis:

No método `initializePerfis()` da classe `GameScene`, adicione:

```cpp
{
    "NOME DA PESSOA",  // Resposta correta
    {
        "Dica 1 sobre a pessoa",
        "Dica 2 sobre a pessoa",
        "Dica 3 sobre a pessoa",
        "Dica 4 sobre a pessoa",
        "Dica 5 sobre a pessoa"
    },
    "CATEGORIA"
}
```

### Exemplo - Adicionar Marie Curie:
```cpp
{
    "MARIE CURIE",
    {
        "Nasci na Polonia em 1867",
        "Fui cientista e fisica",
        "Ganhei dois Premios Nobel",
        "Descobri elementos radioativos",
        "Radio e Polonio foram meus descobertas"
    },
    "CIENTISTA"
}
```

---

## 💡 Melhorias Futuras (Se Tiver Tempo Extra)

1. **Categorias temáticas**: Histórico, Científico, Artístico, Esportivo
2. **Níveis de dificuldade**: Fácil, Médio, Difícil
3. **Modo multiplayer**: Jogadores alternados
4. **Sons**: Efeitos sonoros ao acertar/errar
5. **Animações**: Transições suaves entre telas
6. **Ranking**: Sistema de high scores
7. **Dica extra**: Sistema de ajuda (ex: primeiras letras)
8. **Timer**: Modo contra o tempo

---

## 📚 Recursos de Aprendizado

- **SFML Documentação**: https://www.sfml-dev.org/documentation/
- **Tutorial de Input de Texto**: https://www.sfml-dev.org/tutorials/2.5/window-events.php
- **Gerenciamento de Cenas**: https://github.com/SFML/SFML/wiki/Tutorial:-Manage-different-Screens
- **Exemplos SFML**: https://github.com/SFML/SFML/wiki/Projects

---

## 🐛 Troubleshooting

### Problema: Fonte não carrega
**Solução**: Altere o caminho da fonte:
- **Linux**: `/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf`
- **Windows**: `C:/Windows/Fonts/arial.ttf`
- **Alternativa**: Baixe uma fonte .ttf e coloque na pasta do projeto

### Problema: Acentos não funcionam
**Solução**: O código já possui tratamento básico de acentos na função `removeAccents()`. Para respostas, use caracteres sem acento.

### Problema: Não compila
**Solução**: Verifique se:
1. SFML está instalado
2. O compilador está no PATH
3. Flags de linkagem estão corretas

---

## 👨‍💻 Estrutura do Código

```
perfil_game.cpp
├── struct Perfil          // Estrutura de dados dos perfis
├── class MenuScene        // Gerencia o menu e regras
├── class GameScene        // Gerencia a mecânica do jogo
└── main()                 // Loop principal e controle de cenas
```

---

## ✨ Diferenciais do Projeto

✔️ Sistema de pontuação dinâmica  
✔️ Feedback visual imediato  
✔️ Interface intuitiva  
✔️ Indicadores visuais de progresso  
✔️ Tela de regras integrada  
✔️ Tratamento de input robusto  
✔️ Código bem comentado e organizado  

---

**Desenvolvido para disciplina de programação multimídia com SFML e C++**

Boa sorte no seu projeto! 🎓🚀

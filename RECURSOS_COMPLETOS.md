# 📚 RECURSOS E LINKS ÚTEIS - Projeto SFML

## 🔗 Repositórios de Referência

### 🎯 Projetos Completos para Estudar:

#### 1. Menu SFML Simples (ESSENCIAL!)
- **Link**: https://github.com/terroo/menu-sfml
- **O que tem**: Menu com mouse e teclado, navegação simples
- **Use para**: Estrutura do menu, detecção de clique
- **Código exemplo**: menu.cpp é muito didático

#### 2. Tutorial Oficial de Gerenciamento de Cenas (LEIA ISSO!)
- **Link**: https://github.com/SFML/SFML/wiki/Tutorial:-Manage-different-Screens
- **O que tem**: Sistema completo de troca de cenas
- **Use para**: Entender como alternar entre Menu/Jogo
- **Importante**: Base para qualquer jogo SFML

#### 3. 16 Jogos Simples em SFML
- **Link**: https://github.com/suraj95/16-Games-in-SFML
- **O que tem**: Tetris, Snake, Arkanoid, etc
- **Use para**: Ver diferentes mecânicas de jogo
- **Dica**: Compile alguns para ter inspiração

#### 4. Jogo 2D Simples com SFML
- **Link**: https://github.com/mataktelis/Simple-SFML-2D-Game
- **O que tem**: Projeto completo com sprites, texturas, inputs
- **Use para**: Estrutura de projeto profissional
- **Destaque**: Boa organização de código

#### 5. Tutorial de Engine Básica
- **Link**: https://github.com/SFML/SFML/wiki/Tutorial:-Basic-Game-Engine
- **O que tem**: Conceitos de namespace, estados, design patterns
- **Use para**: Entender arquitetura de jogos
- **Nível**: Intermediário

#### 6. Livro Oficial SFML Game Development
- **Link**: https://github.com/SFML/SFML-Game-Development-Book
- **O que tem**: Código completo dos capítulos do livro
- **Use para**: Referência profissional
- **Destaque**: Melhor prática em SFML

---

## 📖 Tutoriais e Documentação

### Documentação Oficial SFML:
- **Principal**: https://www.sfml-dev.org/documentation/2.5.1/
- **Tutoriais**: https://www.sfml-dev.org/tutorials/2.5/

### Tutoriais Específicos:

#### Eventos e Input:
- https://www.sfml-dev.org/tutorials/2.5/window-events.php
- Como capturar teclado, mouse, texto

#### Graphics e Sprites:
- https://www.sfml-dev.org/tutorials/2.5/graphics-sprite.php
- Texturas, sprites, transformações

#### Shapes:
- https://www.sfml-dev.org/tutorials/2.5/graphics-shape.php
- Círculos, retângulos, polígonos

#### Text e Fontes:
- https://www.sfml-dev.org/tutorials/2.5/graphics-text.php
- Como usar fontes e renderizar texto

---

## 🎮 Projetos Similares ao Perfil

### Jogos de Quiz/Adivinhação em SFML:

1. **Projetos SFML no GitHub**:
   - https://github.com/topics/sfml-game
   - Busque por "quiz", "trivia", "guessing"

2. **SFML Game Development Examples**:
   - https://github.com/topics/sfml-game-development
   - Vários exemplos educacionais

---

## 🛠️ Ferramentas e Recursos

### Fontes Gratuitas:
- **Google Fonts**: https://fonts.google.com/
- **DaFont**: https://www.dafont.com/
- **Font Squirrel**: https://www.fontsquirrel.com/

### Imagens e Sprites Gratuitos:
- **OpenGameArt**: https://opengameart.org/
- **Kenney Assets**: https://kenney.nl/assets
- **itch.io**: https://itch.io/game-assets/free

### Sons e Música (se quiser adicionar):
- **Freesound**: https://freesound.org/
- **OpenGameArt Audio**: https://opengameart.org/art-search-advanced?keys=&field_art_type_tid%5B%5D=13

---

## 💻 Setup e Instalação

### Tutoriais de Instalação SFML:

#### Windows:
- **Code::Blocks**: https://www.sfml-dev.org/tutorials/2.5/start-cb.php
- **Visual Studio**: https://www.sfml-dev.org/tutorials/2.5/start-vc.php
- **MinGW**: https://www.sfml-dev.org/tutorials/2.5/compile-with-cmake.php

#### Linux:
```bash
sudo apt-get install libsfml-dev
```
- **Tutorial completo**: https://www.sfml-dev.org/tutorials/2.5/start-linux.php

#### macOS:
- https://www.sfml-dev.org/tutorials/2.5/start-osx.php

---

## 🎓 Conceitos Importantes para Entender

### 1. Game Loop
```
while (window.isOpen()) {
    // 1. Processar eventos
    // 2. Atualizar lógica
    // 3. Renderizar
}
```

### 2. Event Handling
- **Mouse**: MouseButtonPressed, MouseMoved
- **Teclado**: KeyPressed, TextEntered
- **Janela**: Closed, Resized

### 3. Renderização
- **Ordem importa**: Primeiro desenhado = atrás
- **Clear antes**: Sempre limpar antes de desenhar
- **Display depois**: Sempre display após desenhar tudo

---

## 🐛 Problemas Comuns e Soluções

### Erro: "cannot find -lsfml-graphics"
**Solução**: SFML não está instalado ou no PATH
```bash
# Linux
sudo apt-get install libsfml-dev

# Verificar instalação
pkg-config --libs sfml-graphics
```

### Erro: Fonte não carrega
**Solução**: Caminho errado da fonte
```cpp
// Tente diferentes caminhos:
font.loadFromFile("arial.ttf");  // Pasta do projeto
font.loadFromFile("C:/Windows/Fonts/arial.ttf");  // Windows
font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");  // Linux
```

### Erro: Janela não abre
**Solução**: Problemas com drivers gráficos
```cpp
// Tente modo de compatibilidade:
sf::RenderWindow window(sf::VideoMode(800, 600), "Titulo", sf::Style::Default);
```

### Erro: Texto não aparece
**Solução**: Fonte não carregada ou cor igual ao fundo
```cpp
// Sempre verificar se carregou:
if (!font.loadFromFile("font.ttf")) {
    std::cerr << "ERRO: Fonte não carregou!" << std::endl;
}

// Verificar cor:
text.setFillColor(sf::Color::White);  // Não transparente!
```

---

## 📝 Snippets Úteis

### Criar Botão Clicável:
```cpp
sf::RectangleShape button(sf::Vector2f(200, 50));
button.setPosition(300, 200);

// No event loop:
if (event.type == sf::Event::MouseButtonPressed) {
    sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
    if (button.getGlobalBounds().contains(mousePos)) {
        // Clicou no botão!
    }
}
```

### Capturar Texto do Teclado:
```cpp
std::string text = "";

// No event loop:
if (event.type == sf::Event::TextEntered) {
    if (event.text.unicode < 128) {
        text += static_cast<char>(event.text.unicode);
    }
}

// Backspace:
if (event.type == sf::Event::KeyPressed) {
    if (event.key.code == sf::Keyboard::Backspace && !text.empty()) {
        text.pop_back();
    }
}
```

### Carregar Sprite:
```cpp
sf::Texture texture;
if (!texture.loadFromFile("image.png")) {
    std::cerr << "Erro ao carregar imagem!" << std::endl;
}

sf::Sprite sprite;
sprite.setTexture(texture);
sprite.setPosition(100, 100);

// No render loop:
window.draw(sprite);
```

---

## 🎨 Paletas de Cores Prontas

### Paleta 1 - Vibrante:
```cpp
sf::Color background(25, 25, 45);    // Azul escuro
sf::Color primary(0, 200, 255);      // Ciano
sf::Color secondary(255, 100, 100);  // Coral
sf::Color accent(255, 220, 0);       // Amarelo
```

### Paleta 2 - Profissional:
```cpp
sf::Color background(30, 30, 60);
sf::Color primary(50, 100, 200);
sf::Color secondary(200, 50, 50);
sf::Color accent(200, 150, 0);
```

### Paleta 3 - Suave:
```cpp
sf::Color background(240, 240, 245);
sf::Color primary(100, 150, 255);
sf::Color secondary(255, 150, 150);
sf::Color accent(150, 200, 100);
```

---

## 📊 Checklist de Desenvolvimento

### Dia 1: Setup
- [ ] SFML instalado e funcionando
- [ ] Janela básica abrindo
- [ ] Estrutura de arquivos criada
- [ ] Fonte testada e carregando

### Dia 2: Menu
- [ ] Sprite de fundo
- [ ] Botões com shapes
- [ ] Textos formatados
- [ ] Mouse funcionando
- [ ] Transição para jogo

### Dia 3: Jogo
- [ ] Lógica principal implementada
- [ ] Inputs do teclado funcionando
- [ ] Feedback visual
- [ ] Shapes e textos dinâmicos

### Dia 4: Polimento
- [ ] Cores ajustadas
- [ ] Posicionamento refinado
- [ ] Todos requisitos testados
- [ ] Código comentado
- [ ] README criado

---

## 🎯 Dicas Finais

### Para Impressionar o Professor:

1. **Comente o código**: Explique os requisitos
```cpp
// REQUISITO 1: Carregamento de textura
texture.loadFromFile("image.png");

// REQUISITO 7: Leitura de input (Mouse)
if (event.type == sf::Event::MouseButtonPressed) {
    // ...
}
```

2. **Organize bem**: Use classes separadas para cada cena

3. **README detalhado**: Explique como compilar e jogar

4. **Demonstre**: Grave um vídeo curto mostrando funcionando

5. **Backup**: Faça commits no GitHub durante o desenvolvimento

---

## 🆘 Precisa de Ajuda?

### Comunidades:

- **SFML Forum**: https://en.sfml-dev.org/forums/
- **Reddit r/SFML**: https://www.reddit.com/r/SFML/
- **Stack Overflow**: Tag [sfml]
- **Discord SFML**: https://discord.gg/nr4X7Fh

### Perguntas Frequentes:

**P: Posso usar código de exemplo?**
R: Sim, mas entenda e adapte! Professores percebem cópias.

**P: Quanto tempo leva para aprender SFML?**
R: Básico em 1 dia, intermediário em 1 semana.

**P: Preciso saber design patterns?**
R: Não para este projeto, mas ajuda.

**P: Posso usar C++11/14/17?**
R: Sim! C++11 é o mínimo recomendado.

---

## ✅ Você Está Pronto!

Com os códigos que criei (`perfil_game.cpp` ou `quiz_completo.cpp`) e estes recursos, você tem tudo que precisa!

**Boa sorte! 🚀**

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

enum class Scene {
    MENU,
    GAME
};

// ==================== CLASSE PERFIL ====================
struct Perfil {
    std::string resposta;
    std::vector<std::string> dicas;
    std::string categoria;
};

// ==================== CLASSE MENU ====================
class MenuScene {
private:
    sf::Font font;
    sf::Text title;
    sf::Text subtitle;
    sf::Text playButton;
    sf::Text rulesButton;
    sf::Text exitButton;
    sf::RectangleShape playBox;
    sf::RectangleShape rulesBox;
    sf::RectangleShape exitBox;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::CircleShape decoration1;
    sf::CircleShape decoration2;
    sf::CircleShape decoration3;
    
    // Estado para tela de regras
    bool showingRules;
    sf::Text rulesText;
    sf::Text backText;
    sf::RectangleShape rulesPanel;
    
public:
    MenuScene() {
        showingRules = false;
        
        // REQUISITO: Definição e exibição de textos
        if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) {
            if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
                std::cout << "Erro ao carregar fonte." << std::endl;
            }
        }
        
        // Título
        title.setFont(font);
        title.setString("PERFIL");
        title.setCharacterSize(80);
        title.setFillColor(sf::Color::Yellow);
        title.setPosition(280, 50);
        title.setOutlineColor(sf::Color::Black);
        title.setOutlineThickness(3);
        
        subtitle.setFont(font);
        subtitle.setString("O Jogo das Dicas");
        subtitle.setCharacterSize(25);
        subtitle.setFillColor(sf::Color::White);
        subtitle.setPosition(280, 140);
        
        // Botões
        playButton.setFont(font);
        playButton.setString("JOGAR");
        playButton.setCharacterSize(30);
        playButton.setFillColor(sf::Color::White);
        playButton.setPosition(330, 250);
        
        rulesButton.setFont(font);
        rulesButton.setString("COMO JOGAR");
        rulesButton.setCharacterSize(25);
        rulesButton.setFillColor(sf::Color::White);
        rulesButton.setPosition(290, 350);
        
        exitButton.setFont(font);
        exitButton.setString("SAIR");
        exitButton.setCharacterSize(25);
        exitButton.setFillColor(sf::Color::White);
        exitButton.setPosition(350, 450);
        
        // REQUISITO: Definição de Shapes (retângulos para botões)
        playBox.setSize(sf::Vector2f(200, 60));
        playBox.setPosition(310, 240);
        playBox.setFillColor(sf::Color(0, 150, 50));
        playBox.setOutlineColor(sf::Color::White);
        playBox.setOutlineThickness(3);
        
        rulesBox.setSize(sf::Vector2f(280, 60));
        rulesBox.setPosition(270, 340);
        rulesBox.setFillColor(sf::Color(50, 100, 200));
        rulesBox.setOutlineColor(sf::Color::White);
        rulesBox.setOutlineThickness(3);
        
        exitBox.setSize(sf::Vector2f(150, 60));
        exitBox.setPosition(330, 440);
        exitBox.setFillColor(sf::Color(200, 50, 50));
        exitBox.setOutlineColor(sf::Color::White);
        exitBox.setOutlineThickness(3);
        
        // REQUISITO: Definição de Shapes (círculos decorativos)
        decoration1.setRadius(40);
        decoration1.setFillColor(sf::Color(255, 100, 100, 180));
        decoration1.setPosition(50, 150);
        
        decoration2.setRadius(35);
        decoration2.setFillColor(sf::Color(100, 255, 100, 180));
        decoration2.setPosition(680, 200);
        
        decoration3.setRadius(30);
        decoration3.setFillColor(sf::Color(100, 100, 255, 180));
        decoration3.setPosition(120, 450);
        
        // REQUISITO: Carregamento de textura
        backgroundTexture.create(800, 600);
        sf::Uint8* pixels = new sf::Uint8[800 * 600 * 4];
        for (int i = 0; i < 800 * 600 * 4; i += 4) {
            pixels[i] = 20;
            pixels[i+1] = 20;
            pixels[i+2] = 40;
            pixels[i+3] = 255;
        }
        backgroundTexture.update(pixels);
        delete[] pixels;
        
        // REQUISITO: Exibição de Sprite
        backgroundSprite.setTexture(backgroundTexture);
        
        // Painel de regras
        rulesPanel.setSize(sf::Vector2f(700, 500));
        rulesPanel.setPosition(50, 50);
        rulesPanel.setFillColor(sf::Color(30, 30, 60, 240));
        rulesPanel.setOutlineColor(sf::Color::Yellow);
        rulesPanel.setOutlineThickness(5);
        
        rulesText.setFont(font);
        rulesText.setCharacterSize(22);
        rulesText.setFillColor(sf::Color::White);
        rulesText.setPosition(80, 80);
        rulesText.setString(
            "COMO JOGAR:\n\n"
            "1. Voce recebera dicas sobre um PERFIL misterioso\n\n"
            "2. A cada dica revelada, tente adivinhar QUEM E!\n\n"
            "3. Digite sua resposta e pressione ENTER\n\n"
            "4. Quanto MENOS dicas usar, MAIS pontos ganha!\n\n"
            "5. Use a tecla ESPACO para revelar a proxima dica\n\n"
            "6. Pressione ESC para voltar ao menu\n\n\n"
            "Boa sorte!"
        );
        
        backText.setFont(font);
        backText.setString("Clique para voltar");
        backText.setCharacterSize(20);
        backText.setFillColor(sf::Color::Yellow);
        backText.setPosition(280, 520);
    }
    
    // REQUISITO: Leitura de inputs (Mouse)
    Scene handleInput(sf::RenderWindow& window, sf::Event& event) {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePosF(static_cast<float>(mousePos.x), 
                                      static_cast<float>(mousePos.y));
                
                if (showingRules) {
                    // REQUISITO: Interação - voltar das regras
                    showingRules = false;
                    return Scene::MENU;
                }
                
                // REQUISITO: Interação baseada nos inputs
                if (playBox.getGlobalBounds().contains(mousePosF)) {
                    return Scene::GAME;
                }
                if (rulesBox.getGlobalBounds().contains(mousePosF)) {
                    showingRules = true;
                }
                if (exitBox.getGlobalBounds().contains(mousePosF)) {
                    window.close();
                }
            }
        }
        
        // Feedback visual ao passar mouse
        if (!showingRules) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f mousePosF(static_cast<float>(mousePos.x), 
                                  static_cast<float>(mousePos.y));
            
            if (playBox.getGlobalBounds().contains(mousePosF)) {
                playBox.setFillColor(sf::Color(0, 200, 70));
            } else {
                playBox.setFillColor(sf::Color(0, 150, 50));
            }
            
            if (rulesBox.getGlobalBounds().contains(mousePosF)) {
                rulesBox.setFillColor(sf::Color(70, 130, 255));
            } else {
                rulesBox.setFillColor(sf::Color(50, 100, 200));
            }
            
            if (exitBox.getGlobalBounds().contains(mousePosF)) {
                exitBox.setFillColor(sf::Color(255, 80, 80));
            } else {
                exitBox.setFillColor(sf::Color(200, 50, 50));
            }
        }
        
        return Scene::MENU;
    }
    
    // REQUISITO: Exibição de Sprites, Shapes e Textos
    void render(sf::RenderWindow& window) {
        window.draw(backgroundSprite);
        
        if (showingRules) {
            window.draw(rulesPanel);
            window.draw(rulesText);
            window.draw(backText);
        } else {
            window.draw(decoration1);
            window.draw(decoration2);
            window.draw(decoration3);
            window.draw(playBox);
            window.draw(rulesBox);
            window.draw(exitBox);
            window.draw(title);
            window.draw(subtitle);
            window.draw(playButton);
            window.draw(rulesButton);
            window.draw(exitButton);
        }
    }
};

// ==================== CLASSE JOGO ====================
class GameScene {
private:
    sf::Font font;
    sf::Text categoryText;
    sf::Text clueText;
    sf::Text inputPrompt;
    sf::Text userInput;
    sf::Text scoreText;
    sf::Text feedbackText;
    sf::Text instructionText;
    
    sf::RectangleShape categoryBox;
    sf::RectangleShape clueBox;
    sf::RectangleShape inputBox;
    sf::RectangleShape scoreBar;
    
    sf::CircleShape clueIndicator1;
    sf::CircleShape clueIndicator2;
    sf::CircleShape clueIndicator3;
    sf::CircleShape clueIndicator4;
    sf::CircleShape clueIndicator5;
    
    sf::Texture iconTexture;
    sf::Sprite iconSprite;
    
    std::vector<Perfil> perfis;
    int currentPerfil;
    int currentClue;
    int score;
    std::string playerAnswer;
    bool showingFeedback;
    sf::Clock feedbackClock;
    bool gameWon;
    
    void initializePerfis() {
        perfis = {
            {
                "ALBERT EINSTEIN",
                {
                    "Nasci na Alemanha em 1879",
                    "Fui um fisico teorico",
                    "Ganhei o Premio Nobel de Fisica",
                    "Criei a teoria da relatividade",
                    "E = mc² e minha equacao famosa"
                },
                "CIENTISTA"
            },
            {
                "LEONARDO DA VINCI",
                {
                    "Vivi durante o Renascimento",
                    "Fui pintor, inventor e cientista",
                    "Pintei a Mona Lisa",
                    "Estudei anatomia e engenharia",
                    "Desenhei maquinas voadoras"
                },
                "ARTISTA"
            },
            {
                "SANTOS DUMONT",
                {
                    "Nasci no Brasil em 1873",
                    "Fui pioneiro da aviacao",
                    "Vivi grande parte da vida na Franca",
                    "Inventei o relogio de pulso para pilotos",
                    "Voei o 14-Bis em Paris"
                },
                "INVENTOR"
            }
        };
    }
    
    std::string toUpperCase(std::string str) {
        std::transform(str.begin(), str.end(), str.begin(), ::toupper);
        return str;
    }
    
    std::string removeAccents(std::string str) {
        // Simplificação: remover acentos comuns
        std::string result = str;
        size_t pos;
        while ((pos = result.find("Ã")) != std::string::npos) result.replace(pos, 2, "A");
        while ((pos = result.find("Á")) != std::string::npos) result.replace(pos, 2, "A");
        while ((pos = result.find("É")) != std::string::npos) result.replace(pos, 2, "E");
        while ((pos = result.find("Í")) != std::string::npos) result.replace(pos, 2, "I");
        while ((pos = result.find("Ó")) != std::string::npos) result.replace(pos, 2, "O");
        while ((pos = result.find("Ú")) != std::string::npos) result.replace(pos, 2, "U");
        return result;
    }
    
public:
    GameScene() {
        if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
            std::cout << "Erro ao carregar fonte." << std::endl;
        }
        
        initializePerfis();
        currentPerfil = 0;
        currentClue = 0;
        score = 0;
        playerAnswer = "";
        showingFeedback = false;
        gameWon = false;
        
        // Configurar textos
        categoryText.setFont(font);
        categoryText.setCharacterSize(30);
        categoryText.setFillColor(sf::Color::Yellow);
        categoryText.setPosition(50, 30);
        
        clueText.setFont(font);
        clueText.setCharacterSize(24);
        clueText.setFillColor(sf::Color::White);
        clueText.setPosition(70, 150);
        
        inputPrompt.setFont(font);
        inputPrompt.setString("Sua resposta:");
        inputPrompt.setCharacterSize(22);
        inputPrompt.setFillColor(sf::Color::White);
        inputPrompt.setPosition(50, 450);
        
        userInput.setFont(font);
        userInput.setCharacterSize(24);
        userInput.setFillColor(sf::Color::Yellow);
        userInput.setPosition(70, 490);
        
        scoreText.setFont(font);
        scoreText.setCharacterSize(28);
        scoreText.setFillColor(sf::Color::Yellow);
        scoreText.setPosition(600, 30);
        
        feedbackText.setFont(font);
        feedbackText.setCharacterSize(36);
        feedbackText.setPosition(250, 350);
        
        instructionText.setFont(font);
        instructionText.setString("ESPACO: Proxima dica | ENTER: Enviar | ESC: Menu");
        instructionText.setCharacterSize(16);
        instructionText.setFillColor(sf::Color(200, 200, 200));
        instructionText.setPosition(150, 570);
        
        // REQUISITO: Definição de Shapes (retângulos)
        categoryBox.setSize(sf::Vector2f(250, 50));
        categoryBox.setPosition(40, 20);
        categoryBox.setFillColor(sf::Color(80, 50, 120));
        categoryBox.setOutlineColor(sf::Color::Yellow);
        categoryBox.setOutlineThickness(2);
        
        clueBox.setSize(sf::Vector2f(700, 250));
        clueBox.setPosition(50, 100);
        clueBox.setFillColor(sf::Color(40, 40, 80, 200));
        clueBox.setOutlineColor(sf::Color::Cyan);
        clueBox.setOutlineThickness(3);
        
        inputBox.setSize(sf::Vector2f(700, 80));
        inputBox.setPosition(50, 440);
        inputBox.setFillColor(sf::Color(50, 50, 50));
        inputBox.setOutlineColor(sf::Color::White);
        inputBox.setOutlineThickness(2);
        
        scoreBar.setSize(sf::Vector2f(150, 50));
        scoreBar.setPosition(590, 20);
        scoreBar.setFillColor(sf::Color(200, 150, 0));
        scoreBar.setOutlineColor(sf::Color::White);
        scoreBar.setOutlineThickness(2);
        
        // REQUISITO: Definição de Shapes (círculos - indicadores de dicas)
        float startX = 60;
        float startY = 380;
        float spacing = 40;
        
        clueIndicator1.setRadius(15);
        clueIndicator1.setPosition(startX, startY);
        clueIndicator1.setFillColor(sf::Color(100, 100, 100));
        
        clueIndicator2.setRadius(15);
        clueIndicator2.setPosition(startX + spacing, startY);
        clueIndicator2.setFillColor(sf::Color(100, 100, 100));
        
        clueIndicator3.setRadius(15);
        clueIndicator3.setPosition(startX + spacing * 2, startY);
        clueIndicator3.setFillColor(sf::Color(100, 100, 100));
        
        clueIndicator4.setRadius(15);
        clueIndicator4.setPosition(startX + spacing * 3, startY);
        clueIndicator4.setFillColor(sf::Color(100, 100, 100));
        
        clueIndicator5.setRadius(15);
        clueIndicator5.setPosition(startX + spacing * 4, startY);
        clueIndicator5.setFillColor(sf::Color(100, 100, 100));
        
        // REQUISITO: Criar textura para ícone
        iconTexture.create(50, 50);
        iconSprite.setTexture(iconTexture);
        iconSprite.setPosition(200, 350);
        
        updateDisplay();
    }
    
    void updateDisplay() {
        if (currentPerfil < perfis.size()) {
            categoryText.setString("Categoria: " + perfis[currentPerfil].categoria);
            
            std::string cluesText = "";
            for (int i = 0; i <= currentClue && i < perfis[currentPerfil].dicas.size(); i++) {
                cluesText += "Dica " + std::to_string(i + 1) + ": " + 
                           perfis[currentPerfil].dicas[i] + "\n\n";
            }
            clueText.setString(cluesText);
            
            scoreText.setString("Score: " + std::to_string(score));
            userInput.setString("> " + playerAnswer);
            
            // Atualizar indicadores de dicas
            std::vector<sf::CircleShape*> indicators = {
                &clueIndicator1, &clueIndicator2, &clueIndicator3, 
                &clueIndicator4, &clueIndicator5
            };
            
            for (int i = 0; i < indicators.size(); i++) {
                if (i <= currentClue) {
                    indicators[i]->setFillColor(sf::Color(0, 200, 255));
                } else {
                    indicators[i]->setFillColor(sf::Color(100, 100, 100));
                }
            }
        }
    }
    
    void checkAnswer() {
        std::string normalizedAnswer = removeAccents(toUpperCase(playerAnswer));
        std::string normalizedCorrect = removeAccents(perfis[currentPerfil].resposta);
        
        // REQUISITO: Lógica (verificar resposta)
        if (normalizedAnswer == normalizedCorrect) {
            // Correto! Calcular pontuação
            int points = (5 - currentClue) * 20;
            score += points;
            feedbackText.setString("CORRETO! +" + std::to_string(points) + " pontos!");
            feedbackText.setFillColor(sf::Color::Green);
            gameWon = true;
        } else {
            feedbackText.setString("ERRADO! Era: " + perfis[currentPerfil].resposta);
            feedbackText.setFillColor(sf::Color::Red);
            gameWon = false;
        }
        
        showingFeedback = true;
        feedbackClock.restart();
    }
    
    void nextProfile() {
        currentPerfil++;
        if (currentPerfil >= perfis.size()) {
            currentPerfil = 0;
            score = 0;
        }
        currentClue = 0;
        playerAnswer = "";
        updateDisplay();
    }
    
    // REQUISITO: Leitura de inputs (Teclado - diferente do menu)
    Scene handleInput(sf::Event& event) {
        if (showingFeedback) {
            if (feedbackClock.getElapsedTime().asSeconds() > 2.5f) {
                showingFeedback = false;
                nextProfile();
            }
            return Scene::GAME;
        }
        
        // REQUISITO: Interação baseada nos inputs (Teclado)
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                // Resetar jogo e voltar ao menu
                currentPerfil = 0;
                currentClue = 0;
                score = 0;
                playerAnswer = "";
                updateDisplay();
                return Scene::MENU;
            }
            
            // REQUISITO: Lógica (revelar próxima dica)
            if (event.key.code == sf::Keyboard::Space) {
                if (currentClue < perfis[currentPerfil].dicas.size() - 1) {
                    currentClue++;
                    updateDisplay();
                }
            }
            
            if (event.key.code == sf::Keyboard::Enter) {
                if (!playerAnswer.empty()) {
                    checkAnswer();
                }
            }
            
            if (event.key.code == sf::Keyboard::Backspace) {
                if (!playerAnswer.empty()) {
                    playerAnswer.pop_back();
                    updateDisplay();
                }
            }
        }
        
        // Capturar texto digitado
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode < 128 && event.text.unicode != 13 && 
                event.text.unicode != 8) {
                playerAnswer += static_cast<char>(event.text.unicode);
                updateDisplay();
            }
        }
        
        return Scene::GAME;
    }
    
    // REQUISITO: Exibição de Sprites, Shapes e Textos
    void render(sf::RenderWindow& window) {
        // Fundo gradiente
        sf::RectangleShape background(sf::Vector2f(800, 600));
        background.setFillColor(sf::Color(25, 25, 45));
        window.draw(background);
        
        window.draw(categoryBox);
        window.draw(clueBox);
        window.draw(inputBox);
        window.draw(scoreBar);
        
        window.draw(clueIndicator1);
        window.draw(clueIndicator2);
        window.draw(clueIndicator3);
        window.draw(clueIndicator4);
        window.draw(clueIndicator5);
        
        window.draw(categoryText);
        window.draw(clueText);
        window.draw(inputPrompt);
        window.draw(userInput);
        window.draw(scoreText);
        window.draw(instructionText);
        
        if (showingFeedback) {
            sf::RectangleShape overlay(sf::Vector2f(800, 600));
            overlay.setFillColor(sf::Color(0, 0, 0, 150));
            window.draw(overlay);
            window.draw(feedbackText);
        }
    }
};

// ==================== MAIN ====================
int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "PERFIL - Jogo das Dicas");
    window.setFramerateLimit(60);
    
    Scene currentScene = Scene::MENU;
    MenuScene menu;
    GameScene game;
    
    // REQUISITO: Lógica (controle de cenas - parar, iniciar, mudar)
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            
            if (currentScene == Scene::MENU) {
                currentScene = menu.handleInput(window, event);
            } else if (currentScene == Scene::GAME) {
                currentScene = game.handleInput(event);
            }
        }
        
        window.clear();
        
        if (currentScene == Scene::MENU) {
            menu.render(window);
        } else if (currentScene == Scene::GAME) {
            game.render(window);
        }
        
        window.display();
    }
    
    return 0;
}

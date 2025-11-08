#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

enum class Scene {
    MENU,
    QUIZ
};

// ==================== CLASSE MENU ====================
class MenuScene {
private:
    sf::Font font;
    sf::Text title;
    sf::Text startButton;
    sf::Text exitButton;
    sf::RectangleShape startBox;
    sf::RectangleShape exitBox;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::CircleShape decoration1;
    sf::CircleShape decoration2;
    
public:
    MenuScene() {
        // Carregar fonte (REQUISITO: Definição e exibição de textos)
        if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
            std::cout << "Erro ao carregar fonte. Usando fonte padrão." << std::endl;
        }
        
        // Título
        title.setFont(font);
        title.setString("QUIZ EDUCACIONAL");
        title.setCharacterSize(50);
        title.setFillColor(sf::Color::White);
        title.setPosition(200, 50);
        
        // Botão Iniciar
        startButton.setFont(font);
        startButton.setString("INICIAR QUIZ");
        startButton.setCharacterSize(30);
        startButton.setFillColor(sf::Color::White);
        startButton.setPosition(300, 250);
        
        // Botão Sair
        exitButton.setFont(font);
        exitButton.setString("SAIR");
        exitButton.setCharacterSize(30);
        exitButton.setFillColor(sf::Color::White);
        exitButton.setPosition(350, 350);
        
        // REQUISITO: Definição de Shapes (retângulos)
        startBox.setSize(sf::Vector2f(250, 60));
        startBox.setPosition(280, 240);
        startBox.setFillColor(sf::Color(0, 100, 200));
        startBox.setOutlineColor(sf::Color::White);
        startBox.setOutlineThickness(2);
        
        exitBox.setSize(sf::Vector2f(150, 60));
        exitBox.setPosition(330, 340);
        exitBox.setFillColor(sf::Color(200, 50, 50));
        exitBox.setOutlineColor(sf::Color::White);
        exitBox.setOutlineThickness(2);
        
        // REQUISITO: Definição de Shapes (círculos)
        decoration1.setRadius(30);
        decoration1.setFillColor(sf::Color(255, 200, 0, 150));
        decoration1.setPosition(100, 200);
        
        decoration2.setRadius(40);
        decoration2.setFillColor(sf::Color(100, 255, 100, 150));
        decoration2.setPosition(650, 400);
        
        // REQUISITO: Carregamento de textura (criar uma textura simples)
        backgroundTexture.create(800, 600);
        sf::Uint8* pixels = new sf::Uint8[800 * 600 * 4];
        for (int i = 0; i < 800 * 600 * 4; i += 4) {
            pixels[i] = 20;     // R
            pixels[i+1] = 30;   // G
            pixels[i+2] = 50;   // B
            pixels[i+3] = 255;  // A
        }
        backgroundTexture.update(pixels);
        delete[] pixels;
        
        // REQUISITO: Exibição de Sprite
        backgroundSprite.setTexture(backgroundTexture);
    }
    
    // REQUISITO: Leitura de inputs (Mouse)
    Scene handleInput(sf::RenderWindow& window, sf::Event& event) {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePosF(static_cast<float>(mousePos.x), 
                                      static_cast<float>(mousePos.y));
                
                // REQUISITO: Interação baseada nos inputs
                if (startBox.getGlobalBounds().contains(mousePosF)) {
                    return Scene::QUIZ;
                }
                if (exitBox.getGlobalBounds().contains(mousePosF)) {
                    window.close();
                }
            }
        }
        
        // Feedback visual ao passar mouse
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosF(static_cast<float>(mousePos.x), 
                              static_cast<float>(mousePos.y));
        
        if (startBox.getGlobalBounds().contains(mousePosF)) {
            startBox.setFillColor(sf::Color(0, 150, 255));
        } else {
            startBox.setFillColor(sf::Color(0, 100, 200));
        }
        
        if (exitBox.getGlobalBounds().contains(mousePosF)) {
            exitBox.setFillColor(sf::Color(255, 80, 80));
        } else {
            exitBox.setFillColor(sf::Color(200, 50, 50));
        }
        
        return Scene::MENU;
    }
    
    // REQUISITO: Exibição de Sprites, Shapes e Textos
    void render(sf::RenderWindow& window) {
        window.draw(backgroundSprite);
        window.draw(decoration1);
        window.draw(decoration2);
        window.draw(startBox);
        window.draw(exitBox);
        window.draw(title);
        window.draw(startButton);
        window.draw(exitButton);
    }
};

// ==================== CLASSE QUIZ ====================
class QuizScene {
private:
    sf::Font font;
    sf::Text questionText;
    sf::Text option1, option2, option3, option4;
    sf::Text scoreText;
    sf::Text feedbackText;
    sf::RectangleShape questionBox;
    sf::CircleShape optionCircle1, optionCircle2, optionCircle3, optionCircle4;
    sf::RectangleShape scoreBar;
    sf::Texture iconTexture;
    sf::Sprite feedbackSprite;
    
    int currentQuestion;
    int score;
    std::vector<std::string> questions;
    std::vector<std::vector<std::string>> options;
    std::vector<int> correctAnswers;
    bool showingFeedback;
    sf::Clock feedbackClock;
    
public:
    QuizScene() {
        // Carregar fonte
        if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
            std::cout << "Erro ao carregar fonte." << std::endl;
        }
        
        currentQuestion = 0;
        score = 0;
        showingFeedback = false;
        
        // PERGUNTAS DO QUIZ
        questions = {
            "Qual é a capital do Brasil?",
            "Quanto é 5 + 7?",
            "Qual linguagem usamos neste projeto?"
        };
        
        options = {
            {"1. São Paulo", "2. Rio de Janeiro", "3. Brasília", "4. Salvador"},
            {"1. 10", "2. 11", "3. 12", "4. 13"},
            {"1. Python", "2. C++", "3. Java", "4. JavaScript"}
        };
        
        correctAnswers = {3, 3, 2}; // Respostas corretas (1-4)
        
        // Configurar textos
        questionText.setFont(font);
        questionText.setCharacterSize(28);
        questionText.setFillColor(sf::Color::White);
        questionText.setPosition(50, 80);
        
        option1.setFont(font);
        option1.setCharacterSize(24);
        option1.setPosition(150, 200);
        
        option2.setFont(font);
        option2.setCharacterSize(24);
        option2.setPosition(150, 270);
        
        option3.setFont(font);
        option3.setCharacterSize(24);
        option3.setPosition(150, 340);
        
        option4.setFont(font);
        option4.setCharacterSize(24);
        option4.setPosition(150, 410);
        
        scoreText.setFont(font);
        scoreText.setCharacterSize(30);
        scoreText.setFillColor(sf::Color::Yellow);
        scoreText.setPosition(600, 30);
        
        feedbackText.setFont(font);
        feedbackText.setCharacterSize(40);
        feedbackText.setFillColor(sf::Color::Green);
        feedbackText.setPosition(300, 500);
        
        // REQUISITO: Definição de Shapes (retângulo para pergunta)
        questionBox.setSize(sf::Vector2f(700, 80));
        questionBox.setPosition(50, 70);
        questionBox.setFillColor(sf::Color(50, 50, 100, 200));
        questionBox.setOutlineColor(sf::Color::Cyan);
        questionBox.setOutlineThickness(3);
        
        // REQUISITO: Definição de Shapes (círculos para opções)
        optionCircle1.setRadius(25);
        optionCircle1.setFillColor(sf::Color(100, 100, 200));
        optionCircle1.setPosition(100, 200);
        
        optionCircle2.setRadius(25);
        optionCircle2.setFillColor(sf::Color(100, 100, 200));
        optionCircle2.setPosition(100, 270);
        
        optionCircle3.setRadius(25);
        optionCircle3.setFillColor(sf::Color(100, 100, 200));
        optionCircle3.setPosition(100, 340);
        
        optionCircle4.setRadius(25);
        optionCircle4.setFillColor(sf::Color(100, 100, 200));
        optionCircle4.setPosition(100, 410);
        
        // REQUISITO: Shape para barra de pontuação
        scoreBar.setSize(sf::Vector2f(150, 40));
        scoreBar.setPosition(590, 20);
        scoreBar.setFillColor(sf::Color(200, 150, 0));
        scoreBar.setOutlineColor(sf::Color::White);
        scoreBar.setOutlineThickness(2);
        
        // REQUISITO: Criar textura para feedback
        iconTexture.create(50, 50);
        feedbackSprite.setTexture(iconTexture);
        feedbackSprite.setPosition(250, 500);
        
        updateQuestion();
    }
    
    void updateQuestion() {
        if (currentQuestion < questions.size()) {
            questionText.setString(questions[currentQuestion]);
            option1.setString(options[currentQuestion][0]);
            option2.setString(options[currentQuestion][1]);
            option3.setString(options[currentQuestion][2]);
            option4.setString(options[currentQuestion][3]);
            scoreText.setString("Score: " + std::to_string(score));
        }
    }
    
    // REQUISITO: Leitura de inputs (Teclado - diferente do menu que usa mouse)
    Scene handleInput(sf::Event& event) {
        if (showingFeedback) {
            if (feedbackClock.getElapsedTime().asSeconds() > 1.5f) {
                showingFeedback = false;
                currentQuestion++;
                
                if (currentQuestion >= questions.size()) {
                    // Quiz finalizado, volta para o menu
                    currentQuestion = 0;
                    score = 0;
                    updateQuestion();
                    return Scene::MENU;
                }
                updateQuestion();
            }
            return Scene::QUIZ;
        }
        
        // REQUISITO: Interação baseada nos inputs
        if (event.type == sf::Event::KeyPressed) {
            int answer = 0;
            
            // Teclas numéricas ou Numpad
            if (event.key.code == sf::Keyboard::Num1 || 
                event.key.code == sf::Keyboard::Numpad1) answer = 1;
            else if (event.key.code == sf::Keyboard::Num2 || 
                     event.key.code == sf::Keyboard::Numpad2) answer = 2;
            else if (event.key.code == sf::Keyboard::Num3 || 
                     event.key.code == sf::Keyboard::Numpad3) answer = 3;
            else if (event.key.code == sf::Keyboard::Num4 || 
                     event.key.code == sf::Keyboard::Numpad4) answer = 4;
            else if (event.key.code == sf::Keyboard::Escape) {
                // Voltar ao menu
                currentQuestion = 0;
                score = 0;
                updateQuestion();
                return Scene::MENU;
            }
            
            // REQUISITO: Lógica (verificar resposta)
            if (answer > 0) {
                if (answer == correctAnswers[currentQuestion]) {
                    score += 10;
                    feedbackText.setString("CORRETO!");
                    feedbackText.setFillColor(sf::Color::Green);
                } else {
                    feedbackText.setString("ERRADO!");
                    feedbackText.setFillColor(sf::Color::Red);
                }
                showingFeedback = true;
                feedbackClock.restart();
            }
        }
        
        return Scene::QUIZ;
    }
    
    // REQUISITO: Exibição de Sprites, Shapes e Textos
    void render(sf::RenderWindow& window) {
        // Desenhar fundo gradiente
        sf::RectangleShape background(sf::Vector2f(800, 600));
        background.setFillColor(sf::Color(30, 30, 60));
        window.draw(background);
        
        // Desenhar elementos
        window.draw(scoreBar);
        window.draw(questionBox);
        window.draw(optionCircle1);
        window.draw(optionCircle2);
        window.draw(optionCircle3);
        window.draw(optionCircle4);
        window.draw(questionText);
        window.draw(option1);
        window.draw(option2);
        window.draw(option3);
        window.draw(option4);
        window.draw(scoreText);
        
        if (showingFeedback) {
            window.draw(feedbackText);
        }
        
        // Instrução
        sf::Text instruction;
        instruction.setFont(font);
        instruction.setString("Pressione 1-4 para responder | ESC para voltar");
        instruction.setCharacterSize(18);
        instruction.setFillColor(sf::Color(200, 200, 200));
        instruction.setPosition(200, 550);
        window.draw(instruction);
    }
};

// ==================== MAIN ====================
int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Quiz Educacional - Projeto SFML");
    window.setFramerateLimit(60);
    
    Scene currentScene = Scene::MENU;
    MenuScene menu;
    QuizScene quiz;
    
    // REQUISITO: Lógica (controle de cenas)
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            
            // Processar input baseado na cena
            if (currentScene == Scene::MENU) {
                currentScene = menu.handleInput(window, event);
            } else if (currentScene == Scene::QUIZ) {
                currentScene = quiz.handleInput(event);
            }
        }
        
        window.clear();
        
        // Renderizar cena atual
        if (currentScene == Scene::MENU) {
            menu.render(window);
        } else if (currentScene == Scene::QUIZ) {
            quiz.render(window);
        }
        
        window.display();
    }
    
    return 0;
}

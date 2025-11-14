#include "Scenes/MenuScene.hpp"
#include "Utils/FontManager.hpp"
#include "Utils/Utf.hpp"
#include "Utils/Colors.hpp"
#include "Config.hpp"
#include <cmath>

MenuScene::MenuScene() 
    : titleText(FontManager::getInstance().getFont(FontManager::FontType::Title))
    , subtitleText(FontManager::getInstance().getFont(FontManager::FontType::Regular))
    , quizButtonText(FontManager::getInstance().getFont(FontManager::FontType::Bold))
    , faceButtonText(FontManager::getInstance().getFont(FontManager::FontType::Bold))
    , exitButtonText(FontManager::getInstance().getFont(FontManager::FontType::Bold))
    , instructionText(FontManager::getInstance().getFont(FontManager::FontType::Regular))
    , currentHover(HoveredButton::None)
    , animationTime(0.0f) {
    setupTexts();
    setupButtons();
    setupDecorations();
}

void MenuScene::setupTexts() {
    // Título principal
    titleText.setString(Utf::toSf("FACE"));
    titleText.setCharacterSize(120);
    titleText.setFillColor(Colors::Yellow);
    titleText.setOutlineColor(Colors::Orange);
    titleText.setOutlineThickness(4);
    titleText.setPosition(sf::Vector2f(360.f, 80.f));
    
    // Subtítulo
    subtitleText.setString(Utf::toSf("O Jogo das Dicas"));
    subtitleText.setCharacterSize(32);
    subtitleText.setFillColor(Colors::Green);
    subtitleText.setPosition(sf::Vector2f(345.f, 200.f));
    
    // Botão Quiz
    quizButtonText.setString(Utf::toSf("QUIZ"));
    quizButtonText.setCharacterSize(36);
    quizButtonText.setFillColor(Colors::TextPrimary);
    quizButtonText.setPosition(sf::Vector2f(430.f, 305.f));
    
    // Botão Face
    faceButtonText.setString(Utf::toSf("FACE"));
    faceButtonText.setCharacterSize(36);
    faceButtonText.setFillColor(Colors::TextPrimary);
    faceButtonText.setPosition(sf::Vector2f(430.f, 415.f));
    
    // Botão Sair
    exitButtonText.setString(Utf::toSf("SAIR"));
    exitButtonText.setCharacterSize(36);
    exitButtonText.setFillColor(Colors::TextPrimary);
    exitButtonText.setPosition(sf::Vector2f(445.f, 525.f));
    
    // Instrução
    instructionText.setString(Utf::toSf("Clique para selecionar o modo de jogo"));
    instructionText.setCharacterSize(20);
    instructionText.setFillColor(Colors::TextSecondary);
    instructionText.setPosition(sf::Vector2f(320.f, 640.f));
}

void MenuScene::setupButtons() {
    // Botão Quiz
    quizButton.setSize(sf::Vector2f(280.f, 70.f));
    quizButton.setPosition(sf::Vector2f(360.f, 295.f));
    quizButton.setFillColor(Colors::Navy);
    quizButton.setOutlineColor(Colors::Border);
    quizButton.setOutlineThickness(3.f);
    
    // Botão Face
    faceButton.setSize(sf::Vector2f(280.f, 70.f));
    faceButton.setPosition(sf::Vector2f(360.f, 405.f));
    faceButton.setFillColor(Colors::Navy);
    faceButton.setOutlineColor(Colors::Border);
    faceButton.setOutlineThickness(3.f);
    
    // Botão Sair
    exitButton.setSize(sf::Vector2f(280.f, 70.f));
    exitButton.setPosition(sf::Vector2f(360.f, 515.f));
    exitButton.setFillColor(Colors::Navy);
    exitButton.setOutlineColor(Colors::Border);
    exitButton.setOutlineThickness(3.f);
}

void MenuScene::setupDecorations() {
    // Fundo gradiente
    backgroundGradient.setSize(sf::Vector2f(static_cast<float>(Config::WINDOW_WIDTH), static_cast<float>(Config::WINDOW_HEIGHT)));
    backgroundGradient.setPosition(sf::Vector2f(0.f, 0.f));
    backgroundGradient.setFillColor(Colors::Background);
    
    // Círculos decorativos animados
    decorations.clear();
    
    // Círculo 1 - Amarelo
    sf::CircleShape deco1(50.f);
    deco1.setFillColor(Colors::DecoYellow);
    deco1.setPosition(sf::Vector2f(80.f, 250.f));
    decorations.push_back(deco1);
    
    // Círculo 2 - Laranja
    sf::CircleShape deco2(60.f);
    deco2.setFillColor(Colors::DecoOrange);
    deco2.setPosition(sf::Vector2f(820.f, 150.f));
    decorations.push_back(deco2);
    
    // Círculo 3 - Verde
    sf::CircleShape deco3(45.f);
    deco3.setFillColor(Colors::DecoGreen);
    deco3.setPosition(sf::Vector2f(120.f, 500.f));
    decorations.push_back(deco3);
    
    // Círculo 4 - Amarelo menor
    sf::CircleShape deco4(35.f);
    deco4.setFillColor(Colors::DecoYellow);
    deco4.setPosition(sf::Vector2f(850.f, 480.f));
    decorations.push_back(deco4);
}

void MenuScene::updateButtonStates(const sf::Vector2f& mousePos) {
    HoveredButton newHover = HoveredButton::None;
    
    // Verificar hover em cada botão
    if (quizButton.getGlobalBounds().contains(mousePos)) {
        newHover = HoveredButton::Quiz;
    } else if (faceButton.getGlobalBounds().contains(mousePos)) {
        newHover = HoveredButton::Face;
    } else if (exitButton.getGlobalBounds().contains(mousePos)) {
        newHover = HoveredButton::Exit;
    }
    
    // Atualizar cores dos botões
    quizButton.setFillColor(newHover == HoveredButton::Quiz ? Colors::NavyHover : Colors::Navy);
    faceButton.setFillColor(newHover == HoveredButton::Face ? Colors::NavyHover : Colors::Navy);
    exitButton.setFillColor(newHover == HoveredButton::Exit ? Colors::NavyHover : Colors::Navy);
    
    // Atualizar bordas
    quizButton.setOutlineColor(newHover == HoveredButton::Quiz ? Colors::BorderActive : Colors::Border);
    faceButton.setOutlineColor(newHover == HoveredButton::Face ? Colors::BorderActive : Colors::Border);
    exitButton.setOutlineColor(newHover == HoveredButton::Exit ? Colors::BorderActive : Colors::Border);
    
    currentHover = newHover;
}

void MenuScene::handleButtonClick(const sf::Vector2f& mousePos) {
    if (quizButton.getGlobalBounds().contains(mousePos)) {
        // Ir para Quiz
    } else if (faceButton.getGlobalBounds().contains(mousePos)) {
        // Ir para Face
    } else if (exitButton.getGlobalBounds().contains(mousePos)) {
        // Sair
    }
}

void MenuScene::animateDecorations(float deltaTime) {
    animationTime += deltaTime;
    
    // Animar círculos decorativos com movimento flutuante
    for (size_t i = 0; i < decorations.size(); ++i) {
        float offset = std::sin(animationTime * (1.0f + i * 0.3f)) * 10.0f;
        sf::Vector2f originalPos;
        
        switch (i) {
            case 0: originalPos = sf::Vector2f(80.f, 250.f); break;
            case 1: originalPos = sf::Vector2f(820.f, 150.f); break;
            case 2: originalPos = sf::Vector2f(120.f, 500.f); break;
            case 3: originalPos = sf::Vector2f(850.f, 480.f); break;
        }
        
        decorations[i].setPosition(sf::Vector2f(originalPos.x, originalPos.y + offset));
    }
}

SceneType MenuScene::handleInput(const sf::Event& event) {
    if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
            sf::Vector2f mousePos(
                static_cast<float>(mouseButtonPressed->position.x),
                static_cast<float>(mouseButtonPressed->position.y)
            );
            
            if (quizButton.getGlobalBounds().contains(mousePos)) {
                return SceneType::Quiz;
            } else if (faceButton.getGlobalBounds().contains(mousePos)) {
                return SceneType::Face;
            } else if (exitButton.getGlobalBounds().contains(mousePos)) {
                return SceneType::Exit;
            }
        }
    }
    
    return SceneType::Menu;
}

void MenuScene::update(float deltaTime) {
    // Atualizar animações
    animateDecorations(deltaTime);
}

void MenuScene::render(sf::RenderWindow& window) {
    // Atualizar estados dos botões baseado na posição do mouse
    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
    updateButtonStates(worldPos);
    
    // Desenhar fundo
    window.draw(backgroundGradient);
    
    // Desenhar decorações
    for (auto& deco : decorations) {
        window.draw(deco);
    }
    
    // Desenhar botões
    window.draw(quizButton);
    window.draw(faceButton);
    window.draw(exitButton);
    
    // Desenhar textos
    window.draw(titleText);
    window.draw(subtitleText);
    window.draw(quizButtonText);
    window.draw(faceButtonText);
    window.draw(exitButtonText);
    window.draw(instructionText);
}

void MenuScene::onEnter() {
    animationTime = 0.0f;
    currentHover = HoveredButton::None;
}

#include "Scenes/FaceScene.hpp"
#include "Utils/FontManager.hpp"
#include "Utils/Colors.hpp"
#include "Config.hpp"
#include <iostream>
#include <algorithm>

FaceScene::FaceScene()
    : categoryText(FontManager::getInstance().getFont(FontManager::FontType::Regular))
    , cluesText(FontManager::getInstance().getFont(FontManager::FontType::Bold))
    , inputPromptText(FontManager::getInstance().getFont(FontManager::FontType::Regular))
    , userInputText(FontManager::getInstance().getFont(FontManager::FontType::Bold))
    , scoreText(FontManager::getInstance().getFont(FontManager::FontType::Regular))
    , feedbackText(FontManager::getInstance().getFont(FontManager::FontType::Bold))
    , instructionText(FontManager::getInstance().getFont(FontManager::FontType::Regular))
    , currentProfile(0)
    , currentClue(0)
    , score(0)
    , showingFeedback(false)
    , isCorrect(false)
    , feedbackTimer(0.0f)
    , gameFinished(false)
    , inputActive(true) {
    
    loadProfiles();
    setupUI();
}

void FaceScene::loadProfiles() {
    // Adicionar perfis de exemplo
    profiles = {
        {"BRASIL", {"É um país", "Fica na América do Sul", "Fala português", "Capital é Brasília"}, "Geografia"},
        {"SOL", {"É uma estrela", "Fica no centro do sistema", "Dá luz e calor", "A Terra orbita ao redor"}, "Ciência"},
        {"PIZZA", {"É uma comida", "Vem da Itália", "Tem massa e molho", "Pode ter queijo e pepperoni"}, "Culinária"}
    };
}

void FaceScene::setupUI() {
    auto& fontManager = FontManager::getInstance();
    
    // Categoria
    categoryText = sf::Text(fontManager.getFont(FontManager::FontType::Regular));
    categoryText.setCharacterSize(20);
    categoryText.setFillColor(Colors::TextSecondary);
    categoryText.setPosition({50.f, 100.f});
    
    // Dicas
    cluesText = sf::Text(fontManager.getFont(FontManager::FontType::Bold));
    cluesText.setCharacterSize(24);
    cluesText.setFillColor(Colors::TextPrimary);
    cluesText.setPosition({120.f, 180.f});
    
    // Prompt de entrada
    inputPromptText = sf::Text(fontManager.getFont(FontManager::FontType::Regular));
    inputPromptText.setString("Sua resposta:");
    inputPromptText.setCharacterSize(22);
    inputPromptText.setFillColor(Colors::TextSecondary);
    inputPromptText.setPosition({220.f, 380.f});
    
    // Input do usuário
    userInputText = sf::Text(fontManager.getFont(FontManager::FontType::Bold));
    userInputText.setCharacterSize(28);
    userInputText.setFillColor(Colors::TextPrimary);
    userInputText.setPosition({220.f, 425.f});
    
    // Score
    scoreText = sf::Text(fontManager.getFont(FontManager::FontType::Regular));
    scoreText.setCharacterSize(28);
    scoreText.setFillColor(Colors::TextPrimary);
    scoreText.setPosition({50.f, 30.f});
    
    // Feedback
    feedbackText = sf::Text(fontManager.getFont(FontManager::FontType::Bold));
    feedbackText.setCharacterSize(36);
    feedbackText.setPosition({300.f, 550.f});
    
    // Instrução
    instructionText = sf::Text(fontManager.getFont(FontManager::FontType::Regular));
    instructionText.setString("Digite e pressione ENTER | ESPACO para proxima dica");
    instructionText.setCharacterSize(18);
    instructionText.setFillColor(Colors::TextSecondary);
    instructionText.setPosition({220.f, 650.f});
    
    // Boxes
    categoryBox.setSize(sf::Vector2f(200.f, 40.f));
    categoryBox.setPosition({50.f, 90.f});
    categoryBox.setFillColor(Colors::Navy);
    categoryBox.setOutlineColor(Colors::Border);
    categoryBox.setOutlineThickness(2.f);
    
    clueBox.setSize(sf::Vector2f(800.f, 150.f));
    clueBox.setPosition({100.f, 170.f});
    clueBox.setFillColor(sf::Color(20, 30, 50, 100));
    clueBox.setOutlineColor(Colors::Border);
    clueBox.setOutlineThickness(2.f);
    
    inputBox.setSize(sf::Vector2f(600.f, 60.f));
    inputBox.setPosition({200.f, 415.f});
    inputBox.setFillColor(Colors::Navy);
    inputBox.setOutlineColor(Colors::BorderActive);
    inputBox.setOutlineThickness(3.f);
    
    scoreBar.setSize(sf::Vector2f(300.f, 20.f));
    scoreBar.setPosition({650.f, 40.f});
    scoreBar.setFillColor(Colors::Navy);
    scoreBar.setOutlineColor(Colors::Border);
    scoreBar.setOutlineThickness(2.f);
    
    // Indicadores de dicas
    clueIndicators.clear();
    for (int i = 0; i < 4; i++) {
        sf::CircleShape indicator(10.f);
        indicator.setPosition({100.f + i * 40.f, 340.f});
        indicator.setFillColor(Colors::Border);
        indicator.setOutlineColor(Colors::BorderActive);
        indicator.setOutlineThickness(2.f);
        clueIndicators.push_back(indicator);
    }
}

void FaceScene::updateDisplay() {
    scoreText.setString("Score: " + std::to_string(score));
    
    if (currentProfile < static_cast<int>(profiles.size()) && !gameFinished) {
        const auto& profile = profiles[currentProfile];
        categoryText.setString("Categoria: " + profile.category);
        
        // Mostrar dicas até a atual
        std::string cluesDisplay;
        for (int i = 0; i <= currentClue && i < static_cast<int>(profile.clues.size()); i++) {
            cluesDisplay += "Dica " + std::to_string(i + 1) + ": " + profile.clues[i] + "\n\n";
        }
        cluesText.setString(cluesDisplay);
        
        // Atualizar indicadores de dicas
        for (int i = 0; i < static_cast<int>(clueIndicators.size()); i++) {
            if (i <= currentClue) {
                clueIndicators[i].setFillColor(Colors::Green);
            } else {
                clueIndicators[i].setFillColor(Colors::Border);
            }
        }
        
        // Atualizar texto de entrada
        userInputText.setString(playerAnswer + (inputActive ? "_" : ""));
    } else if (gameFinished) {
        cluesText.setString("Jogo Finalizado!");
        feedbackText.setString("Score Final: " + std::to_string(score));
        feedbackText.setFillColor(Colors::Green);
    }
}

SceneType FaceScene::handleInput(const sf::Event& event) {
    if (showingFeedback) {
        if (event.getIf<sf::Event::KeyPressed>()) {
            if (gameFinished) {
                return SceneType::Menu;
            }
            showingFeedback = false;
            inputActive = true;
            nextProfile();
        }
        return SceneType::Face;
    }
    
    // Input de texto
    if (const auto* textEntered = event.getIf<sf::Event::TextEntered>()) {
        if (inputActive && textEntered->unicode < 128) {
            char c = static_cast<char>(textEntered->unicode);
            
            if (c == '\b' && !playerAnswer.empty()) {
                playerAnswer.pop_back();
            } else if (c == '\r' || c == '\n') {
                checkAnswer();
            } else if (c >= 32 && c < 127) {
                playerAnswer += std::toupper(c);
            }
            updateDisplay();
        }
    }
    
    // Teclas especiais
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::Escape) {
            return SceneType::Menu;
        } else if (keyPressed->code == sf::Keyboard::Key::Space) {
            revealNextClue();
        }
    }
    
    // Clique no botão
    if (const auto* mousePressed = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mousePressed->button == sf::Mouse::Button::Left) {
            sf::Vector2f mousePos(
                static_cast<float>(mousePressed->position.x),
                static_cast<float>(mousePressed->position.y)
            );
            
            // Revelar próxima dica se clicar na área apropriada
            revealNextClue();
        }
    }
    
    return SceneType::Face;
}

void FaceScene::revealNextClue() {
    if (currentClue < static_cast<int>(profiles[currentProfile].clues.size()) - 1) {
        currentClue++;
        updateDisplay();
    }
}

void FaceScene::nextProfile() {
    currentProfile++;
    currentClue = 0;
    playerAnswer.clear();
    
    if (currentProfile >= static_cast<int>(profiles.size())) {
        gameFinished = true;
    }
    updateDisplay();
}

void FaceScene::resetProfile() {
    currentProfile = 0;
    currentClue = 0;
    score = 0;
    playerAnswer.clear();
    showingFeedback = false;
    gameFinished = false;
    inputActive = true;
    updateDisplay();
}

std::string FaceScene::toUpperCase(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

std::string FaceScene::removeAccents(const std::string& str) {
    // Implementação básica - pode ser expandida
    return str;
}



void FaceScene::checkAnswer() {
    const auto& profile = profiles[currentProfile];
    isCorrect = (playerAnswer == profile.answer);
    
    if (isCorrect) {
        // Pontuação baseada em quantas dicas foram usadas
        int points = 4 - currentClue;
        score += std::max(1, points);
        
        feedbackText.setString("CORRETO! (+" + std::to_string(points) + " pontos)");
        feedbackText.setFillColor(Colors::Green);
    } else {
        feedbackText.setString("ERRADO! Resposta: " + profile.answer);
        feedbackText.setFillColor(Colors::Red);
    }
    
    showingFeedback = true;
    inputActive = false;
}

void FaceScene::update(float deltaTime) {
    if (showingFeedback) {
        feedbackTimer += deltaTime;
    }
}

void FaceScene::render(sf::RenderWindow& window) {
    // Fundo
    window.clear(Colors::Background);
    
    // Elementos da UI
    window.draw(scoreBar);
    window.draw(scoreText);
    
    if (!gameFinished) {
        window.draw(categoryBox);
        window.draw(categoryText);
        window.draw(clueBox);
        window.draw(cluesText);
        
        // Indicadores de dicas
        for (auto& indicator : clueIndicators) {
            window.draw(indicator);
        }
        
        window.draw(inputPromptText);
        window.draw(inputBox);
        window.draw(userInputText);
        window.draw(instructionText);
    }
    
    if (showingFeedback || gameFinished) {
        window.draw(feedbackText);
    }
}

void FaceScene::onEnter() {
    resetProfile();
    std::cout << "[FaceScene] Entrando no modo Face" << std::endl;
}

void FaceScene::onExit() {
    std::cout << "[FaceScene] Saindo do modo Face" << std::endl;
}

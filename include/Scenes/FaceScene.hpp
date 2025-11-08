#ifndef FACESCENE_HPP
#define FACESCENE_HPP

#include "Scenes/Scene.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

/**
 * @brief Estrutura para um perfil do jogo FACE
 */
struct Profile {
    std::string answer;
    std::vector<std::string> clues;
    std::string category;
};

/**
 * @brief Cena do modo Face (Perfil)
 * 
 * Jogo de dicas progressivas onde o jogador:
 * - Vê dicas uma por uma
 * - Digita a resposta
 * - Ganha mais pontos com menos dicas
 */
class FaceScene : public Scene {
public:
    FaceScene();
    ~FaceScene() override = default;
    
    SceneType handleInput(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
    void onEnter() override;
    void onExit() override;
    SceneType getType() const override { return SceneType::Face; }
    
private:
    // Perfis
    std::vector<Profile> profiles;
    int currentProfile;
    int currentClue;
    int score;
    
    // Estado
    std::string playerAnswer;
    bool showingFeedback;
    bool isCorrect;
    float feedbackTimer;
    bool gameFinished;
    bool inputActive;
    
    // Textos
    sf::Text categoryText;
    sf::Text cluesText;
    sf::Text inputPromptText;
    sf::Text userInputText;
    sf::Text scoreText;
    sf::Text feedbackText;
    sf::Text instructionText;
    
    // Shapes
    sf::RectangleShape categoryBox;
    sf::RectangleShape clueBox;
    sf::RectangleShape inputBox;
    sf::RectangleShape scoreBar;
    std::vector<sf::CircleShape> clueIndicators;
    
    // Métodos auxiliares
    void setupUI();
    void loadProfiles();
    void updateDisplay();
    void revealNextClue();
    void checkAnswer();
    void nextProfile();
    void resetProfile();
    
    // Utilitários de string
    std::string toUpperCase(const std::string& str);
    std::string removeAccents(const std::string& str);
};

#endif // FACESCENE_HPP

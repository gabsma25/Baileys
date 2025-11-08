#ifndef MENUSCENE_HPP
#define MENUSCENE_HPP

#include "Scenes/Scene.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

/**
 * @brief Cena do Menu Principal
 * 
 * Apresenta opções:
 * - Jogar Quiz
 * - Jogar Face (Perfil)
 * - Sair
 */
class MenuScene : public Scene {
public:
    MenuScene();
    ~MenuScene() override = default;
    
    SceneType handleInput(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
    void onEnter() override;
    SceneType getType() const override { return SceneType::Menu; }
    
private:
    // Textos
    sf::Text titleText;
    sf::Text subtitleText;
    sf::Text quizButtonText;
    sf::Text faceButtonText;
    sf::Text exitButtonText;
    sf::Text instructionText;
    
    // Shapes - Botões
    sf::RectangleShape quizButton;
    sf::RectangleShape faceButton;
    sf::RectangleShape exitButton;
    
    // Shapes - Decoração
    std::vector<sf::CircleShape> decorations;
    sf::RectangleShape backgroundGradient;
    
    // Estado
    enum class HoveredButton {
        None,
        Quiz,
        Face,
        Exit
    };
    HoveredButton currentHover;
    
    // Animação
    float animationTime;
    
    // Métodos auxiliares
    void setupTexts();
    void setupButtons();
    void setupDecorations();
    void updateButtonStates(const sf::Vector2f& mousePos);
    void handleButtonClick(const sf::Vector2f& mousePos);
    void animateDecorations(float deltaTime);
};

#endif // MENUSCENE_HPP

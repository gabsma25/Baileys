#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Core/SceneManager.hpp"
#include <memory>

/**
 * @brief Classe principal do jogo FACE
 * 
 * Responsável por:
 * - Inicializar sistemas (janela, fontes, cenas)
 * - Game loop principal
 * - Gerenciar tempo (deltaTime)
 * - Coordenar SceneManager
 */
class Game {
public:
    Game();
    ~Game() = default;
    
    /**
     * @brief Inicializa o jogo
     * @return true se inicialização bem-sucedida
     */
    bool initialize();
    
    /**
     * @brief Executa o loop principal do jogo
     */
    void run();
    
private:
    // Janela SFML
    sf::RenderWindow window;
    sf::Clock gameClock;
    float deltaTime;
    
    // Gerenciador de cenas
    std::unique_ptr<SceneManager> sceneManager;
    
    // Estado do jogo
    bool isRunning;
    bool isInitialized;
    
    // Métodos privados
    void processEvents();
    void update();
    void render();
    
    // Inicialização de subsistemas
    bool initializeWindow();
    bool initializeFonts();
    bool initializeScenes();
};

#endif // GAME_HPP

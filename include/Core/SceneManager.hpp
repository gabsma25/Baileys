#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include "Scenes/Scene.hpp"
#include <memory>
#include <map>

/**
 * @brief Gerenciador de cenas do jogo
 * 
 * Responsável por:
 * - Armazenar todas as cenas
 * - Controlar cena ativa
 * - Gerenciar transições entre cenas
 * - Delegação de eventos
 */
class SceneManager {
public:
    SceneManager();
    ~SceneManager() = default;
    
    /**
     * @brief Adiciona uma nova cena ao gerenciador
     * @param type Tipo da cena
     * @param scene Ponteiro único para a cena
     */
    void addScene(SceneType type, std::unique_ptr<Scene> scene);
    
    /**
     * @brief Define a cena ativa
     * @param type Tipo da cena a ser ativada
     */
    void setActiveScene(SceneType type);
    
    /**
     * @brief Obtém a cena ativa atual
     * @return Ponteiro para cena ativa ou nullptr
     */
    Scene* getActiveScene() const;
    
    /**
     * @brief Obtém o tipo da cena ativa
     */
    SceneType getActiveSceneType() const { return currentSceneType; }
    
    /**
     * @brief Processa eventos na cena ativa
     * @param event Evento SFML
     */
    void handleInput(const sf::Event& event);
    
    /**
     * @brief Atualiza a cena ativa
     * @param deltaTime Tempo desde último frame
     */
    void update(float deltaTime);
    
    /**
     * @brief Renderiza a cena ativa
     * @param window Janela onde desenhar
     */
    void render(sf::RenderWindow& window);
    
    /**
     * @brief Verifica se há uma cena ativa
     */
    bool hasActiveScene() const { return currentSceneType != SceneType::None; }
    
private:
    std::map<SceneType, std::unique_ptr<Scene>> scenes;
    SceneType currentSceneType;
    SceneType requestedSceneType; // Para transições suaves
    
    void performSceneTransition();
};

#endif // SCENEMANAGER_HPP

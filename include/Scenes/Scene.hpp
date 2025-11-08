#ifndef SCENE_HPP
#define SCENE_HPP

#include <SFML/Graphics.hpp>
#include <string>

/**
 * @brief Enumeração dos tipos de cena
 */
enum class SceneType {
    None,
    Menu,
    Quiz,
    Face,
    Exit
};

/**
 * @brief Classe base abstrata para todas as cenas do jogo
 * 
 * Define a interface comum que todas as cenas devem implementar.
 * Usa o padrão Template Method para estrutura consistente.
 */
class Scene {
public:
    virtual ~Scene() = default;
    
    /**
     * @brief Processa eventos de input
     * @param event Evento SFML
     * @return Próxima cena a ser exibida
     */
    virtual SceneType handleInput(const sf::Event& event) = 0;
    
    /**
     * @brief Atualiza lógica da cena
     * @param deltaTime Tempo desde último frame
     */
    virtual void update(float deltaTime) = 0;
    
    /**
     * @brief Renderiza a cena
     * @param window Janela SFML onde desenhar
     */
    virtual void render(sf::RenderWindow& window) = 0;
    
    /**
     * @brief Chamado quando a cena se torna ativa
     */
    virtual void onEnter() {}
    
    /**
     * @brief Chamado quando a cena deixa de ser ativa
     */
    virtual void onExit() {}
    
    /**
     * @brief Retorna o tipo da cena
     */
    virtual SceneType getType() const = 0;
    
protected:
    Scene() = default;
};

#endif // SCENE_HPP

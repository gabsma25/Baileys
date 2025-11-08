#include <SFML/Graphics.hpp>
#include <iostream>

// Enum para controlar as cenas
enum class Scene {
    MENU,
    QUIZ,
    EXIT
};

int main() {
    // Criar janela
    sf::RenderWindow window(sf::VideoMode(800, 600), "Quiz Educacional - SFML");
    window.setFramerateLimit(60);
    
    // Estado atual da cena
    Scene currentScene = Scene::MENU;
    
    // Loop principal
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        // Limpar janela
        window.clear(sf::Color(50, 50, 50));
        
        // Gerenciar cenas
        switch (currentScene) {
            case Scene::MENU:
                // TODO: Implementar menu
                break;
                
            case Scene::QUIZ:
                // TODO: Implementar quiz
                break;
                
            case Scene::EXIT:
                window.close();
                break;
        }
        
        // Exibir janela
        window.display();
    }
    
    return 0;
}

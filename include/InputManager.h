#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <map>

class InputManager {
public:
    void ProcessEvent(const sf::Event& event);
    bool IsKeyPressed(sf::Keyboard::Key key) const;
    bool IsMouseButtonPressed(sf::Mouse::Button button) const;
    sf::Vector2i GetMousePosition(const sf::RenderWindow& window) const;

    void clearKeyStates();
    
private:
    std::map<sf::Keyboard::Key, bool> keyStates;
    std::map<sf::Mouse::Button, bool> mouseStates;
};

#endif

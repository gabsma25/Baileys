#include "InputManager.h"

void InputManager::ProcessEvent(const sf::Event& event) {
    if ( event.is<sf::Event::KeyPressed>() ) {
        keyStates[event.getIf<sf::Event::KeyPressed>()->code] = true;
    }
    if ( event.is<sf::Event::KeyReleased>() ) {
        keyStates[event.getIf<sf::Event::KeyReleased>()->code] = false;
    }

    if (event.is<sf::Event::MouseButtonPressed>()) {
        mouseStates[event.getIf<sf::Event::MouseButtonPressed>()->button] = true;
    }
    if (event.is<sf::Event::MouseButtonReleased>()) {
        mouseStates[event.getIf<sf::Event::MouseButtonReleased>()->button] = false;
    }
}

bool InputManager::IsKeyPressed(sf::Keyboard::Key key) const {
    auto it = keyStates.find(key);
    return it != keyStates.end() && it->second;
}

bool InputManager::IsMouseButtonPressed(sf::Mouse::Button button) const {
    auto it = mouseStates.find(button);
    return it != mouseStates.end() && it->second;
}

sf::Vector2i InputManager::GetMousePosition(const sf::RenderWindow& window) const {
    return sf::Mouse::getPosition(window);
}

void InputManager::clearKeyStates() {
    keyStates.clear();
    mouseStates.clear();
}
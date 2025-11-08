#ifndef GAME_H
#define GAME_H

#define GAME_TITLE "SFML com Classes"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <InputManager.h>

class Game {

public:
    Game();
    void Run();

    void changeResolution(
        unsigned int width,
        unsigned int height,
        sf::State wState
    );

private:
    void ProcessEvents();
    void Update(sf::Time deltaTime);
    void Render();

    sf::RenderWindow window;
    sf::VideoMode videoMode;
    sf::ContextSettings settings;
    std::string title;
    sf::State wState;

    sf::Clock gameClock = sf::Clock();
    sf::Time gameDeltaTime = sf::Time();
    
    InputManager input;

    // Elemento de exemplo para simular um objeto player.
    sf::CircleShape player;
};

#endif

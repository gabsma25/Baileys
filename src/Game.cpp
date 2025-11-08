#include "Game.h"

float speed = 2.5f;
sf::Vector2f move = {0.f, 0.f};
sf::Vector2f p = {0.f, 0.f};

Game::Game() : window(sf::VideoMode({640u, 400u}), GAME_TITLE) {
    
    title = GAME_TITLE;
    wState = sf::State::Windowed;
    gameClock.start();

    // Exemplo para simular um objeto player.
    player.setRadius(30.f);
    player.setFillColor(sf::Color::Green);
    player.setPosition({100.f, 100.f});
    player.setOutlineThickness(2.f);
    player.setOutlineColor(sf::Color::White);
}

void Game::Run() {
    while (window.isOpen()) {
        gameDeltaTime = gameClock.restart();
        ProcessEvents();
        Update(gameDeltaTime);
        Render();
    }
}

void Game::changeResolution(unsigned int width, unsigned int height, sf::State wState) {

    // Fecha a janela atual.
    window.close();
    
    // Atualiza as configurações.
    videoMode.size.x = width;
    videoMode.size.y = height;

    // Recria a janela com as novas configurações.
    window.create(videoMode, title, wState, settings);

}

void Game::ProcessEvents() {
    std::optional<sf::Event> event;
    while (event = window.pollEvent()) {
        if ((*event).is<sf::Event::Closed>())
            window.close();

        input.ProcessEvent((*event));
    }
}

void Game::Update(sf::Time deltaTime) {

    if (input.IsKeyPressed(sf::Keyboard::Key::Escape))
        window.close();

    if (input.IsKeyPressed(sf::Keyboard::Key::Enter)) {
        if (input.IsKeyPressed(sf::Keyboard::Key::LAlt)) {
            input.clearKeyStates();
            changeResolution(800, 400, wState);
        }
    }

    move = {0.f, 0.f};

    if (input.IsKeyPressed(sf::Keyboard::Key::W)) {
        p = player.getPosition();
        move.y = (p.y <= 4) ? 0 : move.y - 1;
    }
    if (input.IsKeyPressed(sf::Keyboard::Key::S)) {
        p = player.getPosition();
        move.y = (p.y >= window.getSize().y - 64) ? 0 : move.y + 1;
    }
    if (input.IsKeyPressed(sf::Keyboard::Key::A)) {
        p = player.getPosition();
        move.x = (p.x <= 4) ? 0 : move.x - 1;
    }
    if (input.IsKeyPressed(sf::Keyboard::Key::D)) {
        p = player.getPosition();
        move.x = (p.x >= window.getSize().x - 64) ? 0 : move.x + 1;
    }
    
    if (move.length() > 0) {
        move = move.normalized();
        player.setPosition( player.getPosition() + (move * speed * deltaTime.asSeconds() * 60.f) );
    }

}

void Game::Render() {
    window.clear();
    window.draw(player);
    window.display();
}

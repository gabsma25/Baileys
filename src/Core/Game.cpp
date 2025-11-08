#include "Core/Game.hpp"
#include "Core/SceneManager.hpp"
#include "Scenes/MenuScene.hpp"
#include "Scenes/QuizScene.hpp"
#include "Scenes/FaceScene.hpp"
#include "Utils/FontManager.hpp"
#include "Config.hpp"
#include <iostream>

Game::Game() 
    : deltaTime(0.0f)
    , isRunning(false)
    , isInitialized(false) {
}

bool Game::initialize() {
    std::cout << "========================================" << std::endl;
    std::cout << "   FACE - O Jogo das Dicas" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "[Game] Iniciando sistemas..." << std::endl;
    
    if (!initializeWindow()) {
        std::cerr << "[Game] ERRO: Falha ao criar janela!" << std::endl;
        return false;
    }
    
    if (!initializeFonts()) {
        std::cerr << "[Game] ERRO: Falha ao carregar fontes!" << std::endl;
        return false;
    }
    
    if (!initializeScenes()) {
        std::cerr << "[Game] ERRO: Falha ao inicializar cenas!" << std::endl;
        return false;
    }
    
    isInitialized = true;
    std::cout << "[Game] Inicializacao completa!" << std::endl;
    std::cout << "========================================" << std::endl;
    return true;
}

bool Game::initializeWindow() {
    std::cout << "[Game] Criando janela..." << std::endl;
    
    try {
        sf::VideoMode videoMode;
        videoMode.size = {Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT};
        
        window.create(
            videoMode,
            Config::WINDOW_TITLE,
            sf::Style::Close | sf::Style::Titlebar
        );
        
        window.setFramerateLimit(Config::FRAMERATE);
        
        // Ícone da janela (opcional)
        // sf::Image icon;
        // if (icon.loadFromFile("assets/icon.png")) {
        //     window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
        // }
        
        std::cout << "[Game] Janela criada: " 
                  << Config::WINDOW_WIDTH << "x" << Config::WINDOW_HEIGHT 
                  << " @ " << Config::FRAMERATE << "fps" << std::endl;
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "[Game] Excecao ao criar janela: " << e.what() << std::endl;
        return false;
    }
}

bool Game::initializeFonts() {
    std::cout << "[Game] Carregando fontes..." << std::endl;
    
    auto& fontManager = FontManager::getInstance();
    if (!fontManager.loadFonts()) {
        std::cerr << "[Game] Falha ao carregar fontes!" << std::endl;
        return false;
    }
    
    return true;
}

bool Game::initializeScenes() {
    std::cout << "[Game] Inicializando cenas..." << std::endl;
    
    try {
        sceneManager = std::make_unique<SceneManager>();
        
        // Criar e adicionar cenas
        std::cout << "[Game] Criando MenuScene..." << std::endl;
        auto menuScene = std::make_unique<MenuScene>();
        sceneManager->addScene(SceneType::Menu, std::move(menuScene));
        
        std::cout << "[Game] Criando QuizScene..." << std::endl;
        auto quizScene = std::make_unique<QuizScene>();
        sceneManager->addScene(SceneType::Quiz, std::move(quizScene));
        
        std::cout << "[Game] Criando FaceScene..." << std::endl;
        auto faceScene = std::make_unique<FaceScene>();
        sceneManager->addScene(SceneType::Face, std::move(faceScene));
        
        // Definir cena inicial
        sceneManager->setActiveScene(SceneType::Menu);
        
        std::cout << "[Game] Cenas inicializadas!" << std::endl;
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "[Game] Excecao ao inicializar cenas: " << e.what() << std::endl;
        return false;
    }
}

void Game::run() {
    if (!isInitialized) {
        std::cerr << "[Game] ERRO: Jogo nao foi inicializado!" << std::endl;
        return;
    }
    
    std::cout << "[Game] Iniciando game loop..." << std::endl;
    isRunning = true;
    gameClock.restart();
    
    while (isRunning && window.isOpen()) {
        // Calcular deltaTime
        deltaTime = gameClock.restart().asSeconds();
        
        processEvents();
        update();
        render();
        
        // Verificar se deve sair
        if (sceneManager->getActiveSceneType() == SceneType::Exit) {
            isRunning = false;
            window.close();
        }
    }
    
    std::cout << "[Game] Encerrando..." << std::endl;
}

void Game::processEvents() {
    while (std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            isRunning = false;
            window.close();
        }
        
        // Delegar evento para o SceneManager
        if (sceneManager) {
            sceneManager->handleInput(*event);
        }
    }
}

void Game::update() {
    if (sceneManager) {
        sceneManager->update(deltaTime);
    }
}

void Game::render() {
    window.clear(sf::Color(Config::Colors::BG_R, Config::Colors::BG_G, Config::Colors::BG_B));
    
    if (sceneManager) {
        sceneManager->render(window);
    }
    
    window.display();
}

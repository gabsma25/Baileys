#include "Core/SceneManager.hpp"
#include <iostream>

SceneManager::SceneManager() 
    : currentSceneType(SceneType::None)
    , requestedSceneType(SceneType::None) {
}

void SceneManager::addScene(SceneType type, std::unique_ptr<Scene> scene) {
    if (scene) {
        scenes[type] = std::move(scene);
        std::cout << "[SceneManager] Cena adicionada: " << static_cast<int>(type) << std::endl;
    }
}

void SceneManager::setActiveScene(SceneType type) {
    if (type == currentSceneType) {
        return; // Já é a cena ativa
    }
    
    requestedSceneType = type;
    performSceneTransition();
}

Scene* SceneManager::getActiveScene() const {
    auto it = scenes.find(currentSceneType);
    if (it != scenes.end()) {
        return it->second.get();
    }
    return nullptr;
}

void SceneManager::performSceneTransition() {
    // Sair da cena atual
    if (currentSceneType != SceneType::None) {
        Scene* currentScene = getActiveScene();
        if (currentScene) {
            currentScene->onExit();
            std::cout << "[SceneManager] Saindo da cena: " 
                      << static_cast<int>(currentSceneType) << std::endl;
        }
    }
    
    // Entrar na nova cena
    currentSceneType = requestedSceneType;
    
    if (currentSceneType != SceneType::None && currentSceneType != SceneType::Exit) {
        Scene* newScene = getActiveScene();
        if (newScene) {
            newScene->onEnter();
            std::cout << "[SceneManager] Entrando na cena: " 
                      << static_cast<int>(currentSceneType) << std::endl;
        } else {
            std::cerr << "[SceneManager] ERRO: Cena nao encontrada: " 
                      << static_cast<int>(currentSceneType) << std::endl;
            currentSceneType = SceneType::None;
        }
    }
}

void SceneManager::handleInput(const sf::Event& event) {
    Scene* activeScene = getActiveScene();
    if (activeScene) {
        SceneType nextScene = activeScene->handleInput(event);
        
        if (nextScene != activeScene->getType()) {
            setActiveScene(nextScene);
        }
    }
}

void SceneManager::update(float deltaTime) {
    Scene* activeScene = getActiveScene();
    if (activeScene) {
        activeScene->update(deltaTime);
    }
}

void SceneManager::render(sf::RenderWindow& window) {
    Scene* activeScene = getActiveScene();
    if (activeScene) {
        activeScene->render(window);
    }
}

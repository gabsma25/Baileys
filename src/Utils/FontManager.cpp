#include "Utils/FontManager.hpp"
#include "Config.hpp"
#include <iostream>

FontManager& FontManager::getInstance() {
    static FontManager instance;
    return instance;
}

bool FontManager::tryLoadFont(FontType type, const std::vector<std::string>& paths) {
    for (const auto& path : paths) {
        if (fonts[type].openFromFile(path)) {
            std::cout << "[FontManager] Fonte carregada: " << path << std::endl;
            return true;
        }
    }
    
    std::cerr << "[FontManager] ERRO: Nao foi possivel carregar fonte tipo " 
              << static_cast<int>(type) << std::endl;
    return false;
}

bool FontManager::loadFonts() {
    if (fontsLoaded) {
        return true; // Já carregadas
    }
    
    std::cout << "[FontManager] Carregando fontes..." << std::endl;
    
    // Tentar carregar fonte regular
    std::vector<std::string> regularPaths = {
        Config::FONT_PATH,
        "C:/Windows/Fonts/calibri.ttf",
        "C:/Windows/Fonts/verdana.ttf",
        "assets/fonts/arial.ttf",
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf" // Linux fallback
    };
    
    if (!tryLoadFont(FontType::Regular, regularPaths)) {
        return false;
    }
    
    // Tentar carregar fonte bold
    std::vector<std::string> boldPaths = {
        Config::FONT_BOLD_PATH,
        "C:/Windows/Fonts/arialbd.ttf",
        "C:/Windows/Fonts/calibrib.ttf",
        "C:/Windows/Fonts/verdanab.ttf",
        Config::FONT_PATH, // Fallback para regular
        "assets/fonts/arialbd.ttf"
    };
    
    if (!tryLoadFont(FontType::Bold, boldPaths)) {
        // Se não conseguir bold, usar regular mesmo
        fonts[FontType::Bold] = fonts[FontType::Regular];
        std::cout << "[FontManager] Usando fonte regular para bold (fallback)" << std::endl;
    }
    
    // Fonte de título usa a mesma que bold
    // Tentar carregar fonte específica para título, se fornecida
    std::vector<std::string> titlePaths = {
        Config::FONT_TITLE_PATH,
        Config::FONT_BOLD_PATH,
        Config::FONT_PATH
    };

    if (!tryLoadFont(FontType::Title, titlePaths)) {
        // Se não houver fonte específica para título, usar bold como fallback
        fonts[FontType::Title] = fonts[FontType::Bold];
    }
    
    fontsLoaded = true;
    std::cout << "[FontManager] Fontes carregadas com sucesso!" << std::endl;
    return true;
}

const sf::Font& FontManager::getFont(FontType type) const {
    auto it = fonts.find(type);
    if (it != fonts.end()) {
        return it->second;
    }
    
    // Fallback para regular se não encontrar
    return fonts.at(FontType::Regular);
}

#ifndef FONTMANAGER_HPP
#define FONTMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <memory>

/**
 * @brief Gerenciador centralizado de fontes
 * 
 * Singleton que carrega e fornece acesso às fontes do jogo.
 * Evita múltiplos carregamentos e centraliza o gerenciamento de recursos.
 */
class FontManager {
public:
    enum class FontType {
        Regular,
        Bold,
        Title
    };
    
    // Singleton - obter instância
    static FontManager& getInstance();
    
    // Carregar todas as fontes necessárias
    bool loadFonts();
    
    // Obter fonte específica
    const sf::Font& getFont(FontType type = FontType::Regular) const;
    
    // Verificar se fontes foram carregadas
    bool isLoaded() const { return fontsLoaded; }
    
    // Delete copy constructor and assignment operator
    FontManager(const FontManager&) = delete;
    FontManager& operator=(const FontManager&) = delete;
    
private:
    FontManager() : fontsLoaded(false) {}
    
    std::map<FontType, sf::Font> fonts;
    bool fontsLoaded;
    
    // Tentar carregar fonte de múltiplos caminhos
    bool tryLoadFont(FontType type, const std::vector<std::string>& paths);
};

#endif // FONTMANAGER_HPP

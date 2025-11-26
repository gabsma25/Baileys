#ifndef COLORS_HPP
#define COLORS_HPP

#include <SFML/Graphics.hpp>
#include <cstdint>
#include "Config.hpp"

namespace Colors {
    // Paleta Vibrante de Outono - Tons Quentes
    
    // Fundos
    inline const sf::Color Background(static_cast<uint8_t>(Config::Colors::BG_DARK_R), static_cast<uint8_t>(Config::Colors::BG_DARK_G), static_cast<uint8_t>(Config::Colors::BG_DARK_B));
    inline const sf::Color BackgroundDark(static_cast<uint8_t>(Config::Colors::BG_OLIVE_R), static_cast<uint8_t>(Config::Colors::BG_OLIVE_G), static_cast<uint8_t>(Config::Colors::BG_OLIVE_B));
    inline const sf::Color BackgroundLight(65, 55, 45);
    
    // Destaques Principais
    inline const sf::Color Yellow(static_cast<uint8_t>(Config::Colors::HIGHLIGHT_ORANGE_R), static_cast<uint8_t>(Config::Colors::HIGHLIGHT_ORANGE_G), static_cast<uint8_t>(Config::Colors::HIGHLIGHT_ORANGE_B));
    inline const sf::Color Orange(static_cast<uint8_t>(Config::Colors::HIGHLIGHT_BURNED_R), static_cast<uint8_t>(Config::Colors::HIGHLIGHT_BURNED_G), static_cast<uint8_t>(Config::Colors::HIGHLIGHT_BURNED_B));
    inline const sf::Color Green(80, 200, 120);
    
    // Botões
    inline const sf::Color Navy(static_cast<uint8_t>(Config::Colors::NAVY_R), static_cast<uint8_t>(Config::Colors::NAVY_G), static_cast<uint8_t>(Config::Colors::NAVY_B));
    inline const sf::Color NavyHover(static_cast<uint8_t>(Config::Colors::NAVY_HOVER_R), static_cast<uint8_t>(Config::Colors::NAVY_HOVER_G), static_cast<uint8_t>(Config::Colors::NAVY_HOVER_B));
    inline const sf::Color NavyActive(70, 120, 180);
    
    // Feedback
    inline const sf::Color Correct(0, 250, 10);
    inline const sf::Color Wrong(220, 80, 80);
    inline const sf::Color Red = Wrong; // alias para consistência
    
    // Textos
    inline const sf::Color TextPrimary(255, 250, 240);
    inline const sf::Color TextSecondary(200, 190, 180);
    inline const sf::Color TextDark(40, 35, 30);
    
    // Decoração
    inline const sf::Color DecoYellow(255, 220, 100, 180);
    inline const sf::Color DecoOrange(255, 160, 80, 180);
    inline const sf::Color DecoGreen(170, 220, 100, 180);
    
    // UI Elements
    inline const sf::Color Border(255, 200, 100);
    inline const sf::Color BorderActive(255, 140, 40);
    
    // Indicadores
    inline const sf::Color IndicatorActive(255, 180, 60);
    inline const sf::Color IndicatorInactive(80, 70, 60);
}

#endif // COLORS_HPP

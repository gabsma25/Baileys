#ifndef COLORS_HPP
#define COLORS_HPP

#include <SFML/Graphics.hpp>
#include "Config.hpp"

namespace Colors {
    // Paleta Vibrante de Outono - Tons Quentes
    
    // Fundos
    const sf::Color Background(Config::Colors::BG_R, Config::Colors::BG_G, Config::Colors::BG_B);
    const sf::Color BackgroundDark(25, 20, 15);
    const sf::Color BackgroundLight(65, 55, 45);
    
    // Destaques Principais
    const sf::Color Yellow(Config::Colors::YELLOW_R, Config::Colors::YELLOW_G, Config::Colors::YELLOW_B);
    const sf::Color Orange(Config::Colors::ORANGE_R, Config::Colors::ORANGE_G, Config::Colors::ORANGE_B);
    const sf::Color Green(Config::Colors::GREEN_R, Config::Colors::GREEN_G, Config::Colors::GREEN_B);
    
    // Botões
    const sf::Color Navy(Config::Colors::NAVY_R, Config::Colors::NAVY_G, Config::Colors::NAVY_B);
    const sf::Color NavyHover(Config::Colors::NAVY_HOVER_R, Config::Colors::NAVY_HOVER_G, Config::Colors::NAVY_HOVER_B);
    const sf::Color NavyActive(70, 120, 180);
    
    // Feedback
    const sf::Color Correct(100, 200, 100);
    const sf::Color Wrong(220, 80, 80);
    const sf::Color Red(220, 80, 80);
    
    // Textos
    const sf::Color TextPrimary(255, 250, 240);
    const sf::Color TextSecondary(200, 190, 180);
    const sf::Color TextDark(40, 35, 30);
    
    // Decoração
    const sf::Color DecoYellow(255, 220, 100, 180);
    const sf::Color DecoOrange(255, 160, 80, 180);
    const sf::Color DecoGreen(170, 220, 100, 180);
    
    // UI Elements
    const sf::Color Border(255, 200, 100);
    const sf::Color BorderActive(255, 140, 40);
    
    // Indicadores
    const sf::Color IndicatorActive(255, 180, 60);
    const sf::Color IndicatorInactive(80, 70, 60);
}

#endif // COLORS_HPP

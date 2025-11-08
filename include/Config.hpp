#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

namespace Config {
    // ==================== JANELA ====================
    const unsigned int WINDOW_WIDTH = 1000;
    const unsigned int WINDOW_HEIGHT = 700;
    const std::string WINDOW_TITLE = "FACE - O Jogo das Dicas";
    const unsigned int FRAMERATE = 60;
    
    // ==================== CAMINHOS ====================
    // Caminhos para Windows
    const std::string FONT_PATH = "assets\fonts\freshman.ttf";
    const std::string FONT_BOLD_PATH = "assets\fonts\freshman.ttf";
    
    // Caminhos alternativos (caso precise de fontes customizadas)
    const std::string ASSETS_FONTS = "assets/fonts/";
    const std::string ASSETS_SOUNDS = "assets/sounds/";
    
    // ==================== GAMEPLAY ====================
    const int MAX_CLUES = 5;
    const int POINTS_PER_CLUE[] = {100, 80, 60, 40, 20}; // Pontos por número de dicas
    const float FEEDBACK_DURATION = 2.5f; // Segundos
    const int TOTAL_QUESTIONS_QUIZ = 5;
    
    // ==================== CORES (Paleta Vibrante Outono) ====================
    namespace Colors {
        // Fundos
        const unsigned int BG_R = 45;
        const unsigned int BG_G = 35;
        const unsigned int BG_B = 25;
        
        // Destaques
        const unsigned int YELLOW_R = 255;
        const unsigned int YELLOW_G = 200;
        const unsigned int YELLOW_B = 50;
        
        const unsigned int ORANGE_R = 255;
        const unsigned int ORANGE_G = 140;
        const unsigned int ORANGE_B = 40;
        
        const unsigned int GREEN_R = 150;
        const unsigned int GREEN_G = 200;
        const unsigned int GREEN_B = 80;
        
        // Botões
        const unsigned int NAVY_R = 30;
        const unsigned int NAVY_G = 60;
        const unsigned int NAVY_B = 100;
        
        const unsigned int NAVY_HOVER_R = 50;
        const unsigned int NAVY_HOVER_G = 90;
        const unsigned int NAVY_HOVER_B = 140;
    }
}

#endif // CONFIG_HPP

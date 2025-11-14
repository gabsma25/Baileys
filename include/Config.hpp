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
    // Caminhos para fontes (usar barras normais ou raw strings)
    const std::string FONT_PATH = "assets/fonts/freshman.ttf"; // Regular
    const std::string FONT_BOLD_PATH = "assets/fonts/8bitOperatorPlus8-Bold.ttf"; // Bold
    const std::string FONT_TITLE_PATH = "assets/fonts/mc-ten-lowercase-alt.ttf"; // Título (opcional)
    
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
    // Fundos (Backgrounds)
    // Azul Ardósia Escuro: #3A5469 (58, 84, 105)
    const unsigned int BG_DARK_R = 58;
    const unsigned int BG_DARK_G = 84;
    const unsigned int BG_DARK_B = 105;

    // Verde Oliva Escuro (Potencial Fundo ou Elemento Secundário): #646C2D (100, 108, 45)
    const unsigned int BG_OLIVE_R = 100;
    const unsigned int BG_OLIVE_G = 108;
    const unsigned int BG_OLIVE_B = 45;
    
    // Destaques (Highlights)
    // Laranja Intenso: #F07F0F (240, 127, 15)
    const unsigned int HIGHLIGHT_ORANGE_R = 240;
    const unsigned int HIGHLIGHT_ORANGE_G = 127;
    const unsigned int HIGHLIGHT_ORANGE_B = 15;
    
    // Laranja Queimado: #D85824 (216, 88, 36)
    const unsigned int HIGHLIGHT_BURNED_R = 216;
    const unsigned int HIGHLIGHT_BURNED_G = 88;
    const unsigned int HIGHLIGHT_BURNED_B = 36;
    
    // Tijolo/Marrom Escuro: #9F361E (159, 54, 30)
    const unsigned int HIGHLIGHT_BRICK_R = 159;
    const unsigned int HIGHLIGHT_BRICK_G = 54;
    const unsigned int HIGHLIGHT_BRICK_B = 30;
    
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

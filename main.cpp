#include "Core/Game.hpp"
#include <iostream>
#include <exception>

/**
 * @brief Ponto de entrada do programa
 * 
 * Cria instância do jogo, inicializa e executa o loop principal.
 */
int main() {
    try {
        // Criar instância do jogo
        Game game;
        
        // Inicializar sistemas
        if (!game.initialize()) {
            std::cerr << "ERRO: Falha na inicializacao do jogo!" << std::endl;
            std::cerr << "Pressione Enter para sair..." << std::endl;
            std::cin.get();
            return -1;
        }
        
        // Executar loop principal
        game.run();
        
        std::cout << "Jogo encerrado com sucesso!" << std::endl;
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "EXCECAO FATAL: " << e.what() << std::endl;
        std::cerr << "Pressione Enter para sair..." << std::endl;
        std::cin.get();
        return -1;
    }
    catch (...) {
        std::cerr << "ERRO DESCONHECIDO!" << std::endl;
        std::cerr << "Pressione Enter para sair..." << std::endl;
        std::cin.get();
        return -1;
    }
}

#include "Core/Game.hpp"
#include <iostream>
#include <exception>

/**
 * @brief Ponto de entrada do programa
 * 
 * Cria instância do jogo, inicializa e executa o loop principal.
 */
int main() {
    // Força flush imediato
    std::cout.setf(std::ios::unitbuf);
    std::cerr.setf(std::ios::unitbuf);
    
    std::cout << "[MAIN] >>> INICIO DO PROGRAMA <<<" << std::endl;
    
    try {
        std::cout << "[MAIN] Iniciando aplicacao..." << std::endl;
        
        // Criar instância do jogo
        std::cout << "[MAIN] Criando instancia do Game..." << std::endl;
        Game game;
        std::cout << "[MAIN] Game criado com sucesso!" << std::endl;
        
        // Inicializar sistemas
        std::cout << "[MAIN] Inicializando sistemas..." << std::endl;
        if (!game.initialize()) {
            std::cerr << "[MAIN] ERRO: Falha na inicializacao do jogo!" << std::endl;
            std::cerr << "Pressione Enter para sair..." << std::endl;
            std::cin.get();
            return -1;
        }
        std::cout << "[MAIN] Inicializacao completa!" << std::endl;
        
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

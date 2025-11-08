#ifndef QUIZSCENE_HPP
#define QUIZSCENE_HPP

#include "Scenes/Scene.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

/**
 * @brief Estrutura para uma pergunta de quiz
 */
struct Question {
    std::string question;
    std::vector<std::string> options;
    int correctAnswer; // Índice da resposta correta (0-3)
    std::string category;
};

/**
 * @brief Cena do modo Quiz
 * 
 * Jogo de perguntas e respostas com 4 opções.
 * Jogador usa teclas 1-4 para responder.
 */
class QuizScene : public Scene {
public:
    QuizScene();
    ~QuizScene() override = default;
    
    SceneType handleInput(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
    void onEnter() override;
    void onExit() override;
    SceneType getType() const override { return SceneType::Quiz; }
    
private:
    // Perguntas
    std::vector<Question> questions;
    int currentQuestion;
    int score;
    int totalQuestions;
    
    // Estado
    bool showingFeedback;
    bool isCorrect;
    float feedbackTimer;
    bool quizFinished;
    
    // Textos
    sf::Text categoryText;
    sf::Text questionText;
    sf::Text option1Text;
    sf::Text option2Text;
    sf::Text option3Text;
    sf::Text option4Text;
    sf::Text scoreText;
    sf::Text feedbackText;
    sf::Text instructionText;
    sf::Text resultText;
    
    // Shapes
    sf::RectangleShape questionBox;
    sf::RectangleShape categoryBox;
    sf::CircleShape optionIndicator1;
    sf::CircleShape optionIndicator2;
    sf::CircleShape optionIndicator3;
    sf::CircleShape optionIndicator4;
    sf::RectangleShape scoreBar;
    sf::RectangleShape progressBar;
    
    // Métodos auxiliares
    void setupUI();
    void loadQuestions();
    void updateDisplay();
    void checkAnswer(int answer);
    void nextQuestion();
    void showResults();
    void resetQuiz();
};

#endif // QUIZSCENE_HPP

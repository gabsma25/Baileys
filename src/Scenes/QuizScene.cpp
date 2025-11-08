#include "Scenes/QuizScene.hpp"
#include "Utils/FontManager.hpp"
#include "Utils/Colors.hpp"
#include "Config.hpp"
#include <iostream>

QuizScene::QuizScene()
    : categoryText(FontManager::getInstance().getFont(FontManager::FontType::Regular))
    , questionText(FontManager::getInstance().getFont(FontManager::FontType::Bold))
    , option1Text(FontManager::getInstance().getFont(FontManager::FontType::Regular))
    , option2Text(FontManager::getInstance().getFont(FontManager::FontType::Regular))
    , option3Text(FontManager::getInstance().getFont(FontManager::FontType::Regular))
    , option4Text(FontManager::getInstance().getFont(FontManager::FontType::Regular))
    , scoreText(FontManager::getInstance().getFont(FontManager::FontType::Regular))
    , feedbackText(FontManager::getInstance().getFont(FontManager::FontType::Bold))
    , instructionText(FontManager::getInstance().getFont(FontManager::FontType::Regular))
    , resultText(FontManager::getInstance().getFont(FontManager::FontType::Title))
    , currentQuestion(0)
    , score(0)
    , totalQuestions(0)
    , showingFeedback(false)
    , isCorrect(false)
    , feedbackTimer(0.0f)
    , quizFinished(false) {
    
    // Carregar perguntas de exemplo
    loadQuestions();
    setupUI();
}

void QuizScene::loadQuestions() {
    // Adicionar perguntas de exemplo
    questions = {
        {"Qual é a capital do Brasil?", {"Rio de Janeiro", "São Paulo", "Brasília", "Salvador"}, 2, "Geografia"},
        {"Quanto é 2 + 2?", {"3", "4", "5", "6"}, 1, "Matemática"},
        {"Quem pintou a Mona Lisa?", {"Van Gogh", "Picasso", "Da Vinci", "Monet"}, 2, "Arte"},
        {"Qual o maior planeta do sistema solar?", {"Terra", "Marte", "Júpiter", "Saturno"}, 2, "Ciência"}
    };
    
    totalQuestions = static_cast<int>(questions.size());
}

void QuizScene::setupUI() {
    auto& fontManager = FontManager::getInstance();
    
    // Categoria
    categoryText = sf::Text(fontManager.getFont(FontManager::FontType::Regular));
    categoryText.setCharacterSize(20);
    categoryText.setFillColor(Colors::TextSecondary);
    categoryText.setPosition({50.f, 100.f});
    
    // Pergunta
    questionText = sf::Text(fontManager.getFont(FontManager::FontType::Bold));
    questionText.setCharacterSize(28);
    questionText.setFillColor(Colors::TextPrimary);
    questionText.setPosition({100.f, 180.f});
    
    // Opções
    option1Text = sf::Text(fontManager.getFont(FontManager::FontType::Regular));
    option1Text.setCharacterSize(24);
    option1Text.setFillColor(Colors::TextPrimary);
    option1Text.setPosition({150.f, 280.f});
    
    option2Text = sf::Text(fontManager.getFont(FontManager::FontType::Regular));
    option2Text.setCharacterSize(24);
    option2Text.setFillColor(Colors::TextPrimary);
    option2Text.setPosition({150.f, 340.f});
    
    option3Text = sf::Text(fontManager.getFont(FontManager::FontType::Regular));
    option3Text.setCharacterSize(24);
    option3Text.setFillColor(Colors::TextPrimary);
    option3Text.setPosition({150.f, 400.f});
    
    option4Text = sf::Text(fontManager.getFont(FontManager::FontType::Regular));
    option4Text.setCharacterSize(24);
    option4Text.setFillColor(Colors::TextPrimary);
    option4Text.setPosition({150.f, 460.f});
    
    // Score
    scoreText = sf::Text(fontManager.getFont(FontManager::FontType::Regular));
    scoreText.setCharacterSize(28);
    scoreText.setFillColor(Colors::TextPrimary);
    scoreText.setPosition({50.f, 30.f});
    
    // Feedback
    feedbackText = sf::Text(fontManager.getFont(FontManager::FontType::Bold));
    feedbackText.setCharacterSize(36);
    feedbackText.setPosition({300.f, 550.f});
    
    // Instrução
    instructionText = sf::Text(fontManager.getFont(FontManager::FontType::Regular));
    instructionText.setString("Use teclas 1-4 para responder");
    instructionText.setCharacterSize(18);
    instructionText.setFillColor(Colors::TextSecondary);
    instructionText.setPosition({300.f, 650.f});
    
    // Resultado final
    resultText = sf::Text(fontManager.getFont(FontManager::FontType::Title));
    resultText.setCharacterSize(48);
    resultText.setPosition({250.f, 300.f});
    
    // Boxes
    questionBox.setSize(sf::Vector2f(800.f, 100.f));
    questionBox.setPosition({100.f, 170.f});
    questionBox.setFillColor(sf::Color(20, 30, 50, 100));
    questionBox.setOutlineColor(Colors::Border);
    questionBox.setOutlineThickness(2.f);
    
    categoryBox.setSize(sf::Vector2f(200.f, 40.f));
    categoryBox.setPosition({50.f, 90.f});
    categoryBox.setFillColor(Colors::Navy);
    categoryBox.setOutlineColor(Colors::Border);
    categoryBox.setOutlineThickness(2.f);
    
    // Indicadores
    optionIndicator1.setRadius(8.f);
    optionIndicator1.setPosition({120.f, 287.f});
    optionIndicator1.setFillColor(Colors::Yellow);
    
    optionIndicator2.setRadius(8.f);
    optionIndicator2.setPosition({120.f, 347.f});
    optionIndicator2.setFillColor(Colors::Orange);
    
    optionIndicator3.setRadius(8.f);
    optionIndicator3.setPosition({120.f, 407.f});
    optionIndicator3.setFillColor(Colors::Green);
    
    optionIndicator4.setRadius(8.f);
    optionIndicator4.setPosition({120.f, 467.f});
    optionIndicator4.setFillColor(Colors::DecoYellow);
    
    // Barras
    scoreBar.setSize(sf::Vector2f(300.f, 20.f));
    scoreBar.setPosition({650.f, 40.f});
    scoreBar.setFillColor(Colors::Navy);
    scoreBar.setOutlineColor(Colors::Border);
    scoreBar.setOutlineThickness(2.f);
    
    progressBar.setSize(sf::Vector2f(0.f, 16.f));
    progressBar.setPosition({652.f, 42.f});
    progressBar.setFillColor(Colors::Green);
}

void QuizScene::updateDisplay() {
    // Atualizar score
    scoreText.setString("Score: " + std::to_string(score) + "/" + std::to_string(totalQuestions));
    
    // Atualizar barra de progresso
    float progress = static_cast<float>(currentQuestion) / static_cast<float>(totalQuestions);
    progressBar.setSize(sf::Vector2f(296.f * progress, 16.f));
    
    if (currentQuestion < totalQuestions && !quizFinished) {
        // Atualizar pergunta atual
        const auto& q = questions[currentQuestion];
        categoryText.setString("Categoria: " + q.category);
        questionText.setString(q.question);
        
        // Atualizar opções
        if (q.options.size() >= 4) {
            option1Text.setString("1. " + q.options[0]);
            option2Text.setString("2. " + q.options[1]);
            option3Text.setString("3. " + q.options[2]);
            option4Text.setString("4. " + q.options[3]);
        }
    } else if (quizFinished) {
        resultText.setString("Quiz Finalizado!");
        resultText.setFillColor(Colors::Yellow);
        feedbackText.setString("Score Final: " + std::to_string(score) + "/" + std::to_string(totalQuestions));
        feedbackText.setFillColor(Colors::Green);
    }
}

SceneType QuizScene::handleInput(const sf::Event& event) {
    if (showingFeedback || quizFinished) {
        // Pressione qualquer tecla para continuar
        if (event.getIf<sf::Event::KeyPressed>()) {
            if (quizFinished) {
                return SceneType::Menu;
            }
            showingFeedback = false;
            nextQuestion();
        }
        return SceneType::Quiz;
    }
    
    // Processar resposta
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        int answer = -1;
        
        switch (keyPressed->code) {
            case sf::Keyboard::Key::Num1: answer = 0; break;
            case sf::Keyboard::Key::Num2: answer = 1; break;
            case sf::Keyboard::Key::Num3: answer = 2; break;
            case sf::Keyboard::Key::Num4: answer = 3; break;
            case sf::Keyboard::Key::Escape: return SceneType::Menu;
            default: break;
        }
        
        if (answer >= 0 && answer < 4) {
            checkAnswer(answer);
        }
    }
    
    return SceneType::Quiz;
}

void QuizScene::checkAnswer(int answer) {
    const auto& q = questions[currentQuestion];
    isCorrect = (answer == q.correctAnswer);
    
    if (isCorrect) {
        score++;
        feedbackText.setString("CORRETO!");
        feedbackText.setFillColor(Colors::Green);
    } else {
        feedbackText.setString("ERRADO! Resposta: " + q.options[q.correctAnswer]);
        feedbackText.setFillColor(Colors::Red);
    }
    
    showingFeedback = true;
    feedbackTimer = 0.0f;
}

void QuizScene::update(float deltaTime) {
    if (showingFeedback) {
        feedbackTimer += deltaTime;
    }
}

void QuizScene::nextQuestion() {
    currentQuestion++;
    if (currentQuestion >= totalQuestions) {
        quizFinished = true;
    }
    updateDisplay();
}

void QuizScene::showResults() {
    quizFinished = true;
    updateDisplay();
}

void QuizScene::resetQuiz() {
    currentQuestion = 0;
    score = 0;
    showingFeedback = false;
    quizFinished = false;
    updateDisplay();
}

void QuizScene::render(sf::RenderWindow& window) {
    // Fundo
    window.clear(Colors::Background);
    
    // Elementos da UI
    window.draw(scoreBar);
    window.draw(progressBar);
    window.draw(scoreText);
    
    if (!quizFinished) {
        window.draw(categoryBox);
        window.draw(categoryText);
        window.draw(questionBox);
        window.draw(questionText);
        
        window.draw(optionIndicator1);
        window.draw(optionIndicator2);
        window.draw(optionIndicator3);
        window.draw(optionIndicator4);
        
        window.draw(option1Text);
        window.draw(option2Text);
        window.draw(option3Text);
        window.draw(option4Text);
        
        window.draw(instructionText);
    } else {
        window.draw(resultText);
    }
    
    if (showingFeedback || quizFinished) {
        window.draw(feedbackText);
    }
}

void QuizScene::onEnter() {
    resetQuiz();
    std::cout << "[QuizScene] Entrando no modo Quiz" << std::endl;
}

void QuizScene::onExit() {
    std::cout << "[QuizScene] Saindo do modo Quiz" << std::endl;
}

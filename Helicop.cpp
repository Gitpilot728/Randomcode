#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <ctime>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Helicopter Game");
    window.setFramerateLimit(60);
    sf::CircleShape helicopter(20.f);
    helicopter.setFillColor(sf::Color::Green);
    helicopter.setPosition(100.f, 300.f);
    float helicopterVelocity = 0.f;
    const float gravity = 0.5f;
    const float lift = -10.f;
    struct Obstacle {
        sf::RectangleShape top;
        sf::RectangleShape bottom;
        float x;
    };
    std::vector<Obstacle> obstacles;
    float obstacleSpeed = -3.f;
    float obstacleSpacing = 400.f;
    float lastObstacleX = 800.f;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(100, 400);
    int score = 0;
    bool gameOver = false;
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return 1;
    }
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(48);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("Game Over!");
    gameOverText.setPosition(300.f, 250.f);
    sf::Clock clock;
    float lastTime = 0.f;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && !gameOver)
                helicopterVelocity = lift;
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R && gameOver) {
                // Reset game
                helicopter.setPosition(100.f, 300.f);
                helicopterVelocity = 0.f;
                obstacles.clear();
                lastObstacleX = 800.f;
                score = 0;
                gameOver = false;
                clock.restart();
            }
        }
        if (!gameOver) {
            helicopterVelocity += gravity;
            helicopter.move(0, helicopterVelocity);
            if (helicopter.getPosition().y < 0) {
                helicopter.setPosition(helicopter.getPosition().x, 0);
                helicopterVelocity = 0;
            }
            if (helicopter.getPosition().y > 580) {
                helicopter.setPosition(helicopter.getPosition().x, 580);
                helicopterVelocity = 0;
            }
            if (lastObstacleX > 400) {
                Obstacle obs;
                float gapY = dis(gen);
                obs.top.setSize(sf::Vector2f(50.f, gapY - 150));
                obs.top.setFillColor(sf::Color::Red);
                obs.top.setPosition(800.f, 0.f);
                obs.bottom.setSize(sf::Vector2f(50.f, 600.f - gapY - 150));
                obs.bottom.setFillColor(sf::Color::Red);
                obs.bottom.setPosition(800.f, gapY + 150);
                obs.x = 800.f;
                obstacles.push_back(obs);
                lastObstacleX = 0.f;
            }
            lastObstacleX += obstacleSpeed;
            for (auto& obs : obstacles) {
                obs.x += obstacleSpeed;
                obs.top.setPosition(obs.x, obs.top.getPosition().y);
                obs.bottom.setPosition(obs.x, obs.bottom.getPosition().y);
            }
            obstacles.erase(
                std::remove_if(obstacles.begin(), obstacles.end(),
                    [](const Obstacle& o) { return o.x < -50.f; }),
                obstacles.end()
            );
            for (const auto& obs : obstacles) {
                if (helicopter.getGlobalBounds().intersects(obs.top.getGlobalBounds()) ||
                    helicopter.getGlobalBounds().intersects(obs.bottom.getGlobalBounds())) {
                    gameOver = true;
                }
            }
            float currentTime = clock.getElapsedTime().asSeconds();
            if (currentTime - lastTime >= 1.f) {
                score++;
                lastTime = currentTime;
            }
        }
        scoreText.setString("Score: " + std::to_string(score));
        window.clear(sf::Color::Blue);
        window.draw(helicopter);
        for (const auto& obs : obstacles) {
            window.draw(obs.top);
            window.draw(obs.bottom);
        }
        window.draw(scoreText);
        if (gameOver)
            window.draw(gameOverText);
        window.display();
    }
    return 0;
}

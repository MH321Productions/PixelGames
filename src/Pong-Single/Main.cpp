#include "SFML/Graphics.hpp"
#include "Objects.hpp"

using namespace std;

int main(int anzahl, char* args[]) {

    sf::RenderWindow window(sf::VideoMode({1280, 720}), "PixelGames - Pong-Single", sf::Style::Close | sf::Style::Titlebar);
    Timer timer;
    vector<Wall> walls = {
        {0, 0, 1280, 20, sf::Color::Green},
        {0, 700, 1280, 20, sf::Color::Green},
        {0, 0, 20, 720, sf::Color::Green}
    };
    Bat bat(1260, 100, 20, 100, sf::Color::Red, window);
    Ball ball(1200, 300, 40, sf::Color::Blue, walls, bat);

    sf::Event event;
    while (window.isOpen()) {
        timer.calculateDeltaTime(true);

        //Process Events
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::EventType::Closed) window.close();
        }

        //Loop
        bat.onLoop(timer.deltaTime);
        ball.onLoop(timer.deltaTime);

        //Render
        window.clear();

        for (Wall& w: walls) w.onRender(window);
        bat.onRender(window);
        ball.onRender(window);

        window.display();

        timer.calculateDeltaTime(false);
    }

    return 0;
}
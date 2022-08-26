#include <iostream> //Test
#include "Objects.hpp"
#include "SFML/Graphics.hpp"

using namespace std;

Wall::Wall(const float& x, const float& y, const float& width, const float& height, const sf::Color& color)
: Object(x, y, width, height), rect({width, height}) {
    rect.setPosition({x, y});
    rect.setFillColor(color);
}

void Wall::onRender(sf::RenderWindow& window) {
    window.draw(rect);
}

bool Wall::isHitting(Ball& ball) {
    float right = x + width, bottom = y + height; //Right and bottom value of wall
    float bRight = ball.x + ball.width, bBottom = ball.y + ball.height; //Right and bottom value of ball

    if (x <= bRight && right >= ball.x && y <= bBottom && bottom >= ball.y) { //Hitboxes somehow overlap

        cout << "Hit: ";

        if (ball.dX == -1 && bRight >= right) { //ball hits from the right side
            ball.dX = 1;
            ball.x = right;
            cout << "Right ";
        } else if (ball.dX == 1 && ball.x <= x) { //ball hits from the left side
            ball.dX = -1;
            ball.x = x - ball.width;
            cout << "Left ";
        }

        if (ball.dY == -1 && bBottom >= bottom) { //ball hits from the bottom
            ball.dY = 1;
            ball.y = bottom;
            cout << "Bottom";
        } else if (ball.dY == 1 && ball.y <= y) { //ball hits from the top
            ball.dY = -1;
            ball.y = y - ball.height;
            cout << "Top";
        }

        cout << endl;

        return true;
    }

    return false;
}

Ball::Ball(const float& x, const float& y, const float& widthHeight, const sf::Color& color, const std::vector<Wall>& walls, Bat& bat)
: Object(x, y, widthHeight, widthHeight), walls(walls), circle(widthHeight * 0.5f), bat(bat) {
    circle.setFillColor(color);
}

void Ball::onLoop(const float& deltaTime) {
    x += (dX * deltaTime * speed);
    y += (dY * deltaTime * speed);

    for (Wall& w: walls) w.isHitting(*this);
    bat.isHitting(*this);
}

void Ball::onRender(sf::RenderWindow& window) {
    circle.setPosition({x, y});
    window.draw(circle);
    sf::RectangleShape bounds({width, height});
    bounds.setPosition({x, y});
    bounds.setOutlineColor(sf::Color::Yellow);
    bounds.setFillColor(sf::Color::Transparent);
    bounds.setOutlineThickness(2);
    window.draw(bounds);
}

Bat::Bat(const float& x, const float& y, const float& width, const float& height, const sf::Color& color, sf::RenderWindow& window)
: Wall(x, y, width, height, color), Object(x, y, width, height), window(window), halfHeight(height / 2),
minY(30), maxY(window.getSize().y - 30 - height) {}

void Bat::onLoop(const float& deltaTime) {
    sf::Vector2i mouse = sf::Mouse::getPosition(window);
    y = clamp(mouse.y - halfHeight, minY, maxY);

    rect.setPosition({x, y});
}
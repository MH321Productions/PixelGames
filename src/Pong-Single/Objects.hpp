#ifndef PG_PONG_SINGLE_OBJECTS_HPP
#define PG_PONG_SINGLE_OBJECTS_HPP

#include <vector>
#include "Util.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

class Ball;

class Wall : public virtual Object {
    protected:
        sf::RectangleShape rect;

    public:
        Wall(const float& x, const float& y, const float& width, const float& height, const sf::Color& color);

        virtual void onLoop(const float& deltaTime) {}
        virtual void onRender(sf::RenderWindow& window);
        bool isHitting(Ball& ball);
};

class Bat : public virtual Wall {
    private:
        sf::RenderWindow& window;
        int halfHeight, minY, maxY;

    public:
        Bat(const float& x, const float& y, const float& width, const float& height, const sf::Color& color, sf::RenderWindow& window);

        virtual void onLoop(const float& deltaTime);
};

class Ball : public virtual Object {
    friend class Wall;
    private:
        sf::CircleShape circle;
        std::vector<Wall> walls;
        Bat& bat;
        float speed = 200.0f;
        int dX = -1, dY = -1;

    public:
        Ball(const float& x, const float& y, const float& widthHeight, const sf::Color& color, const std::vector<Wall>& walls, Bat& bat);

        virtual void onLoop(const float& deltaTime);
        virtual void onRender(sf::RenderWindow& window);
};

#endif//PG_PONG_SINGLE_OBJECTS_HPP
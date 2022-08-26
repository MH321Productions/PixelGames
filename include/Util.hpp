#ifndef PG_OBJECT_HPP
#define PG_OBJECT_HPP

#include <chrono>

namespace sf {
    class RenderWindow;
}

/**
 * An Enum containing identifiers for all minigames
 */ 
enum Games : unsigned char {PongSingle};

/**
 * Interface for Objects over the minigames
 */ 
class Object {
    protected:
        float x, y, width, height;
    
    public:
        Object(const float& x, const float& y, const float& width, const float& height)
        : x(x), y(y), width(width), height(height) {}

        virtual void onLoop(const float& deltaTime) = 0;
        virtual void onRender(sf::RenderWindow& window) = 0;
};

/**
 * A small utility class for calculating delta time
 */ 
class Timer {
    private:
        std::chrono::time_point<std::chrono::system_clock> start;
        std::chrono::duration<float> diff;

    public:
        float deltaTime = 0.0f;

        void calculateDeltaTime(const bool& startFrame);
};

#endif//PG_OBJECT_HPP
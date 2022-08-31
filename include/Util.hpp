#ifndef PG_OBJECT_HPP
#define PG_OBJECT_HPP

#include <chrono>
#include <string>
#include <vector>

namespace sf {
    class RenderWindow;
}

using Byte = unsigned char;

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

/**
 * A small utility class for Base64 en-/decoding
 */ 
class Base64 {
    private:
        static const std::string b64Chars;

        static inline bool isBase64(const Byte& c);

    public:
        static std::string encode(const Byte* buf, size_t len);
        static std::string encode(const std::vector<Byte>& buf);

        static std::vector<Byte> decode(const std::string& encoded);
};

/**
 * A small utility class to setup Windows for UTF-8 use
 */ 
class Windows {
    public:
        static void setupWindows();
};

#endif//PG_OBJECT_HPP
#pragma once
#include <SFML\Graphics.hpp>
#include <Box2D/Box2D.h>

struct Vector2
{
    float x, y;

    Vector2() 
    {
        x = 0;
        y = 0;
    }

    Vector2(float x_, float y_) 
    { 
        x = x_; 
        y = y_; 
    }

    Vector2& operator=(const Vector2& newVec2) 
    {
        x = newVec2.x;
        y = newVec2.y;

        return *this;
    }

    Vector2& operator=(const b2Vec2& newVec2) 
    {
        x = newVec2.x;
        y = newVec2.y;

        return *this;
    }

    Vector2 operator+(const Vector2& newVec2) const 
    {
        return Vector2(x + newVec2.x, y + newVec2.y);
    }

    Vector2 operator-(const Vector2& newVec2) const 
    {
        return Vector2(x - newVec2.x, y - newVec2.y);
    }

    Vector2 operator*(const float& newFloat) const 
    {
        return Vector2(x * newFloat, y * newFloat);
    }

    Vector2 operator/(const float& newFloat) const 
    {
        return Vector2(x / newFloat, y / newFloat);
    }

    //Convert to SFML Vector2
    operator sf::Vector2f() const { return sf::Vector2f(x, y); }

    //Convert to Box2D b2Vec2
    operator b2Vec2() const { return b2Vec2(x, y); }

    //Convert from Box2D b2Vec2
    Vector2(const b2Vec2& b2vec)
    {
        x = b2vec.x;
        y = b2vec.y;
    }

    Vector2(const sf::Vector2i& vec2)
    {
        x = vec2.x;
        y = vec2.y;
    }
};
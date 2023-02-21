#pragma once
#include <SFML\Graphics.hpp>
#include <Box2D/Box2D.h>

struct Vector2
{
    float x, y;

    // Default constructor
    Vector2() 
    {
        x = 0;
        y = 0;
    }

    // Constructor with parameters
    Vector2(float x_, float y_) 
    { 
        x = x_; 
        y = y_; 
    }

    Vector2& operator=(const Vector2& newVec2) {
        x = newVec2.x;
        y = newVec2.y;

        return *this;
    }

    Vector2& operator+(const Vector2& newVec2) {
        x += newVec2.x;
        y += newVec2.y;

        return *this;
    }

    Vector2& operator*(const float& newFloat) {
        x *= newFloat;
        y *= newFloat;

        return *this;
    }

    // Convert to SFML Vector2
    operator sf::Vector2f() const { return sf::Vector2f(x, y); }

    // Convert to Box2D b2Vec2
    operator b2Vec2() const { return b2Vec2(x, y); }
};
#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
class GraphicsEngine
{    
    //this stores the game engine window
    sf::RenderWindow window;

public:

    GraphicsEngine();

    ~GraphicsEngine();

    //this is only called once and it creates and returns the Game Engine Window
    sf::RenderWindow* InitializeWindow(float width, float height);

    void Render();

    sf::RenderWindow* GetEngineWindow();

#pragma region DEBUG FUNCTIONS


	inline void Debug_DrawRectangle(b2Fixture* fixture_ , const sf::Color& color)
	{
        // Get the AABB of the fixture
        b2AABB aabb = fixture_->GetAABB(0);

        // Calculate the position of the rectangle
        sf::Vector2f position(aabb.GetCenter().x * 200.f, aabb.GetCenter().y * 200.f);

        // Calculate the size of the rectangle
        sf::Vector2f size((aabb.GetExtents().x * 2.f) * 200.f, (aabb.GetExtents().y * 2.f) * 200.f);

        // Create an SFML rectangle shape to draw the collider
        sf::RectangleShape rectangle;

        // Set the size and position of the rectangle
        rectangle.setSize(size);
        rectangle.setOrigin(size / 2.f);
        rectangle.setPosition(position);

        // Set the rotation of the rectangle to match the rotation of the Box2D fixture
        rectangle.setRotation(fixture_->GetBody()->GetAngle() * 180.f / b2_pi);

        // Set the color of the rectangle to red
        rectangle.setFillColor(color);

        // Draw the rectangle shape to the SFML window
        window.draw(rectangle);
	};

#pragma endregion
};


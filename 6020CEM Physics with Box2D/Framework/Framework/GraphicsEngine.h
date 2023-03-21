#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>


class GraphicsEngine
{    
    //this stores the game engine window
    sf::RenderWindow window;
    sf::Font gameEngineFont;

public:

    GraphicsEngine();

    ~GraphicsEngine();

    //this is only called once and it creates and returns the Game Engine Window
    sf::RenderWindow* InitializeWindow(float width, float height);

    void Render();

    sf::RenderWindow* GetEngineWindow();

#pragma region DEBUG FUNCTIONS

    //this draws the square colliders (only  activated in debug mode)
	inline void Debug_DrawCollider(b2Fixture* fixture_ , const sf::Color& color)
	{
        //this gets the polygon shape of the fixture received
        b2PolygonShape* polygonShape = dynamic_cast<b2PolygonShape*>(fixture_->GetShape());
        if (!polygonShape)
            return;

        int32 vertexCount = polygonShape->m_count;
        //create a convex shape that will be used to draw our collider
        sf::ConvexShape shapeOfCollider;
        shapeOfCollider.setPointCount(vertexCount);
        //loop through every vertex created and assign its points as the same as the box2d shape
        for (int32 i = 0; i < vertexCount; ++i) {
            b2Vec2 vertex = polygonShape->m_vertices[i];
            shapeOfCollider.setPoint(i, sf::Vector2f(vertex.x * 215.f, vertex.y * 215.f));
        }
        
        //paint the shape
        shapeOfCollider.setFillColor(sf::Color::Transparent);
        shapeOfCollider.setOutlineColor(color);
        shapeOfCollider.setOutlineThickness(-1.0f);

        //this gets the position and angle of the collider
        b2Vec2 position = fixture_->GetBody()->GetPosition();
        float angle = fixture_->GetBody()->GetAngle();
        //creates a new sf::transform and moves it, rotates and scales with the correct values from the collider
        sf::Transform transform;
        transform.translate(position.x * 200.f, position.y * 200.f);
        transform.rotate(angle * 180.f / b2_pi);
        transform.scale(1.f, 1.f);
        //draw the collider
        window.draw(shapeOfCollider, transform);
        
	};

    //this will write on the game screen the debug information
    void Debug_WriteDebugInformation();
#pragma endregion
};


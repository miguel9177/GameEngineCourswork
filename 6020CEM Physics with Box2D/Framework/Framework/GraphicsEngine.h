#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Vector2.h"

class GraphicsEngine
{    
    //this stores the game engine window
    sf::RenderWindow window;
    //stores the camera
    sf::View cameraView;
    //stores the gameengine font
    static sf::Font gameEngineFont;
    //stores the camera position
    Vector2 cameraPos;
public:

    GraphicsEngine();

    ~GraphicsEngine();

    //this is only called once and it creates and returns the Game Engine Window
    sf::RenderWindow* InitializeWindow(float width, float height);

    //this renders everything
    void Render();

    //returns the engine window, since this class is only accescible by the game engine is fine to give the window
    sf::RenderWindow* GetEngineWindow();

    //returns the game engine font
    static inline sf::Font* GetGameEngineFont() { return &gameEngineFont; };

#pragma region Functionality functions
    
    void MoveCamera(Vector2 _newPos);
    //this gets the camera world position
    Vector2 GetCameraPosition();
    //this gets the camera sfml position
    Vector2 GetCameraSfmlPosition();
    Vector2 GetCameraSize();
    //chanhges the camera size
    void SetCameraSize(Vector2 _newSize);
    //changes the camera view port
    void SetCameraViewPort(sf::FloatRect _newViewPort);

#pragma endregion

#pragma region DEBUG FUNCTIONS

    //drawas the debug mode information
    void DrawDebugModeInformation();

    //this draws the square colliders (only  activated in debug mode)
	inline void Debug_DrawCollider(b2Fixture* fixture_ , const sf::Color& color)
	{
        //this gets the polygon shape of the fixture received
        b2PolygonShape* polygonShape = dynamic_cast<b2PolygonShape*>(fixture_->GetShape());
        //if a polygon collider
        if (polygonShape)
        {
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
        }
        //if not polygon collider, then its a circle collider
        else
        {
            b2CircleShape* circleShape = dynamic_cast<b2CircleShape*>(fixture_->GetShape());
            //if not circle collider, leave since something is wrong
            if (!circleShape)
                return;

            //creates the circle shapw with the correct origin and radius
            float radius = circleShape->m_radius;
            sf::CircleShape sfCircleShape(radius * 200.f);
            sfCircleShape.setOrigin(radius * 200.f, radius * 200.f);

            //paint the shape
            sfCircleShape.setFillColor(sf::Color::Transparent);
            sfCircleShape.setOutlineColor(color);
            sfCircleShape.setOutlineThickness(-1.0f);

            //this gets the position and angle of the collider
            b2Vec2 position = fixture_->GetBody()->GetPosition();
            float angle = fixture_->GetBody()->GetAngle();
            sf::Transform transform;
            transform.translate(position.x * 200.f, position.y * 200.f);
            transform.rotate(angle * 180.f / b2_pi);
            transform.scale(1.f, 1.f);
            window.draw(sfCircleShape, transform);
        }
	};

    //this will write on the game screen the debug information
    void Debug_WriteDebugInformation();

#pragma endregion
};


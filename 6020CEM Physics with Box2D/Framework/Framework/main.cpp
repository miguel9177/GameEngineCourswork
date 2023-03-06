#include <iostream>
#include <SFML\Graphics.hpp>
#include <Box2D/Box2D.h>
#include <stdlib.h>
#include "GameEngine.h"
#include "EventQueue.h"
#include "Scene.h"
#include "Com_Mesh.h"
#include "Shape_Box.h"
#include "RigidBody.h"
#include "SquareCollider.h"
#include "Component.h"

void test()
{
    std::cout << "ei" << std::endl;
}

void test2()
{
    std::cout << "ei2" << std::endl;
}

int main()
{
    GameEngine::GetInstance()->InitializeEngine(500,500);

    EventQueue::GetInstance()->SubscribeToVoidEvent(EventQueue::voidEvents::shoot, &test);
    EventQueue::GetInstance()->SubscribeToVoidEvent(EventQueue::voidEvents::shoot, &test2);
    EventQueue::GetInstance()->InvokeVoidEvents(EventQueue::voidEvents::shoot);

#pragma region creating a game object with a mesh with and shape and a texture
    
    GameObject* obj1 = new GameObject("obj1", new Transform(Vector2(1, 0), 0, Vector2(1, 1)));
    
    Shape_Box* shapeBox = new Shape_Box();
    sf::Texture testTexture;
    if (!testTexture.loadFromFile("../Textures/keyboardcat.jpg"))
    {
        std::cout << "Texture did not load!" << "\n" << std::endl;
    }

    Com_Mesh* obj1Mesh = new Com_Mesh(&testTexture, shapeBox);

    RigidBody* rb = new RigidBody(b2_dynamicBody);
    
    SquareCollider* squareColl = new SquareCollider(Vector2(0.1, 0.1), Vector2(0, 0));

    obj1->AddComponent(rb);
    obj1->AddComponent(squareColl);
    obj1->AddComponent(obj1Mesh);

    //add an object to the scene
    Scene::GetInstance()->AddObject(obj1);







    //Object 2
    GameObject* obj2 = new GameObject("obj2", new Transform(Vector2(1,1.2), 0, Vector2(1,1)));

    Shape_Box* shapeBox2 = new Shape_Box();

    Com_Mesh* obj2Mesh = new Com_Mesh();

    RigidBody* rb2 = new RigidBody(b2_kinematicBody);

    SquareCollider* squareColl2 = new SquareCollider(Vector2(0.1, 0.1), Vector2(0, 0));

    sf::Texture testTexture2;
    if (!testTexture2.loadFromFile("../Textures/pngTestTransparent.png"))
    {
        std::cout << "Texture did not load!" << "\n" << std::endl;
    }

    
    obj2Mesh->SetShape(shapeBox2);
    obj2Mesh->SetTexture(&testTexture2);

    obj2->AddComponent(obj2Mesh);
    obj2->AddComponent(rb2);
    obj2->AddComponent(squareColl2);

    //add an object to the scene
    Scene::GetInstance()->AddObject(obj2);
    
#pragma endregion
 



    while (GameEngine::GetInstance()->isGameEngineRunning())
    {
        GameEngine::GetInstance()->Update();
        GameEngine::GetInstance()->Render();
        
        for (int i = 0; i < InputsEngine::GetInstance()->GetInputEvents()->size(); i++)
        {
            if (InputsEngine::GetInstance()->GetInputEvents()->at(i).type == sf::Event::KeyPressed)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {
                    std::cout << "PRessed A" << std::endl;
                    obj1->SetPosition(Vector2(obj1->GetPosition().x + 0.1f, obj1->GetPosition().y));
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                {
                    std::cout << "PRessed D" << std::endl;
                    obj1->SetPosition(Vector2(obj1->GetPosition().x - 0.1f, obj1->GetPosition().y));
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                {
                    std::cout << "PRessed W" << std::endl;
                    obj1->SetPosition(Vector2(obj1->GetPosition().x, obj1->GetPosition().y - 0.1));
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                {
                    std::cout << "PRessed S" << std::endl;
                    obj1->SetPosition(Vector2(obj1->GetPosition().x, obj1->GetPosition().y + 0.1));
                }
            }
            if (InputsEngine::GetInstance()->GetInputEvents()->at(i).type == sf::Event::Closed)
            {
                std::cout << "Closed Window" << std::endl;
            }
            break;
        }


#pragma region testing sfml and box2d position

        Com_Mesh* meshToCheckPos = obj1->TryGetComponent<Com_Mesh>(Component::typeOfComponent::Mesh);
        RigidBody* rbToCheckPos = obj1->TryGetComponent<RigidBody>(Component::typeOfComponent::Physics);

        float scalingFactor = 200.0f;

        // Assume you have a sprite or shape called sprite and a body called body

        // Get the position of the sprite or shape
        sf::Vector2f spritePosition = meshToCheckPos->GetMeshToRender()->getPosition();

        // Get the position of the body
        b2Vec2 bodyPosition = rbToCheckPos->GetPosition();

        // Convert the Box2D position to SFML coordinates
        sf::Vector2f bodyPositionSFML = sf::Vector2f(bodyPosition.x, bodyPosition.y);

        // Compare the two positions
        if (spritePosition == bodyPositionSFML) {
            // The sprite and body are in the same position
        }
        else {
            // The sprite and body are not in the same position
        }



#pragma endregion
    }

	return 0;
}

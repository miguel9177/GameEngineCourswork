#include <iostream>
#include <SFML\Graphics.hpp>
#include <Box2D/Box2D.h>
#include <stdlib.h>
#include "GameEngine.h"
#include "EventQueue.h"
#include "Scene.h"
#include "Com_Mesh.h"
#include "Shape_Box.h"

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
    
    GameObject* obj1 = new GameObject("obj1", new Transform());
    
    Shape_Box* shapeBox = new Shape_Box();
    sf::Texture testTexture;
    if (!testTexture.loadFromFile("../Textures/keyboardcat.jpg"))
    {
        std::cout << "Texture did not load!" << "\n" << std::endl;
    }

    Com_Mesh* obj1Mesh = new Com_Mesh(&testTexture, shapeBox);

    obj1->AddComponent(obj1Mesh);

    //add an object to the scene
    Scene::GetInstance()->AddObject(obj1);

    //Object 2
    GameObject* obj2 = new GameObject("obj2", new Transform(Vector2(200,200), 0, Vector2(2,2)));

    Shape_Box* shapeBox2 = new Shape_Box();

    Com_Mesh* obj2Mesh = new Com_Mesh();
    sf::Texture testTexture2;
    if (!testTexture2.loadFromFile("../Textures/pngTestTransparent.png"))
    {
        std::cout << "Texture did not load!" << "\n" << std::endl;
    }
    obj2Mesh->SetShape(shapeBox2);
    obj2Mesh->SetTexture(&testTexture2);

    obj2->AddComponent(obj2Mesh);

    //add an object to the scene
    Scene::GetInstance()->AddObject(obj2);

#pragma endregion
 
    while (GameEngine::GetInstance()->isGameEngineRunning())
    {
        GameEngine::GetInstance()->Update();
        GameEngine::GetInstance()->Render();
        
        /*  for (int i = 0; i < InputsEngine::GetInstance()->GetInputEvents()->size(); i++)
        {
            if (InputsEngine::GetInstance()->GetInputEvents()->at(i).type == sf::Event::KeyPressed)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {
                    std::cout << "PRessed A" << std::endl;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                {
                    std::cout << "PRessed D" << std::endl;
                }
            }
            if (InputsEngine::GetInstance()->GetInputEvents()->at(i).type == sf::Event::Closed)
            {
                std::cout << "Closed Window" << std::endl;
            }
            break;
        }*/
    }

	return 0;
}

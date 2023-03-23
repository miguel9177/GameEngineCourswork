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
#include "UiEngine.h"
#include "UiScreenView_Text.h"
#include "UiScreenView_Image.h"
#include "UiScreenView_btnImage.h"
#include "UiScreenView_btnText.h"
#include "EngineFunctionalityManager.h"
#include "AllUserScipts/SB_TestScript.h"
#include <fstream>
#include <jsoncpp/json/json.h>

void test()
{
    std::cout << "ei" << std::endl;
}

void test2()
{
    std::cout << "ei2" << std::endl;
}

void test3()
{
    std::cout << "ei3" << std::endl;
}

void testUserKeyPressedA() { std::cout << "Pressed A" << std::endl; }

void testUserKeyReleasedA() { std::cout << "Released A" << std::endl; }

void testUserKeyPressedD() { std::cout << "Pressed D" << std::endl; }

void testUserKeyReleasedD() { std::cout << "Released D" << std::endl; }


#pragma region Testing event callback mouse input

void testUserMouseKeyPressedRight() { std::cout << "Pressed Right Mouse Button" << std::endl; }

void testUserMouseKeyPressedLeft() { std::cout << "Pressed Left Mouse Button" << std::endl; }

void testUserMouseKeyPressedMidle() { std::cout << "Pressed Midle Mouse Button" << std::endl; }

void testUserMouseKeyReleasedRight() { std::cout << "Released Right Mouse Button" << std::endl; }

void testUserMouseKeyReleasedLeft() { std::cout << "Released Left Mouse Button" << std::endl; }

void testUserMouseKeyReleasedMidle() { std::cout << "Released Midle Mouse Button" << std::endl; }

void testUserMouseMoved(Vector2 pos_) { std::cout << "Mouse position: X: " << pos_.x << " Y: " << pos_.y << std::endl; }
void testUserMouseMoved2(Vector2 pos_) { std::cout << "Mouse position2: X: " << pos_.x << " Y: " << pos_.y << std::endl; }

void testUserMouseScrollWheel(float delta_) { std::cout << "Mouse scrolled wheel " << delta_ << std::endl; }

#pragma endregion



int main()
{
    GameEngine::GetInstance()->InitializeEngine(1920,1080);
  
   /* EventQueue::GetInstance()->SubscribeToVoidEvent(EventQueue::voidEvents::shoot, &test);
    EventQueue::GetInstance()->SubscribeToVoidEvent(EventQueue::voidEvents::shoot, &test2);

    EventQueue::GetInstance()->SubscribeToKeyPressEvent(sf::Keyboard::A, &testUserKeyPressedA);
    EventQueue::GetInstance()->SubscribeToKeyPressEvent(sf::Keyboard::D, &testUserKeyPressedD);

    EventQueue::GetInstance()->SubscribeToKeyReleasedEvent(sf::Keyboard::A, &testUserKeyReleasedA);
    EventQueue::GetInstance()->SubscribeToKeyReleasedEvent(sf::Keyboard::D, &testUserKeyReleasedD);

    EventQueue::GetInstance()->SubscribeToMouseKeyPressEvent(sf::Mouse::Button::Right, &testUserMouseKeyPressedRight);
    EventQueue::GetInstance()->SubscribeToMouseKeyPressEvent(sf::Mouse::Button::Left, &testUserMouseKeyPressedLeft);
    EventQueue::GetInstance()->SubscribeToMouseKeyPressEvent(sf::Mouse::Button::Middle, &testUserMouseKeyPressedMidle);
    EventQueue::GetInstance()->SubscribeToMouseKeyReleasedEvent(sf::Mouse::Button::Right, &testUserMouseKeyReleasedRight);
    EventQueue::GetInstance()->SubscribeToMouseKeyReleasedEvent(sf::Mouse::Button::Left, &testUserMouseKeyReleasedLeft);
    EventQueue::GetInstance()->SubscribeToMouseKeyReleasedEvent(sf::Mouse::Button::Middle, &testUserMouseKeyReleasedMidle);*/

 

    //EventQueue::GetInstance()->SubscribeToMouseMovedEvent(&testUserMouseMoved);
    /*EventQueue::GetInstance()->SubscribeToMouseWheelScrolledEvent(&testUserMouseScrollWheel);

    EventQueue::GetInstance()->InvokeVoidEvents(EventQueue::voidEvents::shoot);*/


#pragma region creating a game object with a mesh with and shape and a texture
    
    GameObject* obj1 = new GameObject("obj1", new Transform(Vector2(1, 0), 0, Vector2(1.5, 1.5)));
    
    Shape_Box* shapeBox = new Shape_Box();
    sf::Texture testTexture;
    if (!testTexture.loadFromFile("../Textures/keyboardcat.jpg"))
    {
        std::cout << "Texture did not load!" << "\n" << std::endl;
    }

    Com_Mesh* obj1Mesh = new Com_Mesh(&testTexture, shapeBox);

    RigidBodySettings bodySettings_ = RigidBodySettings(dynamicBody, 1, 1, false, true, false, true, 0);
    RigidBody* rb = new RigidBody(bodySettings_);
    
    SquareCollider* squareColl = new SquareCollider(Vector2(0.122, 0.122), Vector2(0, 0));

    SB_TestScript* playerScript = new SB_TestScript();

    obj1->AddComponent(playerScript);
    obj1->AddComponent(rb);
    obj1->AddComponent(squareColl);
    obj1->AddComponent(obj1Mesh);

    //add an object to the scene
    Scene::GetInstance()->AddObject(obj1);


    //Object 2
    GameObject* obj2 = new GameObject("obj2", new Transform(Vector2(1,1.2), 0, Vector2(1,1)));

    Shape_Box* shapeBox2 = new Shape_Box();

    Com_Mesh* obj2Mesh = new Com_Mesh();

    RigidBodySettings bodySettings = RigidBodySettings(dynamicBody, 1, 1, false, true, false, false, 0);
    RigidBody* rb2 = new RigidBody(bodySettings);

    SquareCollider* squareColl2 = new SquareCollider(Vector2(0.122, 0.122), Vector2(0, 0));

    sf::Texture testTexture2;
    if (!testTexture2.loadFromFile("../Textures/WhiteSquare.png"))
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

    //Object 3
    GameObject* obj3 = new GameObject("obj3", new Transform(Vector2(1, 1.2), 0, Vector2(1.5, 1.5)));

    Shape_Box* shapeBox3 = new Shape_Box();

    Com_Mesh* obj3Mesh = new Com_Mesh();

    RigidBodySettings bodySettings3 = RigidBodySettings(staticBody, 1, 1, false, true, false, false, 0);
    RigidBody* rb3 = new RigidBody(bodySettings3);

    SquareCollider* squareColl3 = new SquareCollider(Vector2(0.122, 0.122), Vector2(0, 0));

    sf::Texture testTexture3;
    if (!testTexture2.loadFromFile("../Textures/WhiteSquare.png"))
    {
        std::cout << "Texture did not load!" << "\n" << std::endl;
    }

    obj3Mesh->SetShape(shapeBox3);
    obj3Mesh->SetTexture(&testTexture3);

    obj3->AddComponent(obj3Mesh);
    obj3->AddComponent(rb3);
    obj3->AddComponent(squareColl3);

    //add an object to the scene
    Scene::GetInstance()->AddObject(obj3);
    
#pragma endregion

    Com_Mesh* meshToCheckPos = obj1->TryGetComponent<Com_Mesh>(Component::typeOfComponent::Mesh);
    RigidBody* rbToCheckPos = obj1->TryGetComponent<RigidBody>(Component::typeOfComponent::Physics);

    float forceToAply = 0.1f;
    while (GameEngine::GetInstance()->isGameEngineRunning())
    {
        GameEngine::GetInstance()->Update();
        GameEngine::GetInstance()->Render();
        GameEngine::GetInstance()->MoveCamera(obj1->GetPosition());


        if (InputsEngine::GetInstance()->GetKeyStates()[sf::Keyboard::A].pressing)
        {
            //std::cout << "PRessed A" << std::endl;
            rbToCheckPos->AddForceToCenter(Vector2(-forceToAply, 0.f));
        }
        if (InputsEngine::GetInstance()->GetKeyStates()[sf::Keyboard::D].pressing)
        {
            //std::cout << "PRessed D" << std::endl;
            rbToCheckPos->AddForceToCenter(Vector2(+forceToAply, 0.f));
        }

        if (InputsEngine::GetInstance()->GetKeyStates()[sf::Keyboard::W].pressing)
        {
            //std::cout << "PRessed W" << std::endl;
            rbToCheckPos->AddForceToCenter(Vector2(0.f, -forceToAply));
        }
        if (InputsEngine::GetInstance()->GetKeyStates()[sf::Keyboard::S].pressing)
        {
            //std::cout << "PRessed S" << std::endl;
            rbToCheckPos->AddForceToCenter(Vector2(0.f, +forceToAply));
        }

        //std::cout << InputsEngine::GetInstance()->GetMouseState().wheelDelta << std::endl;

        /*for (int i = 0; i < InputsEngine::GetInstance()->GetInputEvents()->size(); i++)
        {
            if (InputsEngine::GetInstance()->GetInputEvents()->at(i).type == sf::Event::KeyPressed)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {
                    std::cout << "PRessed A" << std::endl;
                    rbToCheckPos->AddForceToCenter(Vector2(-forceToAply, 0.f));
                    
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                {
                    std::cout << "PRessed D" << std::endl;
                    rbToCheckPos->AddForceToCenter(Vector2(+forceToAply, 0.f));
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                {
                    std::cout << "PRessed W" << std::endl;
                    rbToCheckPos->AddForceToCenter(Vector2(0.f, -forceToAply));
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                {
                    std::cout << "PRessed S" << std::endl;
                    rbToCheckPos->AddForceToCenter(Vector2(0.f, +forceToAply));
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

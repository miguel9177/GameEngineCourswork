#include <iostream>
#include <SFML\Graphics.hpp>
#include <Box2D/Box2D.h>
#include <stdlib.h>
#include "GameEngine.h"
#include "EventQueue.h"
using namespace std;

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
    GameEngine* gameEngine = new GameEngine(500, 500);

    EventQueue::GetInstance()->SubscribeToVoidEvent(EventQueue::voidEvents::shoot, &test);
    EventQueue::GetInstance()->SubscribeToVoidEvent(EventQueue::voidEvents::shoot, &test2);
    EventQueue::GetInstance()->InvokeVoidEvents(EventQueue::voidEvents::shoot);

    while (gameEngine->isGameEngineRunning())
    {
        gameEngine->Update();
        gameEngine->Render();
    }

    delete gameEngine;
	return 0;
}

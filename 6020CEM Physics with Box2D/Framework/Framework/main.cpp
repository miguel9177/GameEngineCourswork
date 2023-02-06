#include <iostream>
#include <SFML\Graphics.hpp>
#include <Box2D/Box2D.h>
#include <stdlib.h>
#include "GameEngine.h"

using namespace std;

int main()
{
    GameEngine* gameEngine = new GameEngine(500, 500);

    while (gameEngine->isGameEngineRunning())
    {
        gameEngine->Update();
        gameEngine->Render();
    }

    delete gameEngine;
	return 0;
}
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
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (GraphicsEngine::GetInstance()->GetEngineWindow()->pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                GraphicsEngine::GetInstance()->GetEngineWindow()->close();
        }

        gameEngine->Render();
    }

    delete gameEngine;
	return 0;
}
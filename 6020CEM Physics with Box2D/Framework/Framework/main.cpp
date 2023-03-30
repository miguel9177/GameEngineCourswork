#include "GameEngine.h"
#include "EventQueue.h"
#include <iostream>
#include <Windows.h>

//if true it will restart the engine
bool restartEngine = false;

//when called, it will tell the engine to restart
void RestartEngine()
{
    restartEngine = true;
}

//this creates a new instance of the application, so that we can safely leave gameplay mode, so that box2d is properly reseted and everything works fine
void CreateNewInstance() 
{
    STARTUPINFOW startupInfo;//stores the start up info
    PROCESS_INFORMATION processInfo;//stores the process information

    //makes the starup info not have unitialize values
    ZeroMemory(&startupInfo, sizeof(startupInfo));
    startupInfo.cb = sizeof(startupInfo);
    //makes the process info not have unitialize values
    ZeroMemory(&processInfo, sizeof(processInfo));
    //choses the settings (in this case show and hide it)
    startupInfo.dwFlags = STARTF_USESHOWWINDOW;
    startupInfo.wShowWindow = SW_HIDE;

    //this gets the path to the executable
    std::wstring exePath = L"\"";
    WCHAR exeFullPath[MAX_PATH];
    GetModuleFileNameW(NULL, exeFullPath, MAX_PATH);
    exePath += exeFullPath;
    exePath += L"\"";

    //we create a cmd command
    std::wstring cmdLine = L"cmd /c start \"\" ";
    cmdLine += exePath;

    //we lanch the create window process
    if (!CreateProcessW(NULL, &exePath[0], NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &startupInfo, &processInfo)) 
        std::cerr << "Error: problkem lanching the new window" << GetLastError() << std::endl;
    
}

int main()
{
    //this initializes the engine
    GameEngine::GetInstance()->InitializeEngine(1920,1080);
    //we subscribe to the restart engine event
    EventQueue::GetInstance()->SubscribeToVoidEvent(EventQueue::voidEvents::RestartEngine, &RestartEngine);

    //tell the code that we havent createdd a new engine windoe
    bool createdNewEngine = false;
    //while the engine is running
    while (GameEngine::GetInstance()->isGameEngineRunning())
    {
        //calls the updates 
        GameEngine::GetInstance()->Update();
        //renders
        GameEngine::GetInstance()->Render();
        
        //if true, we create a new instance and break out of the loop, so that all memory is reseted.
        if (restartEngine == true)
        {
            CreateNewInstance();
            break;
        }

        //if clicking ctrl+l create a new window
        if (InputsEngine::GetInstance()->GetKeyStates().at(sf::Keyboard::L).pressing && InputsEngine::GetInstance()->GetKeyStates().at(sf::Keyboard::LControl).pressing && createdNewEngine == false)
        {
            createdNewEngine = true;
            CreateNewInstance();
        }
    }

	return 0;
}

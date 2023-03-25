#include "GameEngine.h"
#include "EventQueue.h"
#include <iostream>
#include <Windows.h>


bool restartEngine = false;

void RestartEngine()
{
    restartEngine = true;
}

void CreateNewInstance() {
    STARTUPINFOW si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;

    std::wstring exePath = L"\"";
    WCHAR exeFullPath[MAX_PATH];
    GetModuleFileNameW(NULL, exeFullPath, MAX_PATH);
    exePath += exeFullPath;
    exePath += L"\"";

    std::wstring cmdLine = L"cmd /c start \"\" ";
    cmdLine += exePath;

    if (!CreateProcessW(NULL, &exePath[0], NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
        std::cerr << "Failed to launch new instance: " << GetLastError() << std::endl;
    }
}

int main()
{
    
    GameEngine::GetInstance()->InitializeEngine(1920,1080);

    EventQueue::GetInstance()->SubscribeToVoidEvent(EventQueue::voidEvents::RestartEngine, &RestartEngine);

    float forceToAply = 0.1f;
    while (GameEngine::GetInstance()->isGameEngineRunning())
    {
        GameEngine::GetInstance()->Update();
        GameEngine::GetInstance()->Render();
        
        if (restartEngine == true)
        {
            CreateNewInstance();
            break;
        }
    }

	return 0;
}

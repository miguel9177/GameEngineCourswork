#include "EngineJsonReader.h"
#include <fstream>
#include <iostream>

EngineJsonReader* EngineJsonReader::instance;

EngineJsonReader::EngineJsonReader()
{
    //read the data from the test1.JsonFile
    std::ifstream fileStream("JsonFiles/SceneOfGame.json");
    fileStream >> gameSceneData;
    fileStream.close();
}

EngineJsonReader::~EngineJsonReader()
{
}

EngineJsonReader* EngineJsonReader::GetInstance()
{
    if (!instance)
    {
        instance = new EngineJsonReader();
    }
    return instance;
}

void EngineJsonReader::LoadEditorScene()
{
}

void EngineJsonReader::LoadSceneToPlay()
{
    std::string gameobject1Name = gameSceneData["GameObject"]["Name"].asString();
    std::cout << "NPC1's name is " << gameobject1Name << std::endl << std::endl;
}

void EngineJsonReader::SaveScene()
{
}



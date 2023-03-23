#include "EngineJsonReader.h"
#include <fstream>
#include <iostream>
#include "GameObject.h"
#include "Com_Mesh.h"
#include "Shape_Box.h"
#include "Scene.h"

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
    std::vector<GameObject*> gameObjects;

    //this will loop through all the game objects in the json file
    for (const auto& go_json_ObjectData : gameSceneData["GameObjects"])
    {
#pragma region Get the gameobject information
        //gets the game object name
        std::string go_Name = go_json_ObjectData["Name"].asString();
        //gets the gameobject transform data
        Json::Value go_json_transformData = go_json_ObjectData["Transform"];
        //gets the gameobject position
        Vector2 go_position(
            go_json_transformData["position"]["x"].asFloat(),
            go_json_transformData["position"]["y"].asFloat()
        );
        //gets the gameobject rotation
        float go_rotation = go_json_transformData["rotation"].asFloat();
        //gets the gameobject scale
        Vector2 go_scale(
            go_json_transformData["scale"]["x"].asFloat(),
            go_json_transformData["scale"]["y"].asFloat()
        );
#pragma endregion

        //creates a new gameobject
        GameObject* gameObject = new GameObject(go_Name, new Transform(go_position, go_rotation, go_scale));

        //this gets all components
        Json::Value allcomponents_json_Data = go_json_ObjectData["Components"];
        for (const auto& currentComponent_json_Name : allcomponents_json_Data.getMemberNames())
        {
            //this gets the current component json data
            Json::Value currentComponent_Json_Data = allcomponents_json_Data[currentComponent_json_Name];

            //if the current component is called Com_Mesh
            if (currentComponent_json_Name == "Com_Mesh")
            {
                //finaly in the end i add the com mesh to the gameobject
                gameObject->AddComponent(CreateComMeshFromJsonData(currentComponent_Json_Data));
            }
        }
        //adds the gameobject to the gameobject vector list
        gameObjects.push_back(gameObject);
        //add an object to the scene
        Scene::GetInstance()->AddObject(gameObject);
    } 

}

void EngineJsonReader::SaveScene()
{
}


#pragma region Helper Function

Com_Mesh* EngineJsonReader::CreateComMeshFromJsonData(Json::Value jsonData_)
{
    //gets the texture of the com_mesh
    std::string json_Com_Mesh_texture = jsonData_["Texture"].asString();

    #pragma region Getting the json data
        //gets all the shape box data
        Json::Value json_shapeBox_Data = jsonData_["Shape_Box"];
        //this gets the pos offset of the shape box
        Vector2 shapeBox_posOffset(
            json_shapeBox_Data["positionOffsetFromGameObject"]["x"].asFloat(),
            json_shapeBox_Data["positionOffsetFromGameObject"]["y"].asFloat()
        );
        //this gets the rot offset of the shape box
        float shapeBox_rotOffset = json_shapeBox_Data["rotOffsetFromGameObject"].asFloat();
        //this gets the scale offset of the shape box
        Vector2 shapeBox_scaleOffset(
            json_shapeBox_Data["scaleOffsetFromGameObject"]["x"].asFloat(),
            json_shapeBox_Data["scaleOffsetFromGameObject"]["y"].asFloat()
        );
    #pragma endregion

    #pragma region Creating the component

        Shape_Box* shapeBox = new Shape_Box(shapeBox_posOffset, shapeBox_rotOffset, shapeBox_scaleOffset);
        sf::Texture* texture = new sf::Texture();
        if (!texture->loadFromFile("../Textures/keyboardcat.jpg"))
        {
            std::cout << "Texture did not load!" << "\n" << std::endl;
        }

        Com_Mesh* comMesh = new Com_Mesh(texture, shapeBox);

    #pragma endregion

    return comMesh;
}

#pragma endregion


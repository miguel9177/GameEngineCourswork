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
    //read the data from the test1.JsonFile
    std::ifstream fileStream(gameSceneDataPath);
    fileStream >> gameSceneData;
    fileStream.close();

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
    Json::Value root;
    Json::Value jsonGameObjects(Json::arrayValue);

    for (GameObject* currentGameObject : *Scene::GetInstance()->GetAllObjects())
    {
        Json::Value json_go_data;

#pragma region Save GameObject information
        
        json_go_data["Name"] = currentGameObject->name;

        //this saves all the gameobject transform data
        Transform* go_Transform = currentGameObject->GetTransform();
        json_go_data["Transform"]["position"]["x"] = go_Transform->position.x;
        json_go_data["Transform"]["position"]["y"] = go_Transform->position.y;
        json_go_data["Transform"]["rotation"] = go_Transform->rotation;
        json_go_data["Transform"]["scale"]["x"] = go_Transform->scale.x;
        json_go_data["Transform"]["scale"]["y"] = go_Transform->scale.y;
#pragma endregion

        //this will store all gamobject components
        Json::Value json_go_Components;

        //this gets all the components (std::map<Component::typeOfComponent, std::vector<Component*>>*) and loops through every item
        for (const auto& std_pair_components : *currentGameObject->GetAllComponents())
        {
            //this loops through every component skiping the type of component, since we dont need it
            for (Component* component : std_pair_components.second) 
            {
                //if the component is a Com_Mesh
                if (component->GetUniqueIdIdentifier() == Com_Mesh::uniqueComponentIdIdentifier) 
                {
                    Com_Mesh* comMesh = static_cast<Com_Mesh*>(component);

                    Json::Value json_go_component_ComMesh;
                    json_go_component_ComMesh["Texture"] = comMesh->GetTexturePath();

                    Json::Value jsonShapeBox;
                    jsonShapeBox["positionOffsetFromGameObject"]["x"] = comMesh->GetShape()->positionOffsetFromGameObject.x;
                    jsonShapeBox["positionOffsetFromGameObject"]["y"] = comMesh->GetShape()->positionOffsetFromGameObject.y;
                    jsonShapeBox["rotOffsetFromGameObject"] = comMesh->GetShape()->rotOffsetFromGameObject;
                    jsonShapeBox["scaleOffsetFromGameObject"]["x"] = comMesh->GetShape()->scaleOffsetFromGameObject.x;
                    jsonShapeBox["scaleOffsetFromGameObject"]["y"] = comMesh->GetShape()->scaleOffsetFromGameObject.y;

                    json_go_component_ComMesh["Shape_Box"] = jsonShapeBox;
                    json_go_Components["Com_Mesh"] = json_go_component_ComMesh;
                }
                
            }
        }
        json_go_data["Components"] = json_go_Components;
        jsonGameObjects.append(json_go_data);
    }

    root["GameObjects"] = jsonGameObjects;

    // Write the data to the JSON file
    std::ofstream fileStream(gameSceneDataPath);
    if (fileStream.is_open())
    {
        fileStream << root;
        fileStream.close();
    }
    else
    {
        std::cout << "Error: Unable to open file for writing: " << gameSceneDataPath << std::endl;
    }
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
        Com_Mesh* comMesh = new Com_Mesh(json_Com_Mesh_texture, shapeBox);

    #pragma endregion

    return comMesh;
}

#pragma endregion


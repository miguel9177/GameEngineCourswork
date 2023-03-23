#include "EngineJsonReader.h"
#include <fstream>
#include <iostream>
#include "GameObject.h"
#include "Com_Mesh.h"
#include "Shape_Box.h"
#include "Scene.h"
#include "RigidBody.h"
#include "CircleCollider.h"
#include "SquareCollider.h"


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
        GameObject* currentGameObject = new GameObject(go_Name, new Transform(go_position, go_rotation, go_scale));

        //this gets all components
        Json::Value allcomponents_json_Data = go_json_ObjectData["Components"];
        
        //i store the rb and colls in variables so that i can add the colliders after adding the rigidbody
        RigidBody* rb_currentGameObject = nullptr;
        std::vector<Com_Collider*> allColliders_currentGameObject;
        
        for (const auto& currentComponent_json_Name : allcomponents_json_Data.getMemberNames())
        {
            //this gets the current component json data
            Json::Value currentComponent_Json_Data = allcomponents_json_Data[currentComponent_json_Name];

            //if the current component is called Com_Mesh
            if (currentComponent_json_Name == "Com_Mesh")
            {
                //finaly in the end i add the com mesh to the gameobject
                currentGameObject->AddComponent(CreateComMeshFromJsonData(currentComponent_Json_Data));
            }
            else if (currentComponent_json_Name == "RigidBody")
            {
                //i store the rb since i need to add all colliders to the rb;
                rb_currentGameObject = CreateRigidBodyFromJsonData(currentComponent_Json_Data);
            }
            else if (currentComponent_json_Name == "CircleCollider")
            {
                //i store the gameobject collider in a list so that i can then add all colliders to the rb
                allColliders_currentGameObject.push_back(CreateCircleColliderFromJsonData(currentComponent_Json_Data));
            }
        }

        //if we have a rb in this gameobject, we add it to the gameobject and then add all colliders
        if (rb_currentGameObject != nullptr)
        {
            //adds the rbs to the game object
            currentGameObject->AddComponent(rb_currentGameObject);
            //adds the collider to the gameobject
            for (const auto currentColl : allColliders_currentGameObject)
                currentGameObject->AddComponent(currentColl);
        }

        //add an object to the scene
        Scene::GetInstance()->AddObject(currentGameObject);
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
                //if the component is a Com_Mesh write the com_MEsh into the json variable
                if (component->GetUniqueIdIdentifier() == Com_Mesh::uniqueComponentIdIdentifier) 
                {
                    Com_Mesh* comMesh = static_cast<Com_Mesh*>(component);
                    json_go_Components["Com_Mesh"] = ConvertComMeshToJson(comMesh);
                }
                else if (component->GetUniqueIdIdentifier() == RigidBody::uniqueComponentIdIdentifier)
                {
                    RigidBody* rigidBody = static_cast<RigidBody*>(component);
                    json_go_Components["RigidBody"] = ConvertRigidBodyToJson(rigidBody);
                }
                else if (component->GetUniqueIdIdentifier() == CircleCollider::uniqueComponentIdIdentifier)
                {
                    CircleCollider* circleColl = static_cast<CircleCollider*>(component);
                    json_go_Components["CircleCollider"] = ConvertCircleColliderToJson(circleColl);
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
    std::string json_Com_Mesh_texture = jsonData_["texture"].asString();

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

Json::Value EngineJsonReader::ConvertComMeshToJson(Com_Mesh* comMesh)
{
    Json::Value json_go_component_ComMesh;
    json_go_component_ComMesh["texture"] = comMesh->GetTexturePath();

    Json::Value jsonShapeBox;
    jsonShapeBox["positionOffsetFromGameObject"]["x"] = comMesh->GetShape()->positionOffsetFromGameObject.x;
    jsonShapeBox["positionOffsetFromGameObject"]["y"] = comMesh->GetShape()->positionOffsetFromGameObject.y;
    jsonShapeBox["rotOffsetFromGameObject"] = comMesh->GetShape()->rotOffsetFromGameObject;
    jsonShapeBox["scaleOffsetFromGameObject"]["x"] = comMesh->GetShape()->scaleOffsetFromGameObject.x;
    jsonShapeBox["scaleOffsetFromGameObject"]["y"] = comMesh->GetShape()->scaleOffsetFromGameObject.y;

    json_go_component_ComMesh["Shape_Box"] = jsonShapeBox;
    return json_go_component_ComMesh;
}


RigidBody* EngineJsonReader::CreateRigidBodyFromJsonData(Json::Value jsonData_)
{
#pragma region Getting the json data
    RigidBodySettings rbSettings;
    rbSettings.type = static_cast<RigidBodyType>(jsonData_["rbSettings_type"].asInt());
    rbSettings.drag = jsonData_["rbSettings_drag"].asFloat();
    rbSettings.angularDrag = jsonData_["rbSettings_angularDrag"].asFloat();
    rbSettings.allowSleep = jsonData_["rbSettings_allowSleep"].asBool();
    rbSettings.awake = jsonData_["rbSettings_awake"].asBool();
    rbSettings.freezeRotation = jsonData_["rbSettings_freezeRotation"].asBool();
    rbSettings.important = jsonData_["rbSettings_important"].asBool();
    rbSettings.gravityScale = jsonData_["rbSettings_gravityScale"].asFloat();
    bool rb_useGravity = jsonData_["rb_useGravity"].asBool();
#pragma endregion

#pragma region Creating the component
    RigidBody* rigidBody = new RigidBody(rbSettings);
    rigidBody->useGravity = rb_useGravity;
#pragma endregion

    return rigidBody;
}

Json::Value EngineJsonReader::ConvertRigidBodyToJson(RigidBody* rb)
{
    Json::Value json_go_component_RigidBody;

    json_go_component_RigidBody["rbSettings_type"] = static_cast<int>(rb->GetRbType());
    json_go_component_RigidBody["rbSettings_drag"] = rb->GetDrag();
    json_go_component_RigidBody["rbSettings_angularDrag"] = rb->GetAngularDrag();
    json_go_component_RigidBody["rbSettings_allowSleep"] = rb->GetAllowSleep();
    json_go_component_RigidBody["rbSettings_awake"] = rb->GetAwake();
    json_go_component_RigidBody["rbSettings_freezeRotation"] = rb->GetFreezedRotation();
    json_go_component_RigidBody["rbSettings_important"] = rb->IsImportant();
    json_go_component_RigidBody["rbSettings_gravityScale"] = rb->GetGravityScale();
    json_go_component_RigidBody["rb_useGravity"] = rb->useGravity;

    return json_go_component_RigidBody;
}

CircleCollider* EngineJsonReader::CreateCircleColliderFromJsonData(Json::Value jsonData_)
{
#pragma region Getting the json data
    float circleColl_radius = jsonData_["radius"].asFloat();
    Vector2 circleColl_posOffset(
        jsonData_["posOffset"]["x"].asFloat(),
        jsonData_["posOffset"]["y"].asFloat()
    );
    float circleColl_offsetAngle = jsonData_["offsetAngle"].asFloat();
    float circleColl_mass = jsonData_["mass"].asFloat();
    float circleColl_friction = jsonData_["friction"].asFloat();
    float circleColl_bounciness = jsonData_["bouciness"].asFloat();
#pragma endregion

#pragma region Creating the component
    CircleCollider* circleCollider = new CircleCollider(circleColl_radius, circleColl_posOffset, circleColl_offsetAngle, circleColl_mass, circleColl_friction, circleColl_bounciness);
#pragma endregion

    return circleCollider;
}

Json::Value EngineJsonReader::ConvertCircleColliderToJson(CircleCollider* circleColl)
{
    Json::Value json_go_component_CircleColl;

#pragma region Saving the json data
    json_go_component_CircleColl["radius"] = circleColl->GetRadius();
    json_go_component_CircleColl["posOffset"]["x"] = circleColl->GetPosOffset().x;
    json_go_component_CircleColl["posOffset"]["y"] = circleColl->GetPosOffset().y;
    json_go_component_CircleColl["offsetAngle"] = circleColl->GetOffsetAngle();
    json_go_component_CircleColl["mass"] = circleColl->GetMass();
    json_go_component_CircleColl["friction"] = circleColl->GetFriction();
    json_go_component_CircleColl["bouciness"] = circleColl->GetBouciness();
#pragma endregion

    return json_go_component_CircleColl;
}

#pragma endregion


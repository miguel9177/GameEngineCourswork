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
#include "AllUserScipts/ScriptLoaderManager.h"
#include "AudioPlayer.h"

EngineJsonReader* EngineJsonReader::instance;

EngineJsonReader::EngineJsonReader()
{
   
}

EngineJsonReader::~EngineJsonReader()
{
}

//this gets the instance since this is a singleton
EngineJsonReader* EngineJsonReader::GetInstance()
{
    if (!instance)
    {
        instance = new EngineJsonReader();
    }
    return instance;
}

//this loads editor scene, reading the objects from the json
void EngineJsonReader::LoadEditorScene()
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
        //we want to add the scripts as the last thing, since we dont know its depencies, so if we put it in last the character will already have everything 
        std::vector<ScriptBehaviour*>allScripts_currentGameObject;

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
                std::vector<CircleCollider*> newColliders = CreateCircleColliderFromJsonData(currentComponent_Json_Data);
                //i store the gameobject collider in a list so that i can then add all colliders to the rb
                allColliders_currentGameObject.insert(allColliders_currentGameObject.end(), newColliders.begin(), newColliders.end());
            }
            else if (currentComponent_json_Name == "SquareCollider")
            {
                std::vector<SquareCollider*> newColliders = CreateSquareColliderFromJsonData(currentComponent_Json_Data);
                //i store the gameobject collider in a list so that i can then add all colliders to the rb
                allColliders_currentGameObject.insert(allColliders_currentGameObject.end(), newColliders.begin(), newColliders.end());
            }
            else if (currentComponent_json_Name == "AudioPlayer")
            {
                //finaly in the end i add the audio player to the gameobject
                currentGameObject->AddComponent(CreateAudioPlayerFromJsonData(currentComponent_Json_Data));
            }
            else if (currentComponent_json_Name == "ScriptBehaviour")
            {
                std::vector<ScriptBehaviour*> newScripts = CreateScriptBehaviourFromJsonData(currentComponent_Json_Data);
                allScripts_currentGameObject.insert(allScripts_currentGameObject.end(), newScripts.begin(), newScripts.end());
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
        //after adding everything, we add all scripts
        for (const auto currentScript : allScripts_currentGameObject)
            currentGameObject->AddComponent(currentScript);

        //add an object to the scene
        Scene::GetInstance()->AddObject(currentGameObject);
    }
}

//this loads play scene, reading the objects from the json
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
        //we want to add the scripts as the last thing, since we dont know its depencies, so if we put it in last the character will already have everything 
        std::vector<ScriptBehaviour*>allScripts_currentGameObject;
        
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
                std::vector<CircleCollider*> newColliders = CreateCircleColliderFromJsonData(currentComponent_Json_Data);
                //i store the gameobject collider in a list so that i can then add all colliders to the rb
                allColliders_currentGameObject.insert(allColliders_currentGameObject.end(), newColliders.begin(), newColliders.end()); 
            }
            else if (currentComponent_json_Name == "SquareCollider")
            {
                std::vector<SquareCollider*> newColliders = CreateSquareColliderFromJsonData(currentComponent_Json_Data);
                //i store the gameobject collider in a list so that i can then add all colliders to the rb
                allColliders_currentGameObject.insert(allColliders_currentGameObject.end(), newColliders.begin(), newColliders.end());
            }
            else if (currentComponent_json_Name == "AudioPlayer")
            {
                //finaly in the end i add the audio player to the gameobject
                currentGameObject->AddComponent(CreateAudioPlayerFromJsonData(currentComponent_Json_Data));
            }
            else if (currentComponent_json_Name == "ScriptBehaviour")
            {
                std::vector<ScriptBehaviour*> newScripts = CreateScriptBehaviourFromJsonData(currentComponent_Json_Data);
                allScripts_currentGameObject.insert(allScripts_currentGameObject.end(), newScripts.begin(), newScripts.end());
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
        //after adding everything, we add all scripts
        for (const auto currentScript : allScripts_currentGameObject)
            currentGameObject->AddComponent(currentScript);

        //add an object to the scene
        Scene::GetInstance()->AddObject(currentGameObject);
    } 

}

//this saves the scene
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
                    json_go_Components["CircleCollider"].append(ConvertCircleColliderToJson(circleColl));
                }
                else if (component->GetUniqueIdIdentifier() == SquareCollider::uniqueComponentIdIdentifier)
                {
                    SquareCollider* squareColl = static_cast<SquareCollider*>(component);
                    json_go_Components["SquareCollider"].append(ConvertSquareColliderToJson(squareColl));
                }
                else if (component->GetUniqueIdIdentifier() == AudioPlayer::uniqueComponentIdIdentifier)
                {
                    AudioPlayer* audioPlayer = static_cast<AudioPlayer*>(component);
                    json_go_Components["AudioPlayer"] = ConvertAudioPlayerToJson(audioPlayer);
                }
                else if (component->GetUniqueIdIdentifier() > ScriptBehaviour::minimumUniqueComponentIdIdentifier)
                {
                    ScriptBehaviour* scriptBehaviour = static_cast<ScriptBehaviour*>(component);
                    json_go_Components["ScriptBehaviour"].append(ConvertScriptBehaviourToJson(scriptBehaviour));
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


std::vector<CircleCollider*> EngineJsonReader::CreateCircleColliderFromJsonData(Json::Value jsonData_)
{
    std::vector<CircleCollider*> allCircleColliders;
    for (Json::Value circleColliderData : jsonData_)
    {
#pragma region Getting the json data
        float circleColl_radius = circleColliderData["radius"].asFloat();
        Vector2 circleColl_posOffset(
            circleColliderData["posOffset"]["x"].asFloat(),
            circleColliderData["posOffset"]["y"].asFloat()
        );
        float circleColl_offsetAngle = circleColliderData["offsetAngle"].asFloat();
        float circleColl_mass = circleColliderData["mass"].asFloat();
        float circleColl_friction = circleColliderData["friction"].asFloat();
        float circleColl_bounciness = circleColliderData["bouciness"].asFloat();
#pragma endregion

#pragma region Creating the component
        CircleCollider* circleCollider = new CircleCollider(circleColl_radius, circleColl_posOffset, circleColl_offsetAngle, circleColl_mass, circleColl_friction, circleColl_bounciness);
#pragma endregion

        allCircleColliders.push_back(circleCollider);
    }
    return allCircleColliders;

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


std::vector<SquareCollider*> EngineJsonReader::CreateSquareColliderFromJsonData(Json::Value jsonData_)
{
    std::vector<SquareCollider*> allSquareColliders;
    for (Json::Value squareColliderData : jsonData_)
    {
    #pragma region Getting the json data
        Vector2 squareColl_halfSize(
            squareColliderData["halfSize"]["x"].asFloat(),
            squareColliderData["halfSize"]["y"].asFloat()
        );
        Vector2 squareColl_posOffset(
            squareColliderData["posOffset"]["x"].asFloat(),
            squareColliderData["posOffset"]["y"].asFloat()
        );
        float squareColl_offsetAngle = squareColliderData["offsetAngle"].asFloat();
        float squareColl_mass = squareColliderData["mass"].asFloat();
        float squareColl_friction = squareColliderData["friction"].asFloat();
        float squareColl_bounciness = squareColliderData["bouciness"].asFloat();
    #pragma endregion

    #pragma region Creating the component
        SquareCollider* squareCollider = new SquareCollider(squareColl_halfSize, squareColl_posOffset, squareColl_offsetAngle, squareColl_mass, squareColl_friction, squareColl_bounciness);
    #pragma endregion

        allSquareColliders.push_back(squareCollider);
    }
    return allSquareColliders;
}

Json::Value EngineJsonReader::ConvertSquareColliderToJson(SquareCollider* squareColl)
{
    Json::Value json_go_component_SquareColl;

#pragma region Saving the json data
    json_go_component_SquareColl["halfSize"]["x"] = squareColl->GetHalfSize().x;
    json_go_component_SquareColl["halfSize"]["y"] = squareColl->GetHalfSize().y;
    json_go_component_SquareColl["posOffset"]["x"] = squareColl->GetPosOffset().x;
    json_go_component_SquareColl["posOffset"]["y"] = squareColl->GetPosOffset().y;
    json_go_component_SquareColl["offsetAngle"] = squareColl->GetOffsetAngle();
    json_go_component_SquareColl["mass"] = squareColl->GetMass();
    json_go_component_SquareColl["friction"] = squareColl->GetFriction();
    json_go_component_SquareColl["bouciness"] = squareColl->GetBouciness();
#pragma endregion

    return json_go_component_SquareColl;
}

AudioPlayer* EngineJsonReader::CreateAudioPlayerFromJsonData(Json::Value jsonData_)
{
    //gets the texture of the com_mesh
    std::string json_audioPlayer_path = jsonData_["soundPath"].asString();

#pragma region Creating the component

    AudioPlayer* audioPlayer = new AudioPlayer(json_audioPlayer_path);

#pragma endregion

    return audioPlayer;
}

Json::Value EngineJsonReader::ConvertAudioPlayerToJson(AudioPlayer* audioPlayer)
{
    Json::Value json_go_component_AudioSource;
    json_go_component_AudioSource["soundPath"] = audioPlayer->GetAudioPath();
    return json_go_component_AudioSource;
}


std::vector<ScriptBehaviour*> EngineJsonReader::CreateScriptBehaviourFromJsonData(Json::Value jsonData_)
{
    std::vector<ScriptBehaviour*> allScriptBehaviours;
    for (Json::Value scriptData : jsonData_)
    {
#pragma region Getting the json data
        float scriptBehaviour_uniqueId = scriptData["uniqueIdIdentifier"].asUInt();
#pragma endregion

#pragma region Creating the component
        ScriptBehaviour* scriptBehaviour = ScriptLoaderManager::GetInstance()->GetScript(scriptBehaviour_uniqueId);
#pragma endregion

        allScriptBehaviours.push_back(scriptBehaviour);
    }
    return allScriptBehaviours;
}

Json::Value EngineJsonReader::ConvertScriptBehaviourToJson(ScriptBehaviour* scriptBehaviour)
{
    Json::Value json_go_component_ScriptBehaviour;

#pragma region Saving the json data
    json_go_component_ScriptBehaviour["uniqueIdIdentifier"] = scriptBehaviour->GetUniqueIdIdentifier();
#pragma endregion

    return json_go_component_ScriptBehaviour;
}
#pragma endregion


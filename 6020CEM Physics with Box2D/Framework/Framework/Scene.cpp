#include "Scene.h"
#include "ScriptBehaviour.h"

Scene* Scene::instance;

Scene::Scene()
{
    std::function<void()> onEnteredPlayModeCallback = std::bind(&Scene::EnteredPlayMode, this);
    EventQueue::GetInstance()->SubscribeToVoidEvent(EventQueue::voidEvents::EnteredPlayMode, onEnteredPlayModeCallback);

    std::function<void()> onEnteredEditModeCallback = std::bind(&Scene::EnteredEditMode, this);
    EventQueue::GetInstance()->SubscribeToVoidEvent(EventQueue::voidEvents::EnteredEditMode, onEnteredEditModeCallback);
}

Scene::~Scene()
{
}

Scene* Scene::GetInstance()
{
    if (!instance)
    {
        instance = new Scene();
    }
    return instance;
}

void Scene::Update()
{
    for (ScriptBehaviour* scriptBehaviour : allScriptBehaviours)
    {
        scriptBehaviour->Update();
    }
}

//TODO: IMPROVE THIS FUNCTION, DO ONE LOOP ONLY AND IF ONE TYPE, ADD TO THAT ONE, INSTEAD OF HAVING MULTIPLE LOOPS
//this adds an object to the scene, it will alse store its meshes and rb
void Scene::AddObject(GameObject* gameObject)
{
    allSceneGameObjects.push_back(gameObject);

    //this will get all the mesh components of the gameObject
    std::vector<Component*> allMeshComponents = gameObject->GetAllComponentsOfType(Component::typeOfComponent::Mesh);

    //this loops through all the mesh componments
    for (std::vector<Component*>::iterator it = allMeshComponents.begin(); it != allMeshComponents.end(); ++it)
    {
        Component* component = *it;
        //if the component is a Com_Mesh, add it to the allMeshesList
        if (component->GetUniqueIdIdentifier() == Com_Mesh::uniqueComponentIdIdentifier)
        {
            allMeshes.push_back(static_cast<Com_Mesh*>(component));
        }
    }
    
    //if the game object has a rigidbody, add it to the rigidbody scene list
    if(gameObject->HasRigidBody())
        allRigidBodys.push_back(static_cast<RigidBody*>(gameObject->TryGetRigidBody()));

    //this will get all the script behaviours components of the gameObject
    std::vector<Component*> allScriptComponents = gameObject->GetAllComponentsOfType(Component::typeOfComponent::ScriptBehaviour);

    //this loops through all the mesh componments
    for (std::vector<Component*>::iterator it = allScriptComponents.begin(); it != allScriptComponents.end(); ++it)
    {
        Component* component = *it;
        //if the component is a Com_Mesh, add it to the allMeshesList
        if (component->GetUniqueIdIdentifier() > ScriptBehaviour::minimumUniqueComponentIdIdentifier)
        {
            allScriptBehaviours.push_back(static_cast<ScriptBehaviour*>(component));
        }
    }
}

std::vector<GameObject*>* Scene::GetAllObjects()
{
    return &allSceneGameObjects;
}

//this will get all the meshes from the scene
std::vector<Com_Mesh*>* Scene::GetAllMeshes()
{
    return &allMeshes;
}

//this will return all rbs on the scene
std::vector<RigidBody*>* Scene::GetAllRigidBodys()
{
    return &allRigidBodys;
}

std::vector<ScriptBehaviour*>* Scene::GetAllScripts()
{
    return &allScriptBehaviours;
}

#pragma region Functionality functions

//this is called if we entered play mode (in here we load all the player scripts, rigidbodys and let the user play the game)
void Scene::EnteredPlayMode()
{
    DeleteAllGameObjects();
}

//this is called if we entered Edit mode (in here we load all the player Meshes without its scripts)
void Scene::EnteredEditMode()
{
    DeleteAllGameObjects();
}

#pragma endregion

#pragma region Utility Functions

void Scene::DeleteAllGameObjects()
{
    // Delete all GameObjects
    for (GameObject* gameObject : allSceneGameObjects) {
        delete gameObject;
    }
    allSceneGameObjects.clear();
    allMeshes.clear();
    allRigidBodys.clear();
    allScriptBehaviours.clear();
}

#pragma endregion


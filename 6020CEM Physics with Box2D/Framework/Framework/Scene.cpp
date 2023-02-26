#include "Scene.h"

Scene* Scene::instance;

Scene::Scene()
{
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
    
}

//this adds an object to the scene, it will alse store its meshes and rb
void Scene::AddObject(GameObject* gameObject)
{
    allSceneGameObjects.push_back(gameObject);

    //this will get all the mesh components of the gameObject
    std::vector<Component*> allMeshComponents = gameObject->GetAllComponentsOfType(Component::typeOfComponent::Mesh);

    // Loop through the vector of components
    for (std::vector<Component*>::iterator it = allMeshComponents.begin(); it != allMeshComponents.end(); ++it)
    {
        // do something with each component in the vector
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

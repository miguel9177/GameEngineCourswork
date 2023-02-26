#pragma once
#include "CommunImports.h"
#include "SceneObjectsImports.h"
#include "Com_Mesh.h"

//this is a singleton, and stores the scene script
class Scene
{
private:
    static Scene* instance;
    std::vector<GameObject*> allSceneGameObjects;
    std::vector<Com_Mesh*> allMeshes;
    std::vector<RigidBody*> allRigidBodys;

    Scene();
    ~Scene();
public:
    //this gives the instance of the scene, and if theres no instance of it, it creates one
    static Scene* GetInstance();

    void Update();

    void AddObject(GameObject* gameObject);

    //this will get all the meshes from the scene
    std::vector<Com_Mesh*>* GetAllMeshes();

    //this will get all the meshes from the scene
    std::vector<RigidBody*>* GetAllRigidBodys();
};


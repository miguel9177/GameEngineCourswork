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

    Scene();
    ~Scene();
public:
    //this gives the instance of the scene, and if theres no instance of it, it creates one
    static Scene* GetInstance();

    void Update();

    void AddObject(GameObject* gameObject);
};


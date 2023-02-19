#pragma once
#include "CommunImports.h"
#include "SceneObjectsImports.h"

//this is a singleton, and stores the scene script
class Scene
{
private:
    static Scene* instance;
    std::vector<GameObject*> allSceneGameObjects;

    Scene();
    ~Scene();
public:
    //this gives the instance of the scene, and if theres no instance of it, it creates one
    static Scene* GetInstance();

    void Update();

    void AddObject(GameObject* gameObject);
};


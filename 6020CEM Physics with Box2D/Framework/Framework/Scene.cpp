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

void Scene::AddObject(GameObject* gameObject)
{
    allSceneGameObjects.push_back(gameObject);
    //if(gameObject->)
}

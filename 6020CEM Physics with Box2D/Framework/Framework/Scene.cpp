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

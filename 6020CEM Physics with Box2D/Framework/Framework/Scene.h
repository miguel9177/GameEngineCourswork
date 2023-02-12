#pragma once

//this is a singleton, and stores the scene script
class Scene
{
private:
    static Scene* instance;
    Scene();

    ~Scene();
public:
    //this gives the instance of the scene, and if theres no instance of it, it creates one
    static Scene* GetInstance();

    void Update();
};


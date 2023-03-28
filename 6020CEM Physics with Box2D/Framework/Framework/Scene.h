#pragma once
#include "CommunImports.h"
#include "SceneObjectsImports.h"
#include "Com_Mesh.h"

class ScriptBehaviour;
//this is a singleton, and stores the scene script
class Scene
{
private:
    static Scene* instance;
    std::vector<GameObject*> allSceneGameObjects;
    std::vector<Com_Mesh*> allMeshes;
    std::vector<RigidBody*> allRigidBodys;
    std::vector<ScriptBehaviour*> allScriptBehaviours;

    Scene();
    ~Scene();

    //we need to know if its the first update or not, since if it is, we want it to do the late start function
    bool firstUpdate = true;
public:
    //this gives the instance of the scene, and if theres no instance of it, it creates one
    static Scene* GetInstance();

    void Update();

    void AddObject(GameObject* gameObject);

    //this will get all the meshes from the scene
    std::vector<GameObject*>* GetAllObjects();

    //this will get all the meshes from the scene
    std::vector<Com_Mesh*>* GetAllMeshes();

    //this will get all the rigidbodys from the scene
    std::vector<RigidBody*>* GetAllRigidBodys();

    //this will get all the scripts from the scene
    std::vector<ScriptBehaviour*>* GetAllScripts();

private:

#pragma region Functioality Functions

    void EnteredPlayMode();
    void EnteredEditMode();

#pragma endregion

#pragma region Utility Functions
    
    void DeleteAllGameObjects();

#pragma endregion
};


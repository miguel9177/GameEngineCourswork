#pragma once
#include <jsoncpp/json/json.h>
#include <vector>

class Com_Mesh;
class RigidBody;
class CircleCollider;
class SquareCollider;
class ScriptBehaviour;
class AudioPlayer;
class EngineJsonReader
{
private:
	//this is the instance since this is a singleton
	static EngineJsonReader* instance;
	EngineJsonReader();
	~EngineJsonReader();

	//this is the path for the scene json
	const std::string gameSceneDataPath = "JsonFiles/SceneOfGame.json";
	//this stores the game scene data
	Json::Value gameSceneData;
public:
	static EngineJsonReader* GetInstance();

#pragma region reading Json functions
	/// <summary>
	/// this loads a scene that doesnt have player interaction, no script has been initialized and theres no rigidbodys aswell
	/// </summary>
	void LoadEditorScene();
	/// <summary>
	/// this loads a scene that does have player interaction, has scripts and has been initialized and theres rigidbodys aswell
	/// </summary>
	void LoadSceneToPlay();
#pragma endregion

#pragma region writing Json functions
	void SaveScene();
#pragma endregion

//the create functions create the desired object and returns them, the convert receives an object and returns their json equivalent
#pragma region Helper Functions
	Com_Mesh* CreateComMeshFromJsonData(Json::Value jsonData_);
	Json::Value ConvertComMeshToJson(Com_Mesh* comMesh);

	RigidBody* CreateRigidBodyFromJsonData(Json::Value jsonData_);
	Json::Value ConvertRigidBodyToJson(RigidBody* rb);

	std::vector<CircleCollider*> CreateCircleColliderFromJsonData(Json::Value jsonData_);
	Json::Value ConvertCircleColliderToJson(CircleCollider* circleColl);

	std::vector<SquareCollider*> CreateSquareColliderFromJsonData(Json::Value jsonData_);
	Json::Value ConvertSquareColliderToJson(SquareCollider* circleColl);

	AudioPlayer* CreateAudioPlayerFromJsonData(Json::Value jsonData_);
	Json::Value ConvertAudioPlayerToJson(AudioPlayer* audioPlayer);

	std::vector<ScriptBehaviour*> CreateScriptBehaviourFromJsonData(Json::Value jsonData_);
	Json::Value ConvertScriptBehaviourToJson(ScriptBehaviour* scriptBehaviour);
#pragma endregion

};


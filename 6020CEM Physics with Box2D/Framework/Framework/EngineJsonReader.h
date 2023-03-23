#pragma once
#include <jsoncpp/json/json.h>

class Com_Mesh;
class EngineJsonReader
{
private:
	static EngineJsonReader* instance;
	EngineJsonReader();
	~EngineJsonReader();

	const std::string gameSceneDataPath = "JsonFiles/SceneOfGame.json";
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

#pragma region Helper Functions
	Com_Mesh* CreateComMeshFromJsonData(Json::Value jsonData_);
#pragma endregion

};


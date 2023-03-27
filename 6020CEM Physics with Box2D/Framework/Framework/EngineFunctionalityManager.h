#pragma once

class UiScreenView_btnImage;
class GameObject;
class EngineFunctionalityManager
{
private:

#pragma region Ui buttons and images
	UiScreenView_btnImage* uiBtnImg_PlayButton;
	UiScreenView_btnImage* uiBtnImg_DebugButton;
	UiScreenView_btnImage* uiBtnImg_StopButton;
	UiScreenView_btnImage* uiBtnImg_SaveButton;
#pragma endregion

	static EngineFunctionalityManager* instance;
	EngineFunctionalityManager();
	~EngineFunctionalityManager();
	
#pragma region private Event Dependent function
	
	void OnPlayButtonClicked();
	void OnDebugButtonClicked();
	void OnStopButtonClicked();
	void OnSaveButtonClicked();
	void LeftMousePressed();
	void LeftMouseReleased();
	void MiddleMousePressed();
	void MiddleMouseReleased();
	void GameObjectButtonClicked(GameObject* objButtonClicked);
#pragma endregion
	
	GameObject* objBeingDragged;
	
public:
	//this will store the state of the game engine
	enum State {editMode, playMode};
	//this gives the instance of the EngineFunctionality Manager, and if theres no instance of it, it creates one
	static EngineFunctionalityManager* GetInstance();
	void CreateEngineUI();
	void Update();
	void Start();
	inline State GetEngineState() { return state; };

#pragma region helper Functions

	GameObject* GetObjectAtMousePos();

	void CreateTopBarUi();

	void CreateLeftBarUi();

	void CreateRightBarUi();

#pragma endregion
private:
	State state = State::editMode;
};


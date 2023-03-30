#pragma once

class UiScreenView_btnImage;
class GameObject;

//this class does all the functionality of the engine
class EngineFunctionalityManager
{
private:

#pragma region Ui buttons and images
	UiScreenView_btnImage* uiBtnImg_PlayButton;
	UiScreenView_btnImage* uiBtnImg_DebugButton;
	UiScreenView_btnImage* uiBtnImg_StopButton;
	UiScreenView_btnImage* uiBtnImg_SaveButton;
#pragma endregion

	//i have a instace since this is a singleton
	static EngineFunctionalityManager* instance;
	EngineFunctionalityManager();
	~EngineFunctionalityManager();
	
#pragma region private Event Dependent function
	
	//this are events that the engine functionality is subscribed to, this functions will be called by events
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
	
	//this will store the object that is current being ddragged
	GameObject* objBeingDragged;
	
public:
	//this will store the state of the game engine
	enum State {editMode, playMode};
	//this gives the instance of the EngineFunctionality Manager, and if theres no instance of it, it creates one
	static EngineFunctionalityManager* GetInstance();
	//this creates all the ui of the engine, using the helper functuions
	void CreateEngineUI();
	void Update();
	void Start();
	inline State GetEngineState() { return state; };

#pragma region helper Functions

	//this gets the object at the moiuse position (returns null if no object is present)
	GameObject* GetObjectAtMousePos();

	//this healper functions creates the top ui
	void CreateTopBarUi();

	//this healper functions creates the left bar ui
	void CreateLeftBarUi();

#pragma endregion

private:
	//this stores the state of the engine
	State state = State::editMode;
};


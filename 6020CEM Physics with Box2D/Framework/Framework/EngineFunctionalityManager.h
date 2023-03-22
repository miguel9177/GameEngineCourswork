#pragma once

class UiScreenView_btnImage;
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

#pragma endregion

public:
	//this gives the instance of the EngineFunctionality Manager, and if theres no instance of it, it creates one
	static EngineFunctionalityManager* GetInstance();
	void CreateEngineUI();
	void Update();
};


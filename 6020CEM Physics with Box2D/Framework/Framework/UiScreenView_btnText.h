#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Transform.h"
#include <functional>
#include "UiScreenView_Text.h"

class GameObject;
class UiScreenView_btnText
{
private:
	//stores the sprites
	sf::Sprite sprite;
	//stores the texture
	sf::Texture* texture;
	UiScreenView_Text* ui_text;
	//stores the transform
	Transform* transform;
	//stores the text
	Transform* textTansform;
	//gets true if its being pressed
	bool pressing = false;
	//true if its being drawned
	bool isUiBeingDrawned = false;
	//true if world object
	bool worldObject = false;

	//struct with our info
	struct uiTransformInformation
	{
		Vector2 pos;
		Vector2 offset;
		float rot;
		Vector2 scale;
	};
	uiTransformInformation uiTransformInformation;

	//stores all the subscribers on the button press
	std::vector<std::function<void()>> allSubscribedOnButtonPressEvent;
	//stores all the subscribers on the button released
	std::vector<std::function<void()>> allSubscribedOnButtonReleasedEvent;

public:
	UiScreenView_btnText(sf::Texture* _newImage, Transform* _transform, std::string _textToDisplay, Transform* _textTransform, UiScreenView_Text* _ui_text, bool _worldObject = false);
	~UiScreenView_btnText();

#pragma region Settters

	void SetFont(sf::Font _newFont);
	void SetText(sf::String _newText);
	void SetFontSize(float _newSize);
	void SetTextColor(sf::Color _newColor);
	void SetTextUiPosition(Vector2 _newPos, Vector2 _offset = Vector2(0, 0));
	void SetTextUiRotation(float _newRot);
	void SetTextUiScale(Vector2 _newScale);
	void SetUiPosition(Vector2 _newPos, Vector2 _offset = Vector2(0, 0));
	void SetUiRotation(float _newRot);
	void SetUiScale(Vector2 _newScale);

#pragma endregion


#pragma region Getters

	sf::Sprite GetComponentToDraw();
	bool isButtonBeingHovered();
	inline bool IsBeingDrawned() { return isUiBeingDrawned; }

#pragma endregion
	
	//adds the ui on the screen
	void AddUiToScreen();
	//removes the ui on the screen
	void RemoveUiFromScreen();
	void Update();

	//this functions do the subscribing and unsubscribing of the events
	void SubscribeToBtnOnPressEvent(std::function<void()> function);
	void UnsubscribeToBtnOnPressEvent(std::function<void()> function);
	void SubscribeToBtnOnReleasedEvent(std::function<void()> function);
	void UnsubscribeToBtnOnReleasedEvent(std::function<void()> function);

	//this functions do the subscribing and unsubscribing of the events
	void SubscribeToBtnOnPressEvent(GameObject* obj, std::function<void(GameObject* obj)> function);
	void UnsubscribeToBtnOnPressEvent(GameObject* obj, std::function<void(GameObject* obj)> function);
	void SubscribeToBtnOnReleasedEvent(GameObject* obj, std::function<void(GameObject* obj)> function);
	void UnsubscribeToBtnOnReleasedEvent(GameObject* obj, std::function<void(GameObject* obj)> function);

private:
	//this functions invokes the events
	void InvokeButtonPressedEvent();
	void InvokeButtonReleasedEvent();
	void UserPressedLeftMouseButton();
	void UserReleasedLeftMouseButton();
};


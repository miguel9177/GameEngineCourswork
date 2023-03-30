#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Transform.h"
#include <functional>
class UiScreenView_btnImage
{
private:
	//stores the sprites
	sf::Sprite sprite;
	//stores the texture
	sf::Texture* texture;
	//stores the transform
	Transform* transform;
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
	UiScreenView_btnImage(sf::Texture* _newImage, Transform* _transform, bool _worldObject = false);
	~UiScreenView_btnImage();

#pragma region setters
	
	void SetUiPosition(Vector2 _newPos, Vector2 _offset = Vector2(0, 0));
	void SetUiRotation(float _newRot);
	void SetUiScale(Vector2 _newScale);
	void SetTexture(sf::Texture texture_);

#pragma endregion

#pragma region Getters

	sf::Sprite GetComponentToDraw();
	bool isButtonBeingHovered();
	inline bool IsBeingDrawned() { return isUiBeingDrawned; }

#pragma endregion

	//adds the ui on the screen
	void AddUiToScreen();
	//removes the ui from the screen
	void RemoveUiFromScreen();
	
	void Update();

	//subcribes to the press
	void SubscribeToBtnOnPressEvent(std::function<void()> function);
	//unsubscribes to the press
	void UnsubscribeToBtnOnPressEvent(std::function<void()> function);
	//subcribes to the release
	void SubscribeToBtnOnReleasedEvent(std::function<void()> function);
	//unsubscribes to the release
	void UnsubscribeToBtnOnReleasedEvent(std::function<void()> function);

private:
	//invokes the events
	void InvokeButtonPressedEvent();
	void InvokeButtonReleasedEvent();
	void UserPressedLeftMouseButton();
	void UserReleasedLeftMouseButton();
};

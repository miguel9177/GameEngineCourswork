#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Transform.h"
#include <functional>
#include "UiScreenView_Text.h"

class UiScreenView_btnText
{
private:
	sf::Sprite sprite;
	sf::Texture* texture;
	UiScreenView_Text ui_text;
	Transform* transform;
	bool pressing = false;
	bool isUiBeingDrawned = false;

	std::vector<std::function<void()>> allSubscribedOnButtonPressEvent;
	std::vector<std::function<void()>> allSubscribedOnButtonReleasedEvent;

public:
	UiScreenView_btnText(sf::Texture* _newImage, Transform* _transform, std::string _textToDisplay);
	~UiScreenView_btnText();
	void SetUiPosition(Vector2 _newPos);
	void SetUiRotation(float _newRot);
	void SetUiScale(Vector2 _newScale);
	sf::Sprite GetComponentToDraw();
	bool isButtonBeingHovered();
	void AddUiToScreen();
	void RemoveUiFromScreen();
	inline bool IsBeingDrawned() { return isUiBeingDrawned; }

	void SubscribeToBtnOnPressEvent(std::function<void()> function);
	void UnsubscribeToBtnOnPressEvent(std::function<void()> function);
	void SubscribeToBtnOnReleasedEvent(std::function<void()> function);
	void UnsubscribeToBtnOnReleasedEvent(std::function<void()> function);

private:
	void InvokeButtonPressedEvent();
	void InvokeButtonReleasedEvent();
	void UserPressedLeftMouseButton();
	void UserReleasedLeftMouseButton();
};


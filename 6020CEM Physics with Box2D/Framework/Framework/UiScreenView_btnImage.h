#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Transform.h"
#include <functional>
class UiScreenView_btnImage
{
private:
	sf::Sprite sprite;
	sf::Texture* texture;
	Transform* transform;
	bool pressing = false;
	
	std::vector<std::function<void()>> allSubscribedOnButtonPressEvent;
	std::vector<std::function<void()>> allSubscribedOnButtonReleasedEvent;

public:
	UiScreenView_btnImage(sf::Texture* _newImage, Transform* _transform);
	~UiScreenView_btnImage();
	void SetUiPosition(Vector2 _newPos);
	void SetUiRotation(float _newRot);
	void SetUiScale(Vector2 _newScale);
	sf::Sprite GetComponentToDraw();
	bool isButtonBeingHovered();

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

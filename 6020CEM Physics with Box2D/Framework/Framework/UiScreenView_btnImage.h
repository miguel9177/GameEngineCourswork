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
	bool isUiBeingDrawned = false;
	bool worldObject = false;

	struct uiTransformInformation
	{
		Vector2 pos;
		Vector2 offset;
		float rot;
		Vector2 scale;
	};
	uiTransformInformation uiTransformInformation;

	std::vector<std::function<void()>> allSubscribedOnButtonPressEvent;
	std::vector<std::function<void()>> allSubscribedOnButtonReleasedEvent;

public:
	UiScreenView_btnImage(sf::Texture* _newImage, Transform* _transform, bool _worldObject = false);
	~UiScreenView_btnImage();
	void SetUiPosition(Vector2 _newPos, Vector2 _offset = Vector2(0, 0));
	void SetUiRotation(float _newRot);
	void SetUiScale(Vector2 _newScale);
	sf::Sprite GetComponentToDraw();
	bool isButtonBeingHovered();
	void AddUiToScreen();
	void RemoveUiFromScreen();
	inline bool IsBeingDrawned() { return isUiBeingDrawned; }
	void Update();

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

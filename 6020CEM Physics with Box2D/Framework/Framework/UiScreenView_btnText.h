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
	UiScreenView_Text* ui_text;
	Transform* transform;
	Transform* textTansform;
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
	UiScreenView_btnText(sf::Texture* _newImage, Transform* _transform, std::string _textToDisplay, Transform* _textTransform, UiScreenView_Text* _ui_text, bool _worldObject = false);
	~UiScreenView_btnText();
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


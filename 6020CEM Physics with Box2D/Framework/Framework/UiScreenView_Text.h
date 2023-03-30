#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Transform.h"

class UiScreenView_Text
{
private:
	//stores the text
	sf::Text sfmlText;
	//stores the transform
	Transform* transform;
	//stores if the ui is being drawned
	bool isUiBeingDrawned = false;
	//stores if its a world object
	bool worldObject = false;

	//stores the ui transform information
	struct uiTransformInformation
	{
		Vector2 pos;
		Vector2 offset;
		float rot;
		Vector2 scale;
	};
	uiTransformInformation uiTransformInformation;

public:
	UiScreenView_Text(std::string _textToDisplay, Transform* _transform, bool _worldObject = false);
	~UiScreenView_Text();

#pragma region Setters

	void SetFont(sf::Font _newFont);
	void SetText(std::string _newText);
	void SetFontSize(float _newSize);
	void SetTextColor(sf::Color _newColor);
	void SetUiPosition(Vector2 _newPos, Vector2 _offset = Vector2(0, 0));
	void SetUiRotation(float _newRot);
	void SetUiScale(Vector2 _newScale);

#pragma endregion

#pragma region Getters

	sf::Text GetComponentToDraw();
	inline bool IsBeingDrawned() { return isUiBeingDrawned; }
	inline sf::Text* GetSfmlText() { return &sfmlText; };

#pragma endregion

	void AddUiToScreen();
	void RemoveUiFromScreen();
	void Update();
};


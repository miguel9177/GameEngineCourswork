#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Transform.h"

class UiScreenView_Text
{
private:
	sf::Text sfmlText;
	Transform* transform;
public:
	UiScreenView_Text(std::string _textToDisplay, Transform* _transform);
	~UiScreenView_Text();
	void SetFont(sf::Font _newFont);
	void SetText(sf::String _newText);
	void SetFontSize(float _newSize);
	void SetTextColor(sf::Color _newColor);
	void SetUiPosition(Vector2 _newPos);
	void SetUiRotation(float _newRot);
	void SetUiScale(Vector2 _newScale);
	sf::Text GetComponentToDraw();
};


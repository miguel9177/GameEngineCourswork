#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Transform.h"

class UiScreenView_Image
{
private:
	sf::Sprite sprite;
	sf::Texture* texture;
	Transform* transform;
public:
	UiScreenView_Image(sf::Texture* _newImage, Transform* _transform);
	~UiScreenView_Image();
	void SetUiPosition(Vector2 _newPos);
	void SetUiRotation(float _newRot);
	void SetUiScale(Vector2 _newScale);
	sf::Sprite GetComponentToDraw();
};


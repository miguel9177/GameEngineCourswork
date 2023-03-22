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

public:
	UiScreenView_Image(sf::Texture* _newImage, Transform* _transform, bool _worldObject = false);
	~UiScreenView_Image();
	void SetUiPosition(Vector2 _newPos, Vector2 _offset = Vector2(0, 0));
	void SetUiRotation(float _newRot);
	void SetUiScale(Vector2 _newScale);
	sf::Sprite GetComponentToDraw();
	void AddUiToScreen();
	void RemoveUiFromScreen();
	inline bool IsBeingDrawned() { return isUiBeingDrawned; }
	void Update();
};


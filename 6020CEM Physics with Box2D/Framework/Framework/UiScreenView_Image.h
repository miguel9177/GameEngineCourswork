#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Transform.h"

class UiScreenView_Image
{
private:
	//stores the sprite
	sf::Sprite sprite;
	//stores tjhe texture
	sf::Texture* texture;
	//stores the transformm
	Transform* transform;
	//stores if the ui is being ddrawned 
	bool isUiBeingDrawned = false;

	//stores if its a world object
	bool worldObject = false;

	//store its indfo
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

#pragma region setters
	
	void SetUiPosition(Vector2 _newPos, Vector2 _offset = Vector2(0, 0));
	void SetUiRotation(float _newRot);
	void SetUiScale(Vector2 _newScale);

#pragma endregion

#pragma region getters

	sf::Sprite GetComponentToDraw();
	inline bool IsBeingDrawned() { return isUiBeingDrawned; }

#pragma endregion

	void AddUiToScreen();
	void RemoveUiFromScreen();
	void Update();
};


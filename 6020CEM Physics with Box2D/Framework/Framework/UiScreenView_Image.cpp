#include "UiScreenView_Image.h"
#include "GameEngine.h"
#include "Shape.h"
#include "UiEngine.h"

UiScreenView_Image::UiScreenView_Image(sf::Texture* _newImage, Transform* _transform) : texture(_newImage), transform(_transform)
{
	//if the texture is not 0, it means theres a texture assigned
	if (texture != nullptr && texture->getSize() != sf::Vector2u(0, 0))
	{
		sprite.setTexture(*texture);
		SetUiPosition(transform->position);
		SetUiRotation(transform->rotation);
		SetUiScale(transform->scale);
	}
}

UiScreenView_Image::~UiScreenView_Image()
{
	delete texture;
	delete transform;
}

/// <summary>
/// 
/// </summary>
/// <param name="_newPos">NEEDS TO BE A VALUE FROM 0 TO 1</param>
void UiScreenView_Image::SetUiPosition(Vector2 _newPos)
{
	sf::Vector2u windowSize = GameEngine::GetInstance()->GetWindowSize();
	float xPos = windowSize.x * _newPos.x;
	float yPos = windowSize.y * _newPos.y;

	//move the origin to its center
	sf::FloatRect textBounds = sprite.getLocalBounds();
	sprite.setOrigin(textBounds.width / 2, textBounds.height / 2);

	//move the sfml text to the correct position
	sprite.setPosition(xPos, yPos);
}

void UiScreenView_Image::SetUiRotation(float _newRot)
{
	sprite.setRotation(_newRot);
}

void UiScreenView_Image::SetUiScale(Vector2 _newScale)
{
	float scaleX = _newScale.x * Shape::defaultPixelsForBasicShapes / texture->getSize().x;
	float scaleY = _newScale.y * Shape::defaultPixelsForBasicShapes / texture->getSize().y;
	sprite.setScale(scaleX, scaleY);
}

sf::Sprite UiScreenView_Image::GetComponentToDraw()
{
	return sprite;
}

#pragma region helper functions

void UiScreenView_Image::AddUiToScreen()
{
	isUiBeingDrawned = true;
	UiEngine::GetInstance()->AddUiScreenViewImageToUiEngine(this);
}

void UiScreenView_Image::RemoveUiFromScreen()
{
	isUiBeingDrawned = false;
	UiEngine::GetInstance()->RemoveUiScreenViewImageFromUiEngine(this);
}

#pragma endregion


#include "UiScreenView_btnImage.h"
#include "UiEngine.h"
#include "GameEngine.h"
#include "Shape.h"
#include "EventQueue.h"
#include <functional>

UiScreenView_btnImage::UiScreenView_btnImage(sf::Texture* _newImage, Transform* _transform) : texture(_newImage), transform(_transform)
{
	//if the texture is not 0, it means theres a texture assigned
	if (texture != nullptr && texture->getSize() != sf::Vector2u(0, 0))
	{
		sprite.setTexture(*texture);
		SetUiPosition(transform->position);
		SetUiRotation(transform->rotation);
		SetUiScale(transform->scale);
		UiEngine::GetInstance()->AddUiScreenViewButtonImageToUiEngine(this);
		std::function<void()> callback = std::bind(&UiScreenView_btnImage::UserPressedLeftMouseButton, this);
		EventQueue::GetInstance()->SubscribeToMouseKeyPressEvent(sf::Mouse::Left, callback);
	}
}

UiScreenView_btnImage::~UiScreenView_btnImage()
{
	delete texture;
	delete transform;
}

/// <summary>
/// 
/// </summary>
/// <param name="_newPos">NEEDS TO BE A VALUE FROM 0 TO 1</param>
void UiScreenView_btnImage::SetUiPosition(Vector2 _newPos)
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

void UiScreenView_btnImage::SetUiRotation(float _newRot)
{
	sprite.setRotation(_newRot);
}

void UiScreenView_btnImage::SetUiScale(Vector2 _newScale)
{
	float scaleX = _newScale.x * Shape::defaultPixelsForBasicShapes / texture->getSize().x;
	float scaleY = _newScale.y * Shape::defaultPixelsForBasicShapes / texture->getSize().y;
	sprite.setScale(scaleX, scaleY);
}

sf::Sprite UiScreenView_btnImage::GetComponentToDraw()
{
	return sprite;
}

#pragma region Event Functions

void UiScreenView_btnImage::UserPressedLeftMouseButton()
{
}

void UiScreenView_btnImage::SubscribeToBtnOnPressEvent(void(*functionToCallBack)())
{
}

void UiScreenView_btnImage::UnsubscribeToBtnOnPressEvent(void(*functionToCallBack)())
{
}

void UiScreenView_btnImage::SubscribeToBtnOnReleasedEvent(void(*functionToCallBack)())
{
}

void UiScreenView_btnImage::UnsubscribeToBtnOnReleasedEvent(void(*functionToCallBack)())
{
}

#pragma endregion


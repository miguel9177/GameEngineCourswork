#include "UiScreenView_btnImage.h"
#include "UiEngine.h"
#include "GameEngine.h"
#include "Shape.h"
#include "EventQueue.h"
#include <functional>

UiScreenView_btnImage::UiScreenView_btnImage(sf::Texture* _newImage, Transform* _transform, bool _worldObject) : texture(_newImage), transform(_transform), worldObject(_worldObject)
{
	//if the texture is not 0, it means theres a texture assigned
	if (texture != nullptr && texture->getSize() != sf::Vector2u(0, 0))
	{
		sprite.setTexture(*texture);
		SetUiPosition(transform->position);
		SetUiRotation(transform->rotation);
		SetUiScale(transform->scale);

		//this subscribes to the left mouse click event, in order for it to call the function UserPressedLeftMouseButton everytime the user presses left mouse button
		std::function<void()> mousePressCallback = std::bind(&UiScreenView_btnImage::UserPressedLeftMouseButton, this);
		EventQueue::GetInstance()->SubscribeToMouseKeyPressEvent(sf::Mouse::Left, mousePressCallback);
		
		//this subscribes to the left mouse released event, in order for it to call the function UserReleasedLeftMouseButton everytime the user releases left mouse button
		std::function<void()> mouseReleasedCallback = std::bind(&UiScreenView_btnImage::UserReleasedLeftMouseButton, this);
		EventQueue::GetInstance()->SubscribeToMouseKeyReleasedEvent(sf::Mouse::Left, mouseReleasedCallback);
	}
}

UiScreenView_btnImage::~UiScreenView_btnImage()
{
	delete texture;
	delete transform;
}

/// <summary>
/// NEEDS TO BE A VALUE FROM 0 TO 1
/// </summary>
/// <param name="_newPos">NEEDS TO BE A VALUE FROM 0 TO 1</param>
void UiScreenView_btnImage::SetUiPosition(Vector2 _newPos, Vector2 _offset)
{
	uiTransformInformation.pos = _newPos;
	uiTransformInformation.offset = _offset;
	
	Vector2 windowSize = GameEngine::GetInstance()->GetCameraSize();
	float xPos = windowSize.x * _newPos.x;
	float yPos = windowSize.y * _newPos.y;

	//adjust the position of the ui depending on the camera position
	xPos += GameEngine::GetInstance()->GetCameraPosition().x - windowSize.x / 2.0f;
	yPos += GameEngine::GetInstance()->GetCameraPosition().y - windowSize.y / 2.0f;

	//move the origin to its center
	sf::FloatRect textBounds = sprite.getLocalBounds();
	sprite.setOrigin(textBounds.width / 2, textBounds.height / 2);

	//move the sfml text to the correct position
	sprite.setPosition(xPos + _offset.x, yPos + _offset.y);
}

void UiScreenView_btnImage::SetUiRotation(float _newRot)
{
	uiTransformInformation.rot = _newRot;

	sprite.setRotation(_newRot);
}

void UiScreenView_btnImage::SetUiScale(Vector2 _newScale)
{
	uiTransformInformation.scale = _newScale;

	float scaleX = _newScale.x * Shape::defaultPixelsForBasicShapes / texture->getSize().x;
	float scaleY = _newScale.y * Shape::defaultPixelsForBasicShapes / texture->getSize().y;
	sprite.setScale(scaleX, scaleY);
}

void UiScreenView_btnImage::SetTexture(sf::Texture texture_)
{
	*texture = texture_;
}

sf::Sprite UiScreenView_btnImage::GetComponentToDraw()
{
	return sprite;
}

#pragma region Event Functions

void UiScreenView_btnImage::UserPressedLeftMouseButton()
{
	if (!isUiBeingDrawned)
		return;

	if (isButtonBeingHovered() && !pressing)
	{
		pressing = true;
		InvokeButtonPressedEvent();
	}
}

void UiScreenView_btnImage::UserReleasedLeftMouseButton()
{
	if (pressing)
	{
		pressing = false;
		InvokeButtonReleasedEvent();
	}
}

void UiScreenView_btnImage::SubscribeToBtnOnPressEvent(std::function<void()> function)
{
	allSubscribedOnButtonPressEvent.push_back(std::function<void()>(function));
}

void UiScreenView_btnImage::UnsubscribeToBtnOnPressEvent(std::function<void()> function)
{
	for (unsigned int i = 0; i < allSubscribedOnButtonPressEvent.size();)
	{
		if (allSubscribedOnButtonPressEvent[i] != nullptr && EventQueue::getAddress(allSubscribedOnButtonPressEvent[i]) == EventQueue::getAddress(function))
		{
			allSubscribedOnButtonPressEvent.erase(allSubscribedOnButtonPressEvent.begin() + i);
		}
		else
		{
			i++;
		}
	}
}

void UiScreenView_btnImage::SubscribeToBtnOnReleasedEvent(std::function<void()> function)
{
	allSubscribedOnButtonReleasedEvent.push_back(std::function<void()>(function));
}

void UiScreenView_btnImage::UnsubscribeToBtnOnReleasedEvent(std::function<void()> function)
{
	for (unsigned int i = 0; i < allSubscribedOnButtonReleasedEvent.size();)
	{
		if (allSubscribedOnButtonReleasedEvent[i] != nullptr && EventQueue::getAddress(allSubscribedOnButtonReleasedEvent[i]) == EventQueue::getAddress(function))
		{
			allSubscribedOnButtonReleasedEvent.erase(allSubscribedOnButtonReleasedEvent.begin() + i);
		}
		else
		{
			i++;
		}
	}
}

void UiScreenView_btnImage::InvokeButtonPressedEvent()
{
	for (auto& callback : allSubscribedOnButtonPressEvent)
	{
		if (callback != nullptr)
		{
			callback();
		}
	}
}

void UiScreenView_btnImage::InvokeButtonReleasedEvent()
{
	for (auto& callback : allSubscribedOnButtonReleasedEvent)
	{
		if (callback != nullptr)
		{
			callback();
		}
	}
}

#pragma endregion

#pragma region Helper Functions

bool UiScreenView_btnImage::isButtonBeingHovered()
{
	Vector2 screenMousePos = InputsEngine::GetInstance()->GetMouseState().position;
	Vector2 viewCenter = GameEngine::GetInstance()->GetCameraPosition();
	Vector2 viewSize = GameEngine::GetInstance()->GetCameraSize();

	sf::Vector2f worldMousePos = sf::Vector2f(screenMousePos.x + viewCenter.x - viewSize.x / 2.0f, screenMousePos.y + viewCenter.y - viewSize.y / 2.0f);

	sf::FloatRect buttonBounds = sprite.getGlobalBounds();

	if (buttonBounds.contains(worldMousePos))
		return true;
	else
		return false;
}

void UiScreenView_btnImage::AddUiToScreen()
{
	isUiBeingDrawned = true;
	UiEngine::GetInstance()->AddUiScreenViewButtonImageToUiEngine(this);
}

void UiScreenView_btnImage::RemoveUiFromScreen()
{
	isUiBeingDrawned = false;
	UiEngine::GetInstance()->RemoveUiScreenViewButtonImageFromUiEngine(this);
}

void UiScreenView_btnImage::Update()
{
	//if we are a world object we dont want to reposition the ui
	if (worldObject)
		return;

	SetUiPosition(uiTransformInformation.pos, uiTransformInformation.offset);
	SetUiRotation(uiTransformInformation.rot);
	SetUiScale(uiTransformInformation.scale);
}

#pragma endregion

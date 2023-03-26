#include "UiScreenView_btnText.h"
#include "UiEngine.h"
#include "GameEngine.h"
#include "Shape.h"
#include "EventQueue.h"
#include <functional>
#include "UiScreenView_Text.h"

UiScreenView_btnText::UiScreenView_btnText(sf::Texture* _newImage, Transform* _transform, std::string _textToDisplay, Transform* _textTransform, bool _worldObject) : texture(_newImage), transform(_transform), textTansform(_textTransform), ui_text(_textToDisplay, _textTransform), worldObject(_worldObject)
{
	//if the texture is not 0, it means theres a texture assigned
	if (texture != nullptr && texture->getSize() != sf::Vector2u(0, 0))
	{
		SetTextUiPosition(_textTransform->position);
		SetTextUiRotation(_textTransform->rotation);
		SetTextUiScale(_textTransform->scale);

		sprite.setTexture(*texture);
		SetUiPosition(transform->position);
		SetUiRotation(transform->rotation);
		SetUiScale(transform->scale);

		//this subscribes to the left mouse click event, in order for it to call the function UserPressedLeftMouseButton everytime the user presses left mouse button
		std::function<void()> mousePressCallback = std::bind(&UiScreenView_btnText::UserPressedLeftMouseButton, this);
		EventQueue::GetInstance()->SubscribeToMouseKeyPressEvent(sf::Mouse::Left, mousePressCallback);

		//this subscribes to the left mouse released event, in order for it to call the function UserReleasedLeftMouseButton everytime the user releases left mouse button
		std::function<void()> mouseReleasedCallback = std::bind(&UiScreenView_btnText::UserReleasedLeftMouseButton, this);
		EventQueue::GetInstance()->SubscribeToMouseKeyReleasedEvent(sf::Mouse::Left, mouseReleasedCallback);
	}
}

UiScreenView_btnText::~UiScreenView_btnText()
{
	delete texture;
	delete transform;
}

void UiScreenView_btnText::Update()
{
	//if we are a world object we dont want to reposition the ui
	if (worldObject)
		return;

	SetUiPosition(uiTransformInformation.pos, uiTransformInformation.offset);
	SetUiRotation(uiTransformInformation.rot);
	SetUiScale(uiTransformInformation.scale);
}

#pragma region Set Data

void UiScreenView_btnText::SetFont(sf::Font _newFont)
{
	ui_text.SetFont(_newFont);
}

void UiScreenView_btnText::SetText(sf::String _newText)
{
	ui_text.SetText(_newText);
}

void UiScreenView_btnText::SetFontSize(float _newSize)
{
	ui_text.SetFontSize(_newSize);
}

void UiScreenView_btnText::SetTextColor(sf::Color _newColor)
{
	ui_text.SetTextColor(_newColor);
}

/// <summary>
/// NEEDS TO BE A VALUE FROM 0 TO 1
/// </summary>
/// <param name="_newPos">NEEDS TO BE A VALUE FROM 0 TO 1</param>
void UiScreenView_btnText::SetTextUiPosition(Vector2 _newPos, Vector2 _offset)
{
	Vector2 windowSize = GameEngine::GetInstance()->GetCameraSize();
	float xPos = windowSize.x * _newPos.x;
	float yPos = windowSize.y * _newPos.y;
	
	//adjust the position of the ui depending on the camera position
	xPos += GameEngine::GetInstance()->GetCameraSfmlPosition().x - windowSize.x / 2.0f;
	yPos += GameEngine::GetInstance()->GetCameraSfmlPosition().y - windowSize.y / 2.0f;

	//move the origin to its center
	sf::FloatRect textBounds = ui_text.GetSfmlText()->getLocalBounds();
	ui_text.GetSfmlText()->setOrigin(textBounds.width / 2, textBounds.height / 2);

	//move the sfml text to the correct position
	ui_text.GetSfmlText()->setPosition(xPos + _offset.x, yPos + _offset.y);
}

void UiScreenView_btnText::SetTextUiRotation(float _newRot)
{
	ui_text.GetSfmlText()->setRotation(_newRot);
}

void UiScreenView_btnText::SetTextUiScale(Vector2 _newScale)
{
	ui_text.GetSfmlText()->setScale(_newScale);
}

/// <summary>
/// NEEDS TO BE A VALUE FROM 0 TO 1
/// </summary>
/// <param name="_newPos">NEEDS TO BE A VALUE FROM 0 TO 1</param>
void UiScreenView_btnText::SetUiPosition(Vector2 _newPos, Vector2 _offset)
{
	uiTransformInformation.pos = _newPos;
	uiTransformInformation.offset = _offset;

	Vector2 windowSize = GameEngine::GetInstance()->GetCameraSize();;
	float xPos = windowSize.x * _newPos.x;
	float yPos = windowSize.y * _newPos.y;

	//adjust the position of the ui depending on the camera position
	xPos += GameEngine::GetInstance()->GetCameraSfmlPosition().x - windowSize.x / 2.0f;
	yPos += GameEngine::GetInstance()->GetCameraSfmlPosition().y - windowSize.y / 2.0f;

	//move the origin to its center
	sf::FloatRect textBounds = sprite.getLocalBounds();
	sprite.setOrigin(textBounds.width / 2, textBounds.height / 2);

	//move the sfml text to the correct position
	sprite.setPosition(xPos + _offset.x, yPos + _offset.y);
}

void UiScreenView_btnText::SetUiRotation(float _newRot)
{
	uiTransformInformation.rot = _newRot;

	sprite.setRotation(_newRot);
}

void UiScreenView_btnText::SetUiScale(Vector2 _newScale)
{
	uiTransformInformation.scale = _newScale;

	float scaleX = _newScale.x * Shape::defaultPixelsForBasicShapes / texture->getSize().x;
	float scaleY = _newScale.y * Shape::defaultPixelsForBasicShapes / texture->getSize().y;
	sprite.setScale(scaleX, scaleY);
}

#pragma endregion

sf::Sprite UiScreenView_btnText::GetComponentToDraw()
{
	return sprite;
}

#pragma region Event Functions

void UiScreenView_btnText::UserPressedLeftMouseButton()
{
	if (!isUiBeingDrawned)
		return;

	if (isButtonBeingHovered() && !pressing)
	{
		pressing = true;
		InvokeButtonPressedEvent();
	}
}

void UiScreenView_btnText::UserReleasedLeftMouseButton()
{
	if (pressing)
	{
		pressing = false;
		InvokeButtonReleasedEvent();
	}
}


void UiScreenView_btnText::SubscribeToBtnOnPressEvent(std::function<void()> function)
{
	allSubscribedOnButtonPressEvent.push_back(std::function<void()>(function));
}

void UiScreenView_btnText::UnsubscribeToBtnOnPressEvent(std::function<void()> function)
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

void UiScreenView_btnText::SubscribeToBtnOnReleasedEvent(std::function<void()> function)
{
	allSubscribedOnButtonReleasedEvent.push_back(std::function<void()>(function));
}

void UiScreenView_btnText::UnsubscribeToBtnOnReleasedEvent(std::function<void()> function)
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

void UiScreenView_btnText::InvokeButtonPressedEvent()
{
	for (auto& callback : allSubscribedOnButtonPressEvent)
	{
		if (callback != nullptr)
		{
			callback();
		}
	}
}

void UiScreenView_btnText::InvokeButtonReleasedEvent()
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

bool UiScreenView_btnText::isButtonBeingHovered()
{
	Vector2 screenMousePos = InputsEngine::GetInstance()->GetMouseState().position;
	Vector2 viewCenter = GameEngine::GetInstance()->GetCameraSfmlPosition();
	Vector2 viewSize = GameEngine::GetInstance()->GetCameraSize();

	sf::Vector2f worldMousePos = sf::Vector2f(screenMousePos.x + viewCenter.x - viewSize.x / 2.0f, screenMousePos.y + viewCenter.y - viewSize.y / 2.0f);

	sf::FloatRect buttonBounds = sprite.getGlobalBounds();

	if (buttonBounds.contains(worldMousePos))
		return true;
	else
		return false;
}

void UiScreenView_btnText::AddUiToScreen()
{
	isUiBeingDrawned = true;
	UiEngine::GetInstance()->AddUiScreenViewButtonTextToUiEngine(this);
	UiEngine::GetInstance()->AddUiScreenViewTextToUiEngine(&ui_text);
}

void UiScreenView_btnText::RemoveUiFromScreen()
{
	isUiBeingDrawned = false;
	UiEngine::GetInstance()->RemoveUiScreenViewButtonTextFromUiEngine(this);
	UiEngine::GetInstance()->RemoveUiScreenViewTextFromUiEngine(&ui_text);
}

#pragma endregion
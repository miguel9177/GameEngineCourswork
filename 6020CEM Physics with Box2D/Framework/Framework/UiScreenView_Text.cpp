#include "UiScreenView_Text.h"
#include "GameEngine.h"
#include "UiEngine.h"

/// <summary>
/// 
/// </summary>
/// <param name="_textToDisplay"></param>
/// <param name="_transform">position needs to be from 0 to 1</param>
UiScreenView_Text::UiScreenView_Text(std::string _textToDisplay, Transform* _transform, bool _worldObject) : worldObject(_worldObject)
{
	transform = _transform;
	sfmlText.setFont(*GraphicsEngine::GetGameEngineFont());
	sfmlText.setRotation(transform->rotation);
	sfmlText.setScale(transform->scale);
	sfmlText.setString(_textToDisplay);
	sfmlText.setCharacterSize(15);
	sfmlText.setFillColor(sf::Color::White);
	sfmlText.setStyle(sf::Text::Regular);
	SetUiPosition(transform->position);

}

UiScreenView_Text::~UiScreenView_Text()
{
	delete transform;
}

void UiScreenView_Text::SetFont(sf::Font _newFont)
{
	sfmlText.setFont(_newFont);
}

void UiScreenView_Text::SetText(sf::String _newText)
{
	sfmlText.setString(_newText);
}

void UiScreenView_Text::SetFontSize(float _newSize)
{
	sfmlText.setCharacterSize(_newSize);
}

void UiScreenView_Text::SetTextColor(sf::Color _newColor)
{
	sfmlText.setFillColor(_newColor);
}

/// <summary>
/// 
/// </summary>
/// <param name="_newPos">NEEDS TO BE A VALUE FROM 0 TO 1</param>
void UiScreenView_Text::SetUiPosition(Vector2 _newPos, Vector2 _offset)
{
	uiTransformInformation.pos = _newPos;
	uiTransformInformation.offset = _offset;

	Vector2 windowSize = GameEngine::GetInstance()->GetCameraSize();
	float xPos = windowSize.x * _newPos.x;
	float yPos = windowSize.y * _newPos.y;

	//adjust the position of the ui depending on the camera position
	xPos += GameEngine::GetInstance()->GetCameraSfmlPosition().x - windowSize.x / 2.0f;
	yPos += GameEngine::GetInstance()->GetCameraSfmlPosition().y - windowSize.y / 2.0f;

	//move the origin to its center
	sf::FloatRect textBounds = sfmlText.getLocalBounds();
	sfmlText.setOrigin(textBounds.width / 2, textBounds.height / 2);

	//move the sfml text to the correct position
	sfmlText.setPosition(xPos + _offset.x, yPos + _offset.y);
}

void UiScreenView_Text::SetUiRotation(float _newRot)
{
	uiTransformInformation.rot = _newRot;

	sfmlText.setRotation(_newRot);
}

void UiScreenView_Text::SetUiScale(Vector2 _newScale)
{
	uiTransformInformation.scale = _newScale;

	sfmlText.setScale(_newScale);
}

sf::Text UiScreenView_Text::GetComponentToDraw()
{
	return sfmlText;
}

void UiScreenView_Text::AddUiToScreen()
{
	isUiBeingDrawned = true;
	UiEngine::GetInstance()->AddUiScreenViewTextToUiEngine(this);
}

void UiScreenView_Text::RemoveUiFromScreen()
{
	isUiBeingDrawned = false;
	UiEngine::GetInstance()->RemoveUiScreenViewTextFromUiEngine(this);
}

void UiScreenView_Text::Update()
{
	//if we are a world object we dont want to reposition the ui
	if (worldObject)
		return;

	SetUiPosition(uiTransformInformation.pos, uiTransformInformation.offset);
	SetUiRotation(uiTransformInformation.rot);
	SetUiScale(uiTransformInformation.scale);
}

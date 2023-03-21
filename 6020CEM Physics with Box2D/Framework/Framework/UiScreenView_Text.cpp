#include "UiScreenView_Text.h"
#include "GameEngine.h"
#include "UiEngine.h"

/// <summary>
/// 
/// </summary>
/// <param name="_textToDisplay"></param>
/// <param name="_transform">position needs to be from 0 to 1</param>
UiScreenView_Text::UiScreenView_Text(std::string _textToDisplay, Transform* _transform)
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
	UiEngine::GetInstance()->AddUiScreenViewTextToUiEngine(this);

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
void UiScreenView_Text::SetUiPosition(Vector2 _newPos)
{
	sf::Vector2u windowSize = GameEngine::GetInstance()->GetWindowSize();
	float xPos = windowSize.x * _newPos.x;
	float yPos = windowSize.y * _newPos.y;

	//move the origin to its center
	sf::FloatRect textBounds = sfmlText.getLocalBounds();
	sfmlText.setOrigin(textBounds.width / 2, textBounds.height / 2);

	//move the sfml text to the correct position
	sfmlText.setPosition(xPos, yPos);
}

sf::Text UiScreenView_Text::GetComponentToDraw()
{
	return sfmlText;
}

#include "SB_CharacterMovement.h"
#include "../InputsEngine.h"
#include "../RigidBody.h"
#include "../EventQueue.h"
#include "../AudioPlayer.h"

#pragma region Engine functions

SB_CharacterMovement::SB_CharacterMovement() : ScriptBehaviour(uniqueComponentIdIdentifier)
{
    rb = nullptr;
    audioSource = nullptr;
}

//starts, runs once when the component is added to the object
void SB_CharacterMovement::Start()
{
    //gets the rb
    rb = gameObject->TryGetComponent<RigidBody>(Component::typeOfComponent::Physics);

    //gets the audio source
    audioSource = gameObject->TryGetComponent<AudioPlayer>(Component::typeOfComponent::Audio);
    //subscribes to the mouse key +press event and tells it to call left mouse press function
    EventQueue::GetInstance()->SubscribeToMouseKeyPressEvent(sf::Mouse::Left, std::bind(&SB_CharacterMovement::LeftMousePressed, this));

}

//updates every frame
void SB_CharacterMovement::Update()
{
    //if a is pressed, add force
    if (InputsEngine::GetInstance()->GetKeyStates().at(sf::Keyboard::A).pressing)
    {
        rb->AddForceToCenter(Vector2(-amountOfForceToApply, 0.f));
    }
    //if d is pressed, add force
    if (InputsEngine::GetInstance()->GetKeyStates().at(sf::Keyboard::D).pressing)
    {
        rb->AddForceToCenter(Vector2(+amountOfForceToApply, 0.f));
    }
    //if w is pressed, add force
    if (InputsEngine::GetInstance()->GetKeyStates().at(sf::Keyboard::W).pressing)
    {
        rb->AddForceToCenter(Vector2(0.f, -amountOfForceToApply));
    }
    //if s is pressed, add force
    if (InputsEngine::GetInstance()->GetKeyStates().at(sf::Keyboard::S).pressing)
    {
        rb->AddForceToCenter(Vector2(0.f, +amountOfForceToApply));
    }
}

#pragma endregion

//this is called when the left mouse is pressed, and playes the shooting sound
void SB_CharacterMovement::LeftMousePressed()
{
    if (audioSource != nullptr)
        audioSource->PlaySound();
}



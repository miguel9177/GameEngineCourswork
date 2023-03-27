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

void SB_CharacterMovement::Start()
{
    rb = gameObject->TryGetComponent<RigidBody>(Component::typeOfComponent::Physics);

    audioSource = gameObject->TryGetComponent<AudioPlayer>(Component::typeOfComponent::Audio);
    EventQueue::GetInstance()->SubscribeToMouseKeyPressEvent(sf::Mouse::Left, std::bind(&SB_CharacterMovement::LeftMousePressed, this));

}

void SB_CharacterMovement::Update()
{
    if (InputsEngine::GetInstance()->GetKeyStates().at(sf::Keyboard::A).pressing)
    {
        rb->AddForceToCenter(Vector2(-amountOfForceToApply, 0.f));
    }
    if (InputsEngine::GetInstance()->GetKeyStates().at(sf::Keyboard::D).pressing)
    {
        rb->AddForceToCenter(Vector2(+amountOfForceToApply, 0.f));
    }

    if (InputsEngine::GetInstance()->GetKeyStates().at(sf::Keyboard::W).pressing)
    {
        rb->AddForceToCenter(Vector2(0.f, -amountOfForceToApply));
    }
    if (InputsEngine::GetInstance()->GetKeyStates().at(sf::Keyboard::S).pressing)
    {
        rb->AddForceToCenter(Vector2(0.f, +amountOfForceToApply));
    }
}

#pragma endregion

void SB_CharacterMovement::LeftMousePressed()
{
    if (audioSource != nullptr)
        audioSource->PlaySound();
}



#include "SB_MultiplayerServerClient.h"
#include <iostream>
#include "../SquareCollider.h"
#include "../RigidBody.h"
#include "../Shape_Box.h"
#include "../Scene.h"
#include "SB_CharacterMovement.h"

SB_MultiplayerServerClient::SB_MultiplayerServerClient() : ScriptBehaviour(uniqueComponentIdIdentifier)
{
	address = new ENetAddress();
	client = new ENetHost();
	peer = new ENetPeer();
	serverData = new PhysicsData;
	clientData = new ClientData;
	clientPacket = new ClientPacket;
	dataPacket = new ENetPacket();
	enetEvent = new ENetEvent();
	packetType = new int;
	*packetType = -1;
	clientIndex = -1;

	player = nullptr;
}

SB_MultiplayerServerClient::~SB_MultiplayerServerClient()
{
	if (peer != NULL)
	{
		enet_peer_disconnect_now(peer, 0);
	}

	delete address;
	delete client;
	delete peer;
	delete serverData;
	delete clientData;
	delete clientPacket;
	delete dataPacket;
	delete enetEvent;
	delete packetType;

	otherPlayers.clear();
}

void SB_MultiplayerServerClient::Start()
{
}

void SB_MultiplayerServerClient::LateStart()
{
	GetPlayerObject();

	if (enet_initialize() != 0)
	{
		std::cout << "Error: Enet failed to initialise!" << "\n\n" << std::endl;
	}

	client = enet_host_create(NULL, 1, 2, 0, 0);

	if (client == NULL)
	{
		std::cout << "Error: Client failed to initialise!" << "\n\n" << std::endl;
	}

	enet_address_set_host(address, "localhost");
	address->port = 1234;

	peer = enet_host_connect(client, address, 2, 0);

	if (peer == NULL) {
		std::cout << "Error: No available peers for initializing an ENet connection.\n" << std::endl;
	}


	packetType = new int;

	*packetType = -1;

	clientIndex = -1;
}

void SB_MultiplayerServerClient::Update()
{
	if (player == nullptr)
	{
		GetPlayerObject();
		return;
	}

	while (enet_host_service(client, enetEvent, 0) > 0)
	{
		switch (enetEvent->type) 
		{
		case ENET_EVENT_TYPE_CONNECT:
			memcpy(packetType, enetEvent->packet->data, sizeof(int));
			memcpy(clientData, enetEvent->packet->data, sizeof(ClientData));
			clientIndex = clientData->clientIndex;
			CreateNewEnemyPlayer(clientIndex);
			break;

		case ENET_EVENT_TYPE_RECEIVE:

			memcpy(packetType, enetEvent->packet->data, sizeof(int));

			if (*packetType == 0)
			{
				std::cout << "Packet Received!\n";
				memcpy(clientData, enetEvent->packet->data, sizeof(ClientData));
				clientIndex = clientData->clientIndex;
			}
			else if (*packetType == 1)
			{
				memcpy(serverData, enetEvent->packet->data, sizeof(PhysicsData));
				for (int i = 0; i < 2; i++)
				{
					if (i != clientIndex)
					{
						otherPlayers[clientIndex]->SetPosition(serverData->positions[i]);
					}
				}
			}

			break;
		}

		clientPacket->clientIndex = clientIndex;
		clientPacket->position = player->GetPosition();

		dataPacket = enet_packet_create(clientPacket, sizeof(ClientPacket), ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, dataPacket);
	}
}


#pragma region Helper Functions

void SB_MultiplayerServerClient::GetPlayerObject()
{
	for (GameObject* currentObject : *Scene::GetInstance()->GetAllObjects())
	{
		if (currentObject->TryGetComponent<SB_CharacterMovement>(Component::typeOfComponent::ScriptBehaviour))
			player = currentObject;
	}

	if (player == nullptr)
	{
		std::cout << "Error: no character player was found;" << std::endl;
	}
	else
		std::cout << player->name;
}

void SB_MultiplayerServerClient::CreateNewEnemyPlayer(int _clientIndex)
{
	GameObject* enemyPlayer = new GameObject("EnemyPlayer", new Transform(Vector2(0, 0), 0, Vector2(0, 0)));

	Shape_Box* shapeBoxOfEnemy = new Shape_Box();

	Com_Mesh* Com_MeshOfEnemy = new Com_Mesh();

	RigidBodySettings bodySettingsOfEnemy = RigidBodySettings(kinematicBody, 1, 1, false, true, false, false, 0);
	RigidBody* rbOfEnemy = new RigidBody(bodySettingsOfEnemy);

	SquareCollider* squareCollOfEnemy = new SquareCollider(Vector2(0.122, 0.122), Vector2(0, 0));

	Com_MeshOfEnemy->SetShape(shapeBoxOfEnemy);
	Com_MeshOfEnemy->SetTexture("../Textures/EnemyPlayer.png");

	enemyPlayer->AddComponent(Com_MeshOfEnemy);
	enemyPlayer->AddComponent(rbOfEnemy);
	enemyPlayer->AddComponent(squareCollOfEnemy);

	//add an object to the scene
	Scene::GetInstance()->AddObject(enemyPlayer);
	otherPlayers[_clientIndex] = enemyPlayer;
}

#pragma endregion
#include "SB_MultiplayerServerClient.h"
#include <iostream>


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
}

SB_MultiplayerServerClient::~SB_MultiplayerServerClient()
{
	if (peer != NULL)
	{
		enet_peer_disconnect_now(peer, 0);
	}

	delete client;
	delete peer;
	delete serverData;
	delete clientData;
	delete dataPacket;
}

void SB_MultiplayerServerClient::Start()
{
	if (enet_initialize() != 0)
	{
		std::cout << "Enet failed to initialise!" << "\n\n" << std::endl;
	}

	client = enet_host_create(NULL, 1, 2, 0, 0);

	if (client == NULL)
	{
		std::cout << "Client failed to initialise!" << "\n\n" << std::endl;
	}

	enet_address_set_host(address, "localhost");
	address->port = 1234;

	peer = enet_host_connect(client, address, 2, 0);

	if (peer == NULL) {
		std::cout << "No available peers for initializing an ENet connection.\n" << std::endl;
	}


	int* packetType = new int;

	*packetType = -1;



	int clientIndex = -1;
}

void SB_MultiplayerServerClient::Update()
{
}

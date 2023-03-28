#pragma once
#include "../ScriptBehaviour.h"
#include "../Vector2.h"
#include <enet/enet.h>

class SB_MultiplayerServerClient : public ScriptBehaviour
{
	static const unsigned int uniqueComponentIdIdentifier = 10004;
	
	struct PhysicsData {
		int packetType = 1;
		Vector2 positions[2];
	};

	struct ClientData {
		int packetType = 0;
		int clientIndex;
	};

	struct ClientPacket {
		int clientIndex;
		Vector2 position;
	};

	ENetAddress* address;
	ENetHost* client;
	ENetPeer* peer;
	PhysicsData* serverData;
	ClientData* clientData;
	ClientPacket* clientPacket;
	ENetPacket* dataPacket;
	ENetEvent* enetEvent;
	int* packetType;
	int clientIndex;

	GameObject* player;

	std::map<int, GameObject*> otherPlayers;
public:
#pragma region Engine Functions

	SB_MultiplayerServerClient();
	~SB_MultiplayerServerClient();
	void Start() override;
	void Update() override;
	void LateStart() override;

	inline SB_MultiplayerServerClient* Clone() override
	{
		return new SB_MultiplayerServerClient(*this);
	}

#pragma endregion

#pragma region Helper Functions

	void GetPlayerObject();

	void CreateNewEnemyPlayer(int _clientIndex);

#pragma endregion

};


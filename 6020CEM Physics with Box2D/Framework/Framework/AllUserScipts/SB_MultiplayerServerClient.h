#pragma once
#include "../ScriptBehaviour.h"
#include <enet/enet.h>
#include <unordered_map>

class SB_MultiplayerServerClient : public ScriptBehaviour
{
	static const unsigned int uniqueComponentIdIdentifier = 10004;
	
	struct Vector2Online {
		float x;
		float y;
	};

	struct PhysicsData {
		int packetType = 1;
		Vector2Online position;
	};

	struct ClientData {
		int packetType = 0;
		int clientIndex;
	};

	struct ClientPacket {
		int clientIndex;
		Vector2Online position;
	};

	ENetAddress* address;
	ENetHost* client;
	ENetPeer* peer;
	std::unordered_map<int, PhysicsData*> serverData;
	ClientData* clientData;
	ClientPacket* clientPacket;
	ENetEvent* enetEvent;
	int packetType;
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

	PhysicsData* GetPhysicsData(std::unordered_map<int, PhysicsData*>& physicsData, int clientIndex) 
	{
		auto it = physicsData.find(clientIndex);
		if (it == physicsData.end()) {
			PhysicsData* newData = new PhysicsData();
			physicsData[clientIndex] = newData;
			return newData;
		}
		return it->second;
	}

#pragma endregion

};


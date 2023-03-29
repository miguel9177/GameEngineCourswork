#pragma once
#include "../ScriptBehaviour.h"
#include <enet/enet.h>
#include <unordered_map>
#include <queue>
#include <mutex>

class SB_MultiplayerServerClient : public ScriptBehaviour
{
	static const unsigned int uniqueComponentIdIdentifier = 10004;
	
    const std::string SERVER_IP = "192.168.0.38";
    const int SERVER_PORT = 9050;
    const int BUFFER_SIZE = 1024;

    WSADATA wsaData;
    int sockfd;
    struct sockaddr_in server_addr;
    int addr_len = sizeof(server_addr);
    char buffer[1024];

    class Vector3
    {
    public:
        float x;
        float y;
        float z;

        Vector3(float x_, float y_, float z_)
        {
            x = x_;
            y = y_;
            z = z_;
        }

        Vector3()
        {
            x = 0;
            y = 0;
            z = 0;
        }
    };

    class Quaternion
    {
    public:
        float x;
        float y;
        float z;
        float w;

        Quaternion(float x_, float y_, float z_, float w_)
        {
            x = x_;
            y = y_;
            z = z_;
            w = w_;
        }

        Quaternion()
        {
            x = 0;
            y = 0;
            z = 0;
            w = 0;
        }
    };

    static int staticLocalIdNetwork;//this is not necesssary to send to the server, this is something local

    //this has all the player info to send to the network at every possible way, since this info is vital
    class PlayerInfoClass
    {
    public:
        Vector3 position;
        Quaternion rotation;
        int uniqueNetworkID;
        int mylocalIdNetwork;
        float hp;
        GameObject* object;

        PlayerInfoClass()
        {
            position = Vector3(-5, 0, 0);
            rotation = Quaternion(0, 0, 0, 0);
            uniqueNetworkID = -1;
            mylocalIdNetwork = -1;
            hp = 100;
        }
    };

    PlayerInfoClass* playerInfoClass = new PlayerInfoClass();
    std::unordered_map<int, PlayerInfoClass> otherPlayersInfoMap;
    GameObject* enemyPlayer;
    std::mutex receivedMessagesMutex;
    std::queue<std::string> receivedMessages;
public:

#pragma region Engine Functions

	SB_MultiplayerServerClient();
    SB_MultiplayerServerClient(const SB_MultiplayerServerClient& other);
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

	GameObject* GetPlayerObject();

	GameObject* CreateNewEnemyPlayer();

    PlayerInfoClass ParseObjectData(const std::string& objectData);

    void SB_MultiplayerServerClient::ReceiveMessages();

#pragma endregion

};


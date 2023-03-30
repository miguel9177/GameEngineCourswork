#pragma once
#include "../ScriptBehaviour.h"
#include <enet/enet.h>
#include <unordered_map>
#include <queue>
#include <mutex>

class SB_MultiplayerServerClient : public ScriptBehaviour
{
    //this is a unique id identifier, read documentation graph to fully understand its reason, but in short everty component needs an unique identifier
	static const unsigned int uniqueComponentIdIdentifier = 10004;
	
    //stores the server ip
    const std::string SERVER_IP = "10.1.42.104";
    //stores the server port
    const int SERVER_PORT = 9050;
    //stores the buffer size
    const int BUFFER_SIZE = 1024;

    WSADATA wsaData; //declares a variable of type WSADATA to hold information about the Windows Sockets implementation
    int sockfd; //declares a socket file descriptor variable
    struct sockaddr_in server_addr; //declares a sockaddr_in structure to hold information about the server address
    int addr_len = sizeof(server_addr); //gets the size of the server address structure and store it in addr_len
    char buffer[1024]; //declares a buffer to hold data to be sent or received over the socket

    //vector 3 since our server is working for vector 3
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

    //stores the quaternion, since our server is ready fore quaternions
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

    //this stores the player multiplayer info
    PlayerInfoClass* playerInfoClass = new PlayerInfoClass();
    //stores all the other players infos
    std::unordered_map<int, PlayerInfoClass> otherPlayersInfoMap;
    //stores the enemy gameobject to spawn
    GameObject* enemyPlayer;
    //i use mutex to safely use my multiplayer thread without creating problems
    std::mutex receivedMessagesMutex;
    //this tores all the received messages from the server
    std::queue<std::string> receivedMessages;
    //this is true, if we couldnt connect to the server
    bool errorConnectingToServer = false;
public:

#pragma region Engine Functions

	SB_MultiplayerServerClient();
    SB_MultiplayerServerClient(const SB_MultiplayerServerClient& other);
	~SB_MultiplayerServerClient();
    //starts, runs once when the component is added to the object
	void Start() override;
    //updates every frame
	void Update() override;
    //late start is runned once at the beigining of the gameplay, if the script is added at runtime, this wont be called 
	void LateStart() override;

    //this lets the script loader manager to create a instance of this script
	inline SB_MultiplayerServerClient* Clone() override
	{
		return new SB_MultiplayerServerClient(*this);
	}

#pragma endregion

#pragma region Helper Functions

    //gets the player object
	GameObject* GetPlayerObject();

    //creates a new enemy
	GameObject* CreateNewEnemyPlayer();

    //parses the received object data
    PlayerInfoClass ParseObjectData(const std::string& objectData);

    //receives the messages
    void SB_MultiplayerServerClient::ReceiveMessages();

    //replaces all character from a string from one letter to another, this is used to fix , to . since my pc is portuguese
    std::string ReplaceAllCharacters(const std::string& str, char from, char to);

#pragma endregion

};


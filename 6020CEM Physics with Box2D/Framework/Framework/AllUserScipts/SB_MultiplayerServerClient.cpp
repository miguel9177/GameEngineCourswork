#include "SB_MultiplayerServerClient.h"
#include <iostream>
#include "../SquareCollider.h"
#include "../RigidBody.h"
#include "../Shape_Box.h"
#include "../Scene.h"
#include "SB_CharacterMovement.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <sstream>
#include <iomanip>
#include <locale>
#include <codecvt>
#include <unordered_map>
#include <thread>
#include <mutex>

int SB_MultiplayerServerClient::staticLocalIdNetwork = 0;

SB_MultiplayerServerClient::SB_MultiplayerServerClient() : ScriptBehaviour(uniqueComponentIdIdentifier)
{

}

SB_MultiplayerServerClient::SB_MultiplayerServerClient(const SB_MultiplayerServerClient& other) : ScriptBehaviour(uniqueComponentIdIdentifier) 
{
    
}

SB_MultiplayerServerClient::~SB_MultiplayerServerClient()
{
    delete playerInfoClass;
    //closes the socket
    closesocket(sockfd);
    WSACleanup();
}

//starts, runs once when the component is added to the object
void SB_MultiplayerServerClient::Start()
{
}

//late start is runned once at the beigining of the gameplay, if the script is added at runtime, this wont be called 
void SB_MultiplayerServerClient::LateStart()
{
    //gets the player object, and store it on the player infoclass (this class stores all the online information of the players)
    playerInfoClass->object = GetPlayerObject();

    //initializes the socket
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) 
    {
        std::cerr << "Error 1: multiplayer" << result << std::endl;
        errorConnectingToServer = true;
        return;
    }

    //creates an UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    //if the socket is invalid
    if (sockfd == INVALID_SOCKET) 
    {
        std::cerr << "Error 2: multiplayer" << WSAGetLastError() << std::endl;
        errorConnectingToServer = true;
        WSACleanup();
        return;
    }

    //configures the server address
    server_addr.sin_family = AF_INET;
    //sets the server port
    server_addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP.c_str(), &(server_addr.sin_addr));

    //create the first message string
    std::string message = "FirstEntrance";
    //sends the message to the server
    if (sendto(sockfd, message.c_str(), message.size(), 0, (sockaddr*)&server_addr, addr_len) == SOCKET_ERROR) 
    {
        std::cerr << "Error 3: multiplayer" << WSAGetLastError() << std::endl;
        closesocket(sockfd);
        WSACleanup();
        errorConnectingToServer = true;
        return;
    }

    //starts the receive message thread
    std::thread receiveThread(&SB_MultiplayerServerClient::ReceiveMessages, this);
    //i detach the thread so that it doesnt run seperatly from the main thread
    receiveThread.detach();
}

//updates every frame
void SB_MultiplayerServerClient::Update()
{
    //if we had an error connecting to the server we leave
    if (errorConnectingToServer)
        return;

    //this will precess the received messages
    {
        //i use a lock guard to lock received messages mutex, this makes it so that only one thread can access the receivedMessages at a time
        std::lock_guard<std::mutex> lock(receivedMessagesMutex);
        //while we still have received messages to read
        while (!receivedMessages.empty()) 
        {
            //get the first message from the queue
            std::string received_message = receivedMessages.front();
            //we remove the message frrom the queue, since we are going to process the message now
            receivedMessages.pop();
            
            //if the received message was a yep connected
            if (received_message.find("Yep, you just connected!") != std::string::npos) 
            {
                //get the message to send to the server
                std::string message = "I need a UID for local object:" + std::to_string(playerInfoClass->mylocalIdNetwork);

                //this sends the message to the serveer
                if (sendto(sockfd, message.c_str(), message.size(), 0, (sockaddr*)&server_addr, addr_len) == SOCKET_ERROR) 
                {
                    std::cerr << "Error 4: multiplayer" << WSAGetLastError() << std::endl;
                    errorConnectingToServer = true;
                    closesocket(sockfd);
                    WSACleanup();
                    return;
                }
            }
            //if the received message was our uid
            else if (received_message.find("Assigned UID:") != std::string::npos) 
            {
                //we parse the message for us to be able to get the local and global id
                std::istringstream iss(received_message);
                std::string token;

                //this makes it so we skip the Assigned uid part
                std::getline(iss, token, ':');

                //this reads the local id
                std::getline(iss, token, ';');
                staticLocalIdNetwork++;
                playerInfoClass->mylocalIdNetwork = staticLocalIdNetwork;

                //this reads the unique id network
                std::getline(iss, token, ';');
                playerInfoClass->uniqueNetworkID = std::stoi(token);

                std::cout << "Local ID: " << playerInfoClass->mylocalIdNetwork << std::endl;
                std::cout << "Global ID: " << playerInfoClass->uniqueNetworkID << std::endl;
            }
            //if the received message was an object data
            else if (received_message.find("Object data;") != std::string::npos) 
            {
                //we get the object received to an player info class
                PlayerInfoClass tempPlayerInfoReceived = ParseObjectData(received_message);

                //if its not our id
                if (playerInfoClass->uniqueNetworkID != tempPlayerInfoReceived.uniqueNetworkID)
                {
                    //if the id is invalid, leave
                    if (tempPlayerInfoReceived.uniqueNetworkID < 0 || playerInfoClass->uniqueNetworkID < 0)
                        return;

                    //if we have alreedy created the enemy, update its position
                    if (otherPlayersInfoMap.find(tempPlayerInfoReceived.uniqueNetworkID) != otherPlayersInfoMap.end())
                    {
                        otherPlayersInfoMap[tempPlayerInfoReceived.uniqueNetworkID].position = tempPlayerInfoReceived.position;
                        otherPlayersInfoMap[tempPlayerInfoReceived.uniqueNetworkID].rotation = tempPlayerInfoReceived.rotation;
                        otherPlayersInfoMap[tempPlayerInfoReceived.uniqueNetworkID].uniqueNetworkID = tempPlayerInfoReceived.uniqueNetworkID;
                        otherPlayersInfoMap[tempPlayerInfoReceived.uniqueNetworkID].object->SetPosition(Vector2(tempPlayerInfoReceived.position.x, tempPlayerInfoReceived.position.y));
                        otherPlayersInfoMap[tempPlayerInfoReceived.uniqueNetworkID].object->SetRotation(tempPlayerInfoReceived.rotation.x);

                        std::cout << otherPlayersInfoMap[tempPlayerInfoReceived.uniqueNetworkID].position.x << " : " << otherPlayersInfoMap[tempPlayerInfoReceived.uniqueNetworkID].position.y << std::endl;
                    }
                    //if we have havent created the enemy, creates a new player and updates the new enemy pos
                    else
                    {
                        otherPlayersInfoMap[tempPlayerInfoReceived.uniqueNetworkID].position = tempPlayerInfoReceived.position;
                        otherPlayersInfoMap[tempPlayerInfoReceived.uniqueNetworkID].rotation = tempPlayerInfoReceived.rotation;
                        otherPlayersInfoMap[tempPlayerInfoReceived.uniqueNetworkID].uniqueNetworkID = tempPlayerInfoReceived.uniqueNetworkID;
                        otherPlayersInfoMap[tempPlayerInfoReceived.uniqueNetworkID].object = CreateNewEnemyPlayer();
                        otherPlayersInfoMap[tempPlayerInfoReceived.uniqueNetworkID].object->SetPosition(Vector2(tempPlayerInfoReceived.position.x, tempPlayerInfoReceived.position.y));
                        otherPlayersInfoMap[tempPlayerInfoReceived.uniqueNetworkID].object->SetRotation(tempPlayerInfoReceived.rotation.x);
                    }
                }
            }
        }
    }

    //updates our player pos and rot, we are using vector 3 and quaternions because the server is seetud up for 3d games
    playerInfoClass->position = Vector3(playerInfoClass->object->GetPosition().x, playerInfoClass->object->GetPosition().y,0);
    playerInfoClass->rotation = Quaternion(playerInfoClass->object->GetRotation(), playerInfoClass->object->GetRotation(), playerInfoClass->object->GetRotation(), playerInfoClass->object->GetRotation());
    //this will store the data to send to the server
    std::ostringstream playerDataToSend;
    playerDataToSend << std::fixed << std::setprecision(2)
        << "Object data;" << playerInfoClass->uniqueNetworkID << ";"
        << playerInfoClass->position.x << ";" << playerInfoClass->position.y << ";" << playerInfoClass->position.z << ";"
        << playerInfoClass->rotation.x << ";" << playerInfoClass->rotation.y << ";" << playerInfoClass->rotation.z << ";" << playerInfoClass->rotation.w << ";";

    //get the string to send
    std::string messageMyObjectData = playerDataToSend.str();
    //send my player info to the server
    if (sendto(sockfd, messageMyObjectData.c_str(), messageMyObjectData.size(), 0, (sockaddr*)&server_addr, addr_len) == SOCKET_ERROR) 
    {
        std::cerr << "Error 5: multiplayer"  << WSAGetLastError() << std::endl;
        errorConnectingToServer = true;
        closesocket(sockfd);
        WSACleanup();
        return;
    }
}

#pragma region Helper Functions

//this gets the player object
GameObject* SB_MultiplayerServerClient::GetPlayerObject()
{
	GameObject* player = nullptr;
    //loop though all gameobjects
	for (GameObject* currentObject : *Scene::GetInstance()->GetAllObjects())
	{
        //if we have a move script, it means we are the gameobject
		if (currentObject->TryGetComponent<SB_CharacterMovement>(Component::typeOfComponent::ScriptBehaviour))
			player = currentObject;
	}

	if (player == nullptr)
	{
		std::cout << "Error: no character player was found;" << std::endl;
	}
	else
		std::cout << player->name;

	return player;
}

//this creates a new enemy player
GameObject* SB_MultiplayerServerClient::CreateNewEnemyPlayer()
{
    //creates the enemy gameobject
	GameObject* enemyPlayer = new GameObject("EnemyPlayer", new Transform(Vector2(0, 0), 0, Vector2(1, 1)));

    //creates the shape box
	Shape_Box* shapeBoxOfEnemy = new Shape_Box();

    //createes the com_mesh
	Com_Mesh* Com_MeshOfEnemy = new Com_Mesh();

    //creates its rigidbody
	RigidBodySettings bodySettingsOfEnemy = RigidBodySettings(kinematicBody, 1, 1, false, true, false, false, 0);
	RigidBody* rbOfEnemy = new RigidBody(bodySettingsOfEnemy);

    //creates the coll
	SquareCollider* squareCollOfEnemy = new SquareCollider(Vector2(0.122, 0.122), Vector2(0, 0));

    //sets its texture adn shape
	Com_MeshOfEnemy->SetTexture("../Textures/EnemyPlayer.png");
	Com_MeshOfEnemy->SetShape(shapeBoxOfEnemy);

    //adds its components
	enemyPlayer->AddComponent(Com_MeshOfEnemy);
	enemyPlayer->AddComponent(rbOfEnemy);
	enemyPlayer->AddComponent(squareCollOfEnemy);

	//add an object to the scene
	Scene::GetInstance()->AddObject(enemyPlayer);
	return enemyPlayer;
}

//this receives a string containing the object data, and returns it in the player info class
SB_MultiplayerServerClient::PlayerInfoClass SB_MultiplayerServerClient::ParseObjectData(const std::string& objectData)
{
    //creates an player info class that will store the received message
	PlayerInfoClass playerInfoReceived;

    //ceate a string stream
	std::istringstream iss(objectData);
	std::string token;
    //this will store all the divided string
	std::vector<std::string> values;

	//we split the string by the ; and store it in the values
	while (std::getline(iss, token, ';'))
	{
		values.push_back(token);
	}

	//gets the unique id netweok (stoi since its an int)
	playerInfoReceived.uniqueNetworkID = std::stoi(values[1]);
    //gets the pos and rot (stof since its a float)
	playerInfoReceived.position.x = std::stof(ReplaceAllCharacters(values[2], ',', '.'));
	playerInfoReceived.position.y = std::stof(ReplaceAllCharacters(values[3], ',', '.'));
	playerInfoReceived.position.z = std::stof(ReplaceAllCharacters(values[4], ',', '.'));
	playerInfoReceived.rotation.x = std::stof(ReplaceAllCharacters(values[5], ',', '.'));
	playerInfoReceived.rotation.y = std::stof(ReplaceAllCharacters(values[6], ',', '.'));
	playerInfoReceived.rotation.z = std::stof(ReplaceAllCharacters(values[7], ',', '.'));
	playerInfoReceived.rotation.w = std::stof(ReplaceAllCharacters(values[8], ',', '.'));

    //returns the class
	return playerInfoReceived;
}

//this receives the messages, this is done on a seperate thread, to not freaze the game
void SB_MultiplayerServerClient::ReceiveMessages()
{
    //infinite loop too always keep receiving serve messages
    while (true) 
    {
        int recv_len;
        //receives an message and stores the length of the message in recv_len
        if ((recv_len = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (sockaddr*)&server_addr, &addr_len)) == SOCKET_ERROR) 
        {
            std::cerr << "Error 6: multiplayer" << WSAGetLastError() << std::endl;
            closesocket(sockfd);
            WSACleanup();
            return;
        }

        //this verifies that its null-terminated
        buffer[recv_len] = '\0';

        //we lock the mutex to make it safe
        {
            std::lock_guard<std::mutex> lock(receivedMessagesMutex);
            receivedMessages.push(std::string(buffer, recv_len));
        }
    }
}

//this receis a string, and replaces the given character with the given charateer to replace to
std::string SB_MultiplayerServerClient::ReplaceAllCharacters(const std::string& str, char from, char to)
{
    //stores the string
    std::string result(str);
    //loops through the string
    for (auto& ch : result) 
    {
        //replace the character
        if (ch == from) 
        {
            ch = to;
        }
    }
    return result;
}
#pragma endregion
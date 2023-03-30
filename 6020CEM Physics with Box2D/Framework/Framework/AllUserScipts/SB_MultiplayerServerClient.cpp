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
    // Clean up (this code will not be executed because of the infinite loop)
    closesocket(sockfd);
    WSACleanup();
}

void SB_MultiplayerServerClient::Start()
{
}

void SB_MultiplayerServerClient::LateStart()
{
    playerInfoClass->object = GetPlayerObject();

    // Initialize Winsock
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "Error initializing Winsock: " << result << std::endl;
        errorConnectingToServer = false;
        return;
    }

    // Create a UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd == INVALID_SOCKET) {
        std::cerr << "Error creating socket: " << WSAGetLastError() << std::endl;
        errorConnectingToServer = false;
        WSACleanup();
        return;
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP.c_str(), &(server_addr.sin_addr));

    // Send a message to the server
    std::string message = "FirstEntrance";
    if (sendto(sockfd, message.c_str(), message.size(), 0, (sockaddr*)&server_addr, addr_len) == SOCKET_ERROR) {
        std::cerr << "Error sending message: " << WSAGetLastError() << std::endl;
        closesocket(sockfd);
        WSACleanup();
        errorConnectingToServer = true;
        return;
    }

    errorConnectingToServer = false;
    std::thread receiveThread(&SB_MultiplayerServerClient::ReceiveMessages, this);
    receiveThread.detach();
}

void SB_MultiplayerServerClient::Update()
{
    if (errorConnectingToServer)
        return;

    // Process the received messages
    {
        std::lock_guard<std::mutex> lock(receivedMessagesMutex);
        while (!receivedMessages.empty()) 
        {
            std::string received_message = receivedMessages.front();
            receivedMessages.pop();
            
            // Handle the received message here
            if (received_message.find("Yep, you just connected!") != std::string::npos) {
                // Send a message to the server
                std::string message = "I need a UID for local object:" + std::to_string(playerInfoClass->mylocalIdNetwork);
                if (sendto(sockfd, message.c_str(), message.size(), 0, (sockaddr*)&server_addr, addr_len) == SOCKET_ERROR) {
                    std::cerr << "Error sending message: " << WSAGetLastError() << std::endl;
                    closesocket(sockfd);
                    WSACleanup();
                    return;
                }
            }
            else if (received_message.find("Assigned UID:") != std::string::npos) {
                std::istringstream iss(received_message);
                std::string token;

                // Skip the "Assigned UID:" part
                std::getline(iss, token, ':');

                // Read and store the local ID
                std::getline(iss, token, ';');
                staticLocalIdNetwork++;
                playerInfoClass->mylocalIdNetwork = staticLocalIdNetwork;

                // Read and store the global ID
                std::getline(iss, token, ';');
                playerInfoClass->uniqueNetworkID = std::stoi(token);

                std::cout << "Local ID: " << playerInfoClass->mylocalIdNetwork << std::endl;
                std::cout << "Global ID: " << playerInfoClass->uniqueNetworkID << std::endl;
            }
            else if (received_message.find("Object data;") != std::string::npos) 
            {
                PlayerInfoClass tempPlayerInfoReceived = ParseObjectData(received_message);

                if (playerInfoClass->uniqueNetworkID != tempPlayerInfoReceived.uniqueNetworkID)
                {
                    if (tempPlayerInfoReceived.uniqueNetworkID < 0 || playerInfoClass->uniqueNetworkID < 0)
                        return;

                    if (otherPlayersInfoMap.find(tempPlayerInfoReceived.uniqueNetworkID) != otherPlayersInfoMap.end())
                    {
                        otherPlayersInfoMap[tempPlayerInfoReceived.uniqueNetworkID].position = tempPlayerInfoReceived.position;
                        otherPlayersInfoMap[tempPlayerInfoReceived.uniqueNetworkID].rotation = tempPlayerInfoReceived.rotation;
                        otherPlayersInfoMap[tempPlayerInfoReceived.uniqueNetworkID].uniqueNetworkID = tempPlayerInfoReceived.uniqueNetworkID;
                        otherPlayersInfoMap[tempPlayerInfoReceived.uniqueNetworkID].object->SetPosition(Vector2(tempPlayerInfoReceived.position.x, tempPlayerInfoReceived.position.y));
                        otherPlayersInfoMap[tempPlayerInfoReceived.uniqueNetworkID].object->SetRotation(tempPlayerInfoReceived.rotation.x);

                        std::cout << otherPlayersInfoMap[tempPlayerInfoReceived.uniqueNetworkID].position.x << " : " << otherPlayersInfoMap[tempPlayerInfoReceived.uniqueNetworkID].position.y << std::endl;
                    }
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

    playerInfoClass->position = Vector3(playerInfoClass->object->GetPosition().x, playerInfoClass->object->GetPosition().y,0);
    playerInfoClass->rotation = Quaternion(playerInfoClass->object->GetRotation(), playerInfoClass->object->GetRotation(), playerInfoClass->object->GetRotation(), playerInfoClass->object->GetRotation());
    std::ostringstream playerDataToSend;
    playerDataToSend << std::fixed << std::setprecision(2)
        << "Object data;" << playerInfoClass->uniqueNetworkID << ";"
        << playerInfoClass->position.x << ";" << playerInfoClass->position.y << ";" << playerInfoClass->position.z << ";"
        << playerInfoClass->rotation.x << ";" << playerInfoClass->rotation.y << ";" << playerInfoClass->rotation.z << ";" << playerInfoClass->rotation.w << ";";

    std::string messageMyObjectData = playerDataToSend.str();
    if (sendto(sockfd, messageMyObjectData.c_str(), messageMyObjectData.size(), 0, (sockaddr*)&server_addr, addr_len) == SOCKET_ERROR) {
        std::cerr << "Error sending message: " << WSAGetLastError() << std::endl;
        closesocket(sockfd);
        WSACleanup();
        return;
    }

    // Add a sleep interval to avoid overloading the server (optional)
    //Sleep(1000); // Sleep for 1000 milliseconds (1 second)
}

#pragma region Helper Functions


GameObject* SB_MultiplayerServerClient::GetPlayerObject()
{
	GameObject* player = nullptr;
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

	return player;
}

GameObject* SB_MultiplayerServerClient::CreateNewEnemyPlayer()
{
	GameObject* enemyPlayer = new GameObject("EnemyPlayer", new Transform(Vector2(0, 0), 0, Vector2(1, 1)));

	Shape_Box* shapeBoxOfEnemy = new Shape_Box();

	Com_Mesh* Com_MeshOfEnemy = new Com_Mesh();

	RigidBodySettings bodySettingsOfEnemy = RigidBodySettings(kinematicBody, 1, 1, false, true, false, false, 0);
	RigidBody* rbOfEnemy = new RigidBody(bodySettingsOfEnemy);

	SquareCollider* squareCollOfEnemy = new SquareCollider(Vector2(0.122, 0.122), Vector2(0, 0));

	Com_MeshOfEnemy->SetTexture("../Textures/EnemyPlayer.png");
	Com_MeshOfEnemy->SetShape(shapeBoxOfEnemy);

	enemyPlayer->AddComponent(Com_MeshOfEnemy);
	enemyPlayer->AddComponent(rbOfEnemy);
	enemyPlayer->AddComponent(squareCollOfEnemy);

	//add an object to the scene
	Scene::GetInstance()->AddObject(enemyPlayer);
	return enemyPlayer;
}

SB_MultiplayerServerClient::PlayerInfoClass SB_MultiplayerServerClient::ParseObjectData(const std::string& objectData)
{
	PlayerInfoClass playerInfoReceived;
	std::istringstream iss(objectData);
	std::string token;
	std::vector<std::string> values;

	// Split the string by ';'
	while (std::getline(iss, token, ';'))
	{
		values.push_back(token);
	}

	// Parse the values
	playerInfoReceived.uniqueNetworkID = std::stoi(values[1]);
	playerInfoReceived.position.x = std::stof(ReplaceAllCharacters(values[2], ',', '.'));
	playerInfoReceived.position.y = std::stof(ReplaceAllCharacters(values[3], ',', '.'));
	playerInfoReceived.position.z = std::stof(ReplaceAllCharacters(values[4], ',', '.'));
	playerInfoReceived.rotation.x = std::stof(ReplaceAllCharacters(values[5], ',', '.'));
	playerInfoReceived.rotation.y = std::stof(ReplaceAllCharacters(values[6], ',', '.'));
	playerInfoReceived.rotation.z = std::stof(ReplaceAllCharacters(values[7], ',', '.'));
	playerInfoReceived.rotation.w = std::stof(ReplaceAllCharacters(values[8], ',', '.'));

	return playerInfoReceived;
}

void SB_MultiplayerServerClient::ReceiveMessages()
{
    while (true) 
    {
        int recv_len;
        if ((recv_len = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (sockaddr*)&server_addr, &addr_len)) == SOCKET_ERROR) {
            std::cerr << "Error receiving message: " << WSAGetLastError() << std::endl;
            closesocket(sockfd);
            WSACleanup();
            return;
        }

        // Ensure the buffer is properly null-terminated
        buffer[recv_len] = '\0';

        // Lock the mutex to ensure safe access to the received messages queue
        {
            std::lock_guard<std::mutex> lock(receivedMessagesMutex);
            receivedMessages.push(std::string(buffer, recv_len));
        }
    }
}

std::string SB_MultiplayerServerClient::ReplaceAllCharacters(const std::string& str, char from, char to)
{
    std::string result(str);
    for (auto& ch : result) {
        if (ch == from) {
            ch = to;
        }
    }
    return result;
}
#pragma endregion
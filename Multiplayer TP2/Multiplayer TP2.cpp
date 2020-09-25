#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include "TicTacToe.h"

#pragma comment (lib, "ws2_32.lib")

using namespace std;

struct message
{
	char cmd;
	char data[255];
};

/*
0 = ?
1 = alias
2 = text
3 = play
4 = gameText
*/




int main()
{
	WSADATA data;
	WORD version = MAKEWORD(2, 2);
	int port;
	string ip;
	const int textSize = 100;
	char dataToSend[textSize];
	message alias;
	alias.cmd = 1;
	message customMessage;
	sockaddr_in client;
	int clientSize = sizeof(client);
	char clientName[16];

	//Game
	TicTacToe* gameTest;
	gameTest = new TicTacToe();

	gameTest->init();




	ip = "127.0.0.1";

	// inicializar winsock
	int isOK = WSAStartup(version, &data); //If return = 0 todo ok if not error code
	if (isOK != 0)
	{
		// hubo un error
		std::cout << "Cant start!" << isOK;
		return -1;
	}

	// indicar ip y puerto de destino
	sockaddr_in server;
	server.sin_family = AF_INET; // AF_INET = IPv4
	server.sin_port = htons(8900/*port*/); // puerto de destino
	inet_pton(AF_INET, ip.c_str(), &server.sin_addr); // ip addr destino



	// crear listening socket
	SOCKET listening = socket(AF_INET, SOCK_DGRAM, 0);
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(8901); // puerto en el que vamos a escuchar	
	hint.sin_addr.S_un.S_addr = ADDR_ANY;
	int bindResult = bind(listening, (sockaddr*)&hint, sizeof(hint));

	cout << "Enter Alias" << endl;
	cin.getline(alias.data, sizeof(alias.data));

	// enviar data a traves del socket	
	int sendOK = sendto(listening, (char*)&alias, sizeof(alias), 0, (sockaddr*)&server, sizeof(server));
	if (sendOK == SOCKET_ERROR)
	{
		// hubo un error
		std::cout << "Hubo un error al enviar! " << sendOK;
		return -1;
	}
	memset((char*)&customMessage, 0, sizeof(customMessage));
	memset(&client, 0, sizeof(client));
	memset(clientName, 0, sizeof(clientName));

	while (true)
	{

		memset((char*)&customMessage, 0, sizeof(customMessage));
		int bytesIn = recvfrom(listening, (char*)&customMessage, sizeof(customMessage), 0, (sockaddr*)&client, &clientSize);

		switch (customMessage.cmd)
		{
		case 1:
			cout << "You face " << (string)customMessage.data  << endl;
			gameTest->displayInstructions();
			break;
		case 2:
			cout << customMessage.data << endl;
			break;
		case 3:
			gameTest->UpdateMat(customMessage.data);
			gameTest->display();
			break;
		case 4:
			cout << customMessage.data << endl;
			memset((char*)&customMessage, 0, sizeof(customMessage));

			customMessage.cmd = (char)3;
			cin.getline(customMessage.data, sizeof(customMessage.data));
			sendOK = sendto(listening, (char*)&customMessage, sizeof(customMessage), 0, (sockaddr*)&server, sizeof(server));
			memset((char*)&customMessage, 0, sizeof(customMessage));
			break;
		case 5:
			cout << customMessage.data << endl;
			memset((char*)&customMessage, 0, sizeof(customMessage));

			customMessage.cmd = (char)5;
			cin.getline(customMessage.data, sizeof(customMessage.data));
			sendOK = sendto(listening, (char*)&customMessage, sizeof(customMessage), 0, (sockaddr*)&server, sizeof(server));
			memset((char*)&customMessage, 0, sizeof(customMessage));
		default:

			break;
		}
		memset((char*)&customMessage, 0, sizeof(customMessage));
		if (sendOK == SOCKET_ERROR)
		{
			// hubo un error
			std::cout << "Hubo un error al enviar! " << sendOK;
			return -1;
		}
	}


	cin.get();



	// cerrar el socket
	closesocket(listening);

	// cerrar winsock
	WSACleanup();

	return 0;
}


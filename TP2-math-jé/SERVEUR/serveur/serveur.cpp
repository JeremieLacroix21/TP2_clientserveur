#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
// link with Ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

int main()
{
	WSADATA wsaData; SOCKADDR_IN sin;
	SOCKET ClientSocket, ListenSocket = INVALID_SOCKET;
	char msg[512], recvbuf[512]; 
	std::string mot; 
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8080);
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		printf("WSAStartup failed: %d\n", iResult); return 1;
	}
	ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ListenSocket == INVALID_SOCKET)
	{
		printf("Error at socket(): %d\n", WSAGetLastError()); 
		WSACleanup(); 
		return 1;
	}
	iResult = bind(ListenSocket, (SOCKADDR*)& sin, sizeof(sin));
	if (iResult == SOCKET_ERROR)
	{
		printf("bind failed: %d", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		printf("listen failed: %d\n", WSAGetLastError());
		closesocket(ListenSocket); 
		WSACleanup();
		return 1;
	}
	ClientSocket = INVALID_SOCKET; 
	std::cout << "Attendre une connexion d'un client ..... \n";
	ClientSocket = accept(ListenSocket, NULL, NULL); 
	std::cout << "Un client vient de se connecter ..... \n";
	if (ClientSocket == INVALID_SOCKET)
	{
		printf("accept failed: %d\n", WSAGetLastError()); 
		closesocket(ListenSocket); 
		WSACleanup(); 
		return 1;
	}
	iResult = recv(ClientSocket, recvbuf, 512, 0);
	if (iResult > 0)
	{
		memset(&msg, 0, sizeof(msg)); 
		strncpy(msg, recvbuf, iResult); 
		printf("Recu: %s\n", msg);
	}
	else if (iResult == 0) printf("Connection closed\n");
	else
	{ printf("recv failed: %d\n", WSAGetLastError()); 
	closesocket(ClientSocket); 
	WSACleanup(); 
	return 1; 
	}
	closesocket(ListenSocket);
	WSACleanup(); 
	getchar();
	return 0;
}




#include<stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <fstream>

#include "FileExplore.h"
#include "Client.h"

#pragma comment(lib, "Ws2_32.lib")
#define DEFAULT_PORT "27015"
#define DEFAULT_BUFLEN 512




int __cdecl main(int argc, char** argv){

    WSADATA WsaData;
	int recvbuflen = DEFAULT_BUFLEN;
	const char* sendbuf = "Test";
	char recvbuf[DEFAULT_BUFLEN];
	int initResult;

	struct addrinfo* result = NULL, * ptr = NULL, Hints;


	// Validate the parameters
	if (argc != 2) {
		printf("usage: %s server-name\n", argv[0]);
		return 1;
	}

	// Initialize Winsock
	initResult = WSAStartup(MAKEWORD(2, 2), &WsaData);  //init ws2_32.dll
	if (initResult != 0) {
		printf("WSAStartup failed: %d\n", initResult);
		return false;
	}


	ZeroMemory(&Hints, sizeof(Hints));
	Hints.ai_family = AF_INET;
	Hints.ai_socktype = SOCK_STREAM;
	Hints.ai_protocol = IPPROTO_TCP;


	//resolve server address & port     //error here 11001
	initResult = getaddrinfo(argv[1], DEFAULT_PORT, &Hints, &result);
	if (initResult != 0) {
		printf("getaddrinfo failed: %d\n", initResult);
		WSACleanup();
		return false;
	}

	SOCKET ConnectSocket = INVALID_SOCKET;


	// Attempt to connect to the server
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			return false;
		}

		initResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (initResult == SOCKET_ERROR) {
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}


	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server \n");
		WSACleanup();
		return false;
	}



	//Get file to send
	//use Search functiont to check if exists first.
	//ExploreFuncs.Search()
	//std::ifstream FileToSend(File, std::ios::binary);
    
	//if (!FileToSend) {
	//	std::cerr << "Failed to open file: " << File << std::endl;
	//	closesocket(ConnectSocket);
	//	WSACleanup();
	//	return false;
	//}
    //std::string FileName = File.filename().string();
	//int FileNameSize = static_cast<int>(FileName.size());
	//initResult = send(ConnectSocket, reinterpret_cast<const char*>(&FileNameSize), sizeof(FileNameSize), 0);
	//if (initResult == SOCKET_ERROR) {
	//	printf("send failed: %d\n", WSAGetLastError());
	//	closesocket(ConnectSocket);
	//	WSACleanup();
	//	return false;
	//}
    //
	//initResult = send(ConnectSocket, FileName.c_str(), FileNameSize, 0);
	//if (initResult == SOCKET_ERROR) {
	//	printf("send failed: %d\n", WSAGetLastError());
	//	closesocket(ConnectSocket);
	//	WSACleanup();
	//	return false;
	//}
    //
	//while (FileToSend.read(recvbuf, recvbuflen) || FileToSend.gcount() > 0) {
	//	initResult = send(ConnectSocket, recvbuf, static_cast<int>(FileToSend.gcount()), 0);
	//	if (initResult == SOCKET_ERROR) {
	//		printf("send failed: %d\n", WSAGetLastError());
	//		closesocket(ConnectSocket);
	//		WSACleanup();
	//		return false;
	//	}
	//}




	//// Send an initial buffer
	//initResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
	//if (initResult == SOCKET_ERROR) {
	//	printf("send failed: %d\n", WSAGetLastError());
	//	closesocket(ConnectSocket);
	//	WSACleanup();
	//	return 1;
	//}
	//printf("Bytes Sent: %ld\n", initResult);

	initResult = shutdown(ConnectSocket, SD_SEND);
	if (initResult == SOCKET_ERROR) {
		printf("Shutdown failed %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return false;
	}

	do {
		initResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		if (initResult > 0) {
			printf("Bytes recived: %d\n", initResult);
		}
		else if (initResult == 0) {
			printf("Connection closed\n");
		}
		else {
			printf("Recv failed: %d\n", WSAGetLastError());

		}
	} while (initResult > 0);

	closesocket(ConnectSocket);
	WSACleanup();
	return true;
}

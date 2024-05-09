#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")
#define DEFAULT_PORT "27015"
#define DEFAULT_BUFLEN 512


WSADATA WsaData;



int main(int argc, char **argv  ) {

    int recvbuflen = DEFAULT_BUFLEN;
    const char* sendbuf = "Test";
    char recvbuf[DEFAULT_BUFLEN];
    int initResult;
    // Initialize Winsock
    initResult = WSAStartup(MAKEWORD(2, 2), &WsaData);  //init ws2_32.dll
    if (initResult != 0) {
        printf("WSAStartup failed: %d\n", initResult);
        return 1;
    }

    struct addrinfo* result = NULL, * ptr = NULL, Hints;

    ZeroMemory(&Hints, sizeof(Hints));
    Hints.ai_family = AF_INET;
    Hints.ai_socktype = SOCK_STREAM;

    //resolve server address & port
    initResult = getaddrinfo(argv[1], DEFAULT_PORT, &Hints, &result);
    if (initResult != 0) {
        printf("getaddrinfo failed: %d\n", initResult);
        WSACleanup();
        return 1;
    }

    SOCKET ConnectSocket = INVALID_SOCKET;

    ptr = result;
    ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    if (ConnectSocket == INVALID_SOCKET) {
        printf("Error at socket(): %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    initResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
    if (initResult == SOCKET_ERROR) {
        closesocket(ConnectSocket);
        ConnectSocket = INVALID_SOCKET;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server \n");
        WSACleanup();
        return 1;
    }

    // Send an initial buffer
    initResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
    if (initResult == SOCKET_ERROR) {
        printf("send failed: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }
    printf("Bytes Sent: %ld\n", initResult);

    initResult = shutdown(ConnectSocket, SD_SEND);
    if (initResult == SOCKET_ERROR) {
        printf("Shutdown failed %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
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
    return 0;




}

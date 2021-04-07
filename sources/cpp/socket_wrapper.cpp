#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <stdio.h> 
#include <winsock2.h>
#include <string.h> 
#include <Windows.h>
#include <ws2tcpip.h>
#include <winsock.h>
#pragma comment(lib, "Ws2_32.lib")

using namespace std;

class Socket
{

	int sockfd;

public:
	Socket()
	{
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
	}

	bool connect_to_server(const char* server_ip, unsigned short int port)
	{
		sockaddr_in serv_addr;

		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(port);
		serv_addr.sin_addr.s_addr = inet_addr(server_ip);

		if (serv_addr.sin_addr.s_addr == -1)
		{
			return false;
		}

		if (connect(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
		{
			return false;
		}

		return true;
	}

	int receive(char buffer[], int len)
	{
		return recv(sockfd, buffer, len, 0);
	}

	int send(const char buffer[])
	{
		return ::send(sockfd, buffer, strlen(buffer), 0);
	}

};


#define BUFFER_LEN 1024
int main()
{
	WSADATA data;
	WSAStartup(MAKEWORD(2, 2), &data);
	char buffer[BUFFER_LEN + 1] = { 0 };
	const char* message = "message";

	Socket socket;

	if (!socket.connect_to_server("127.0.0.1", 7777))
	{
		cout << "Connetion failed" << endl;
		return -1;
	}

	cout << "Bytes received: " << socket.receive(buffer, BUFFER_LEN) << endl;
	cout << buffer << endl;

	cout << "Bytes sent: " << socket.send(message) << endl;
	cout << message << endl;
}
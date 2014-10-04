#pragma once
#include <winsock2.h>

#include<string>

class UDPReceiver
{
public:
	UDPReceiver(void);

	//initializes the winsock and server
	int Initialize();

	//sends a UDP message
	int ReceiveUDPMessage(std::string&);

	~UDPReceiver(void);
private:
	SOCKET sd;
	sockaddr_in server;
	int server_length;
};

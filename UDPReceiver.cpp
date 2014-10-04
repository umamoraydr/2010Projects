#include "StdAfx.h"
#include "UDPReceiver.h"

#include <iostream>
using namespace std;


UDPReceiver::UDPReceiver(void)
{
}

//initializes the winsock and server
//for simplicity return 1 on success and -1 on error.
//CHECK ALL RET VALS
int UDPReceiver::Initialize()
{
	
	
	// INITIALIZE THE WINSOCK
			WORD wVersionRequested;
			WSADATA wsaData;
			int iReturn=0;

			/* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
			wVersionRequested = MAKEWORD(2, 2);

			iReturn = WSAStartup(wVersionRequested, &wsaData);
			if ( iReturn != 0) {
				/* Tell the user that we could not find a usable */
				/* Winsock DLL.                                  */				
				cout << "WSAStartup failed with error: " << iReturn;
				return -1;
			}

			/* Confirm that the WinSock DLL supports 2.2.*/
			/* Note that if the DLL supports versions greater    */
			/* than 2.2 in addition to 2.2, it will still return */
			/* 2.2 in wVersion since that is the version we      */
			/* requested.                                        */

			if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
				/* Tell the user that we could not find a usable */
				/* WinSock DLL.                                  */
				//printf("Could not find a usable version of Winsock.dll\n");
				cout << "Could not find a usable version of Winsock.dll\n" ;
				WSACleanup();
				return -1;
			}			


	//END INITIALIZE WINSOCK


	//OPEN DATAGRAM SOCKET
			sd = socket(AF_INET, SOCK_DGRAM, 0);
			if (sd == INVALID_SOCKET)
			{
				cout << "Could not create socket.\n" ;
				WSACleanup();
				return -1;
			}
	//END OPEN DATAGRAM SOCKET


	//SET SERVER INFORMATION

			/* Set family and port */
			server.sin_family = AF_INET;
			server.sin_port = htons(20033);

			/* Set address */

			char host_name[128]={0}; // CHECK THIS
			struct hostent *hp;


			/* Get host name of this computer */
			gethostname(host_name, sizeof(host_name));
			hp = gethostbyname(host_name);
			
			/* Check for NULL pointer */
			if (hp == NULL)
			{
				cout << "Could not get host name.\n" ;
				closesocket(sd);
				WSACleanup();
				return -1;
			}

			/* Assign the address */
			server.sin_addr.S_un.S_un_b.s_b1 = hp->h_addr_list[0][0];
			server.sin_addr.S_un.S_un_b.s_b2 = hp->h_addr_list[0][1];
			server.sin_addr.S_un.S_un_b.s_b3 = hp->h_addr_list[0][2];
			server.sin_addr.S_un.S_un_b.s_b4 = hp->h_addr_list[0][3];
		
	//END SET SERVER INFORMATION

	//int server_length = 0;
	server_length = sizeof(struct sockaddr_in);


	/* Bind address to socket */
	if (bind(sd, (struct sockaddr *)&server, 
		sizeof(struct sockaddr_in)) == -1)
	{
		fprintf(stderr, "Could not bind name to socket.\n");
		closesocket(sd);
		WSACleanup();
		return -1;
	}
	return 1;
}

//receives UDP message
//CHECK ALL RET VALS
int UDPReceiver::ReceiveUDPMessage(string& outStrMsg )
{

	char message[100]={0};//check this
	
	
	if ( recvfrom(sd, (char *)&message, 
		(int)sizeof(message), 0, 
		(struct sockaddr *)&server, 
		&server_length ) < 0)
	{
		cout << "Error receiving data.\n";
		closesocket(sd);
		WSACleanup();
		return -1;
	}//end if	
	std::string line( message );//change these
	outStrMsg = message;//change this
	return 1;
}

UDPReceiver::~UDPReceiver(void)
{
	closesocket(sd);
    WSACleanup();
}

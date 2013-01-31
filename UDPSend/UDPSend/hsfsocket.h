#ifndef _HSFSOCKET_H_
#define _HSFSOCKET_H_

#include <netinet/in.h>		//IPv4 socket address structures
#include <arpa/inet.h>
#include "packets.h"

#define SOCKET_ERROR -1
typedef  int SOCKET;

class CUDPSocket
{
	public:
		CUDPSocket();
		~CUDPSocket();

		int MakeNonBlocking(void);
		int Initialise(void);
		int Bind(const int Port);
		int Receive(char * Buffer);
		int Send(char * Buffer);
		void SetDestinationAddress(char * IP, const int Port);
		sockaddr_in GetDestinationAddress(void);

	protected:
		SOCKET m_Socket;
		socklen_t m_SocketAddressSize;
		int m_Ret;
		struct sockaddr_in m_LocalAddress, m_RemoteAddress;

};

#endif
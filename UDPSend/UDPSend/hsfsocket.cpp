#include "hsfsocket.h"
#include <stdio.h>
#include <unistd.h>			//UNIX stuff needed for close()
#include <netinet/in.h>		//IPv4 socket address structures
#include <netdb.h>			//Access to DNS lookup
#include <arpa/inet.h>		//inet_ntop functions
#include <sys/socket.h>		//Socket functions
#include <fcntl.h>

CUDPSocket::CUDPSocket()
{
	m_SocketAddressSize = sizeof(sockaddr_in);
	m_Socket = 0;
}

CUDPSocket::~CUDPSocket()
{
	if(m_Socket)close(m_Socket);

	m_Socket = 0;
}


int CUDPSocket::MakeNonBlocking(void)
{
	if ((fcntl(m_Socket, F_SETFL, O_NONBLOCK)) < 0)
		{
			printf("Error:  Can't make Socket nonblocking\n");
			return 0;
		}

	return 1;
}

int CUDPSocket::Initialise(void)
{
	// socket creation
	m_Socket = socket(AF_INET, SOCK_DGRAM, 0);
	if(m_Socket<0)
	{
		printf("Cannot open socket \n");
		return 0;
	}

	return 1;
}

int CUDPSocket::Bind(const int Port)
{
	/* bind socket to local port */
	m_LocalAddress.sin_family 		= AF_INET;
	m_LocalAddress.sin_addr.s_addr 	= htonl(INADDR_ANY);
	m_LocalAddress.sin_port 		= htons(Port);

	int rc = bind (m_Socket, (struct sockaddr *)&m_LocalAddress, m_SocketAddressSize);
	if(rc<0)
	{
		printf("cannot bind port number %d \n", Port);
		return 0;
	}

	return 1;
}

int CUDPSocket::Receive(byte * Buffer)
{
	int n = recvfrom(m_Socket, Buffer, sizeof(MyPacket_t), 0, (struct sockaddr *)&m_RemoteAddress, &m_SocketAddressSize);

	return n;
}

int CUDPSocket::Send(byte * Buffer)
{
	int n = sendto(m_Socket, Buffer, sizeof(MyPacket_t), 0, (struct sockaddr *)&m_RemoteAddress, m_SocketAddressSize);

	return n;
}

sockaddr_in CUDPSocket::GetDestinationAddress(void)
{
	return m_RemoteAddress;
}

void CUDPSocket::SetDestinationAddress(char * IP, const int Port)
{
	m_RemoteAddress.sin_family = AF_INET;
	m_RemoteAddress.sin_port = htons (Port);
	m_RemoteAddress.sin_addr.s_addr = inet_addr (IP);
}


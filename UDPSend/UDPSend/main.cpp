/*
An example of a peer-to-peer UDP sending application
*/

#ifdef USEUNIX
	#include <string.h>
#endif

#include <stdio.h>
#include "hsfsocket.h"

#define LOCALPORT (1501)
#define REMOTEPORT (1500)

int main(int argc, char *argv[])
{
	CUDPSocket UDPSocket;
	char Buffer[PACKETSIZE];

	UDPSocket.Initialise();
  	UDPSocket.MakeNonBlocking();
	//The socket must be bound so that we know the port number
  	UDPSocket.Bind(LOCALPORT);

	//Define where we are sending the data
	UDPSocket.SetDestinationAddress("127.0.0.1", REMOTEPORT);

	// Clear the buffer memory
	memset(Buffer, 0x0, PACKETSIZE);

	printf("Sending data from UDPport:%u to UDPport:%u\n\n", LOCALPORT, REMOTEPORT);

	int Data = 0;

	/* infinite loop */
	while(1)
	{
		// Copy the data into the buffer and send it
		std::memcpy(Buffer, &Data, sizeof(int));
		int n = UDPSocket.Send(Buffer);

		// There has been an error
		if(n == SOCKET_ERROR)
		{
			printf("Send failed\n");
		}

		// data has been sent
		if(n>0)
		{
			printf("Sent %d to IP:%s UDP PORT:%u\n",
			Data,
			inet_ntoa(UDPSocket.GetDestinationAddress().sin_addr),
			ntohs(UDPSocket.GetDestinationAddress().sin_port));

			Data++;
		}

		Sleep(500);
  	}

return 0;
}



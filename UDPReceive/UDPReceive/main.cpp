/*
An example of a peer-to-peer UDP Receive application
*/

#include <stdio.h>
#include "hsfsocket.h"

#ifdef USEUNIX
	#include <string>
	#include <unistd.h>
	#define Sleep usleep
#endif

#define LOCALPORT (1500)
#define REMOTEPORT (1501)

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
  
	printf("Waiting for data on port UDP %u\n\n", LOCALPORT);

	// The data we will receive
	int Data = -1;
	
	/* Infinite loop */
	while(1)
	{		
		/* receive packet in to the buffer*/
		int n = UDPSocket.Receive(Buffer);
		
		// if n>0 we have got some data
		if(n>0)
		{
			// got some data
			memcpy(&Data, Buffer, sizeof(int));
			printf("Received from %s:UDP%u : %d \n", 
			inet_ntoa(UDPSocket.GetDestinationAddress().sin_addr),
			ntohs(UDPSocket.GetDestinationAddress().sin_port),
			Data);
		}
		
	// go round the loop 10 times per second
	Sleep(100);
  	}
return 0;
}



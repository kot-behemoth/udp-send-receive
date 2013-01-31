/*
 An example of a peer-to-peer UDP sending application
 */

#include <stdio.h>
#include <string>
#include <unistd.h>
#include "hsfsocket.h"

const int LOCALPORT  = 1501;
const int REMOTEPORT = 1500;

int main(int argc, char *argv[])
{
	CUDPSocket UDPSocket;
	byte Buffer[PACKETSIZE];

	UDPSocket.Initialise();
  	UDPSocket.MakeNonBlocking();
	//The socket must be bound so that we know the port number
  	UDPSocket.Bind(LOCALPORT);

	//Define where we are sending the data
	UDPSocket.SetDestinationAddress("127.0.0.1", REMOTEPORT);

	// Clear the buffer memory
	memset(Buffer, 0x0, PACKETSIZE);

	printf("Sending data from UDPport:%u to UDPport:%u\n\n", LOCALPORT, REMOTEPORT);

	// Initialise the packet
	MyPacket_t packet = MyPacket_t();
	packet.Acceleration = 1.0f;

	/* infinite loop */
	while(1)
	{
		// Copy the data into the buffer and send it
		memcpy(Buffer, &packet, PACKETSIZE);
		int result = UDPSocket.Send(Buffer);

		// There has been an error
		if(result == SOCKET_ERROR)
		{
			printf("Send failed\n");
		}

		// data has been sent
		if(result > 0)
		{
			printf("Sent to IP:%s UDP PORT:%u\n",
				   inet_ntoa(UDPSocket.GetDestinationAddress().sin_addr),
				   ntohs(UDPSocket.GetDestinationAddress().sin_port));
		    packet.Inspect();
		    packet.Velocity += packet.Acceleration;
		}

		usleep(500);
  	}

	return 0;
}

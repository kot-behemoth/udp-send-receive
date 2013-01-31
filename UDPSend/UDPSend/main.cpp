/*
 An example of a peer-to-peer UDP sending application
 */

#include <stdio.h>
#include <string>
#include <unistd.h>
#include "hsfsocket.h"

const int LOCALPORT = 1500;
const int REMOTEPORT  = 1501;

int main(int argc, char *argv[])
{
	int IDtoAcknowledge = 1;
	/*
	  LOCALSOCKET setup
	 */

	CUDPSocket localSocket;
	localSocket.Initialise();
	localSocket.MakeNonBlocking();
	//The socket must be bound so that we know the port number
	localSocket.Bind(LOCALPORT);
	//Define where we are sending the data
	localSocket.SetDestinationAddress("127.0.0.1", REMOTEPORT);

	printf("Sending data from UDPport:%u to UDPport:%u\n\n", LOCALPORT, REMOTEPORT);

	// Clear the buffer memory
	byte localBuffer[sizeof(MyPacket_t)];
	memset(localBuffer, 0x0, sizeof(MyPacket_t));

	// Initialise the packet
	MyPacket_t sendPacket;// = MyPacket_t();
	sendPacket.Acceleration = 1.0f;

	/* infinite loop */
	while(true)
	{
		if(IDtoAcknowledge)
		{
			// SEND

			// Copy the data into the buffer and send it
			memcpy(localBuffer, &sendPacket, sizeof(MyPacket_t));
			int sendResult = localSocket.Send(localBuffer);

			// There has been an error
			if(sendResult == SOCKET_ERROR)
			{
				printf("Send failed\n");
			}

			// data has been sent
			if(sendResult > 0)
			{
				printf("Sent to IP:%s UDP PORT:%u\n",
					   inet_ntoa(localSocket.GetDestinationAddress().sin_addr),
					   ntohs(localSocket.GetDestinationAddress().sin_port));
				sendPacket.Inspect();

				IDtoAcknowledge = sendPacket.ID;

				sendPacket.ID++;
				sendPacket.Velocity += sendPacket.Acceleration;
			}
		}

		usleep(1000);
	}

	return 0;
}

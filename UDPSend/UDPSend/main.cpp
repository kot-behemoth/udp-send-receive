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
	int IDtoAcknowledge = -1;
	int receivedID = -1;
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

	printf("Sending data FROM: [%u] TO: [%u]\n\n", LOCALPORT, REMOTEPORT);

	// Clear the buffer memory
	byte localBuffer[sizeof(MyPacket_t)];
	memset(localBuffer, NULL, sizeof(MyPacket_t));

	byte receivingBuffer[sizeof(MyPacket_t)];
	memset(receivingBuffer, NULL, sizeof(MyPacket_t));

	// Initialise the packet
	MyPacket_t sendPacket;
	sendPacket.Acceleration = 1.0f;
	MyPacket_t receivePacket;

	/* infinite loop */
	while(true)
	{
		if(IDtoAcknowledge == receivedID)
		{
			// Copy the data into the buffer and send it
			memcpy(localBuffer, &sendPacket, sizeof(MyPacket_t));
			int sendResult = localSocket.Send(localBuffer);
			// data has been sent
			if(sendResult > 0)
			{
				printf("Sent to IP: [%s] PORT: [%u]\n",
					   inet_ntoa(localSocket.GetDestinationAddress().sin_addr),
					   ntohs(localSocket.GetDestinationAddress().sin_port));
				sendPacket.Inspect();

				IDtoAcknowledge = sendPacket.ID;
				receivedID = -1;

				sendPacket.ID++;
				sendPacket.Velocity += sendPacket.Acceleration;
			}
		}

		/* receive packet in to the buffer */
		int receiveResult = localSocket.Receive(receivingBuffer);
		// if n>0 we have got some data
		if(receiveResult > 0)
		{
			memcpy(&receivePacket, receivingBuffer, sizeof(MyPacket_t));
			printf("Received an acknowldment for ID %d\n", receivePacket.ID);
			receivedID = receivePacket.ID;
		}

		usleep(1000000);
	}

	return 0;
}

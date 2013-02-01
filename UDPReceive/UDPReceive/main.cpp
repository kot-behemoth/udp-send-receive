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
	/*
	  REMOTESOCKET setup
	 */

	CUDPSocket remoteSocket;
	remoteSocket.Initialise();
	remoteSocket.MakeNonBlocking();
	//The socket must be bound so that we know the port number
	remoteSocket.Bind(REMOTEPORT);
	//Define where we are sending the data
	remoteSocket.SetDestinationAddress("127.0.0.1", LOCALPORT);

	printf("Receiving data FROM: [%u]\n\n", LOCALPORT, REMOTEPORT);

	// Clear the buffer memory
	byte receivingBuffer[sizeof(MyPacket_t)];
	memset(receivingBuffer, 0x0, sizeof(MyPacket_t));

	byte acknowledgementBuffer[sizeof(MyPacket_t)];
	memset(acknowledgementBuffer, 0x0, sizeof(MyPacket_t));

	// Initialise the packet
	MyPacket_t receivePacket = MyPacket_t();

	/* infinite loop */
	while(true)
	{
		// RECEIVE

		/* receive packet in to the buffer */
		int receiveResult = remoteSocket.Receive(receivingBuffer);

		// if n>0 we have got some data
		if(receiveResult > 0)
		{
			// got some data
			memcpy(&receivePacket, receivingBuffer, sizeof(MyPacket_t));
			printf("Received from IP: [%s] PORT: [%u]\n",
				inet_ntoa(remoteSocket.GetDestinationAddress().sin_addr),
				ntohs(remoteSocket.GetDestinationAddress().sin_port));

			int sendResult = remoteSocket.Send(receivingBuffer);
			// data has been sent
			if(sendResult > 0)
			{
				printf("Sent an acknowldment for ID %d\n", receivePacket.ID);
			}
		}

		usleep(1000000);
	}

	return 0;
}

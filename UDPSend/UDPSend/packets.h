#ifndef _PACKETS_H_
#define _PACKETS_H_

struct MyPacket_t
{
	int ID;
	int Time;
	float x, y, z;
	float Velocity;
	float Accel;
	float Health;

	MyPacket_t()
	{
		ID = 0;
		Time = 0;
		x = y = z = 0.0f;
		Velocity = 0.0f;
		Accel = 0.0f;
		Health = 1.0f;
	}

};

extern const int PACKETSIZE;

#endif
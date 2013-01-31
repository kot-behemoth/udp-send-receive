#ifndef _PACKETS_H_
#define _PACKETS_H_

#include <iostream>

struct MyPacket_t
{
	int ID;
	int Time;
	float x, y, z;
	float Velocity;
	float Acceleration;
	float Health;

	MyPacket_t()
	{
		ID = 1;
		Time = 0;
		x = y = z = 0.0f;
		Velocity = 0.0f;
		Acceleration = 0.0f;
		Health = 1.0f;
	}

	void Inspect()
	{
		std::cout << "{ id: " << ID
				  << " time: " << Time
				  << " v: " << Velocity
				  << " a: " << Acceleration
				  << " }"
				  << std::endl;
	}

};

#endif
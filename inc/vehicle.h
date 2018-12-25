#ifndef VEHICLE_H
#define VEHICLE_H

#include<vector>
#include "common.h"

using namespace std;

class Vehicle
{
public:
	Vehicle(int id);
	void setPosition(double S, double D);
	void setVelocity(double V);
	lane getLane();
	
	int id;
	double s;
	double d;
	double v;
	lane laneID; 
	
	bool collision_chance;
	
};
#endif
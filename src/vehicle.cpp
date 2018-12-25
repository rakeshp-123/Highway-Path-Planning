#include "vehicle.h"

// get lane based on lateral distance from yellow line in middle of road
lane Vehicle::getLane()
{
	lane laneNum = lane::END;
 
	if (d > 0.0 && d < 4.0) 
	{
		laneNum = lane::LEFT;
	} 
	else if (d > 4.0 && d < 8.0) 
	{
		laneNum = lane::CENTER;
	}
	else if (d > 8.0 && d < 12.0) 
	{
		laneNum = lane::RIGHT;
	}
 
	return laneNum;
}

Vehicle::Vehicle(int id){
	laneID = lane::END;
	this->id = id;
	s = 0.0;
	d = 0.0;
	v = 0.0;
	collision_chance = false;
}

void Vehicle::setPosition(double S, double D){
	s = S;
	d = D;
	laneID = getLane();
}

void Vehicle::setVelocity(double V){
	v = V;
}




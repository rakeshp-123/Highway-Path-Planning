#ifndef PLANNER_H
#define PLANNER_H

#include<iostream>
#include "vehicle.h"

using namespace std;

class Planner
{
public:
	Planner();
	Movement planNextMovement(Vehicle& car, std::vector<Vehicle> carList);
	double findOtherCarDistance(Vehicle& car, std::vector<Vehicle>& carList, lane ln, double direction);
	double find_cost(double distance_front, double distance_back, lane ln);
	double find_cost(double distance_front);

};
#endif

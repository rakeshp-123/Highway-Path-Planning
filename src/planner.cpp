#include "planner.h"

Planner::Planner()
{
  
}

//Find cost for left and right lanes
double Planner::find_cost(double front_gap, double back_gap, lane ln) 
{

  	double cost = (1.0 / front_gap + 0.4 / back_gap);

  	if (ln == lane::END) 
  	{
    	cout << "Invalid Lane \n" << endl;
    	return 1000000.0;
  	}

  	if (front_gap < 30.0 || back_gap < 15)
  	{
    	cout << "Not safe to turn. Vehicles in proximity" << endl;
    	cout << "GAP - front: " << front_gap << " rear: " << back_gap << endl;

    	return 1000000.0;
  	}

  	// Add extra cost to compensate unnecessary lane shifting
  	cost = cost * 1.4;

  	if (ln == lane::CENTER) 
  	{
    	// Reward to go to center lane
    	cost = cost * 0.35;
  	}
  	return cost;
}

// cost function for same lane
double Planner::find_cost(double gap) 
{
  	if (gap < 30.0) 
  	{
   	 	cout << "Very near to front vehicle" << endl;
    	cout << "DO shift lane if safe. distance: " << gap << endl;

    	return 1000000.0;

  	} 

  	return 1.0 / gap;
}

//Find the nearest car in front, left front, left rear, right front, right rear.
double Planner::findOtherCarDistance(Vehicle& myCar, std::vector<Vehicle>& carList, lane ln, double dir) 
{

  	if (ln == lane::END) 
  	{
    	return 0.0001;
  	}

  	double distance = 1000000.0;
	//int count = 0;
  	for(auto &car: carList)
    {
    	double gap = (car.s - myCar.s) * dir;

    	if (car.laneID == ln && gap > 0.0 && gap < distance) 
        {
      		distance = gap;
      	//cout<<count<<"\n";
    	}
    	//count++;
 	}

  	return distance;
}



Movement Planner::planNextMovement(Vehicle& car, std::vector<Vehicle> carList)
{
	int lane_curr = static_cast<int>(car.laneID);
	int lane_left = (lane_curr == 0)?static_cast<int>(lane::END):(lane_curr - 1);
	int lane_right = (lane_curr == static_cast<int>(lane::RIGHT))?static_cast<int>(lane::END):(lane_curr + 1);
	double backDir = -1.0;
	double frontDir = 1.0;	
	
  	cout<<"car.laneID: "<<static_cast<int>(car.laneID)<<"\n";
  	double front_car = findOtherCarDistance(car, carList, car.laneID, frontDir);
  	cout<<"front_car: "<<front_car<<"\n";
    double keepLane_cost = find_cost(front_car);
  
  	cout<<"keepLane_cost: "<<keepLane_cost<<"\n";
	double front_left_car = findOtherCarDistance(car, carList, static_cast<lane>(lane_left), frontDir);
  	cout<<"front_left_car: "<<front_left_car<<"\n";
	double rear_left_car = findOtherCarDistance(car, carList, static_cast<lane>(lane_left), backDir);
  	cout<<"rear_left_car: "<<rear_left_car<<"\n";
	double front_right_car = findOtherCarDistance(car, carList, static_cast<lane>(lane_right), frontDir);
  	cout<<"front_right_car: "<<front_right_car<<"\n";
	double rear_right_car = findOtherCarDistance(car, carList, static_cast<lane>(lane_right), backDir);
  	cout<<"rear_right_car: "<<rear_right_car<<"\n";
	
	
	double left_cost = find_cost(front_left_car, rear_left_car, static_cast<lane>(lane_left));
	double right_cost = find_cost(front_right_car, rear_right_car, static_cast<lane>(lane_right));
	
	cout<<"left_cost: "<<left_cost<<"\n";
  	cout<<"right_cost: "<<right_cost<<"\n";
  
    if(front_car < 30)
	{
		car.collision_chance = true;
      	cout<<"Planner:car.collision_chance: " << car.collision_chance << "\n";
	}
  	else
    {
      	car.collision_chance = false;
    }
  
	if((left_cost < keepLane_cost) && (left_cost < right_cost))
	{
		return Movement::LANE_CHANGE_LEFT;
	}
	else if((right_cost < keepLane_cost) && (right_cost < left_cost))
	{
		return Movement::LANE_CHANGE_RIGHT;
	}
	return Movement::KEEP_LANE;
}
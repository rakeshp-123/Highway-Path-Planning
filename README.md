# Highway-Path-Planning-Project

Self-Driving Car Engineer Nanodegree Program(Term 3)
   
### Introduction

This project contains a intelligent path planner used for highway driving. Using this planner, a Self-Driving vehicle can move through the highway traffic smoothly with having any collision with other vehicles. The self-driving car can also change lanes if it senses any obstacle and then moves back to previous lane after overtaking it.

# Project Goals

### The following criteria have been met
- The car is able to drive at least 4.32 miles without incident.
- The car doesn't drive faster than the speed limit. Also the car isn't driving much slower than speed limit unless obstructed by traffic.
- Max Acceleration and Jerk are not exceeded. The car does not exceed a total acceleration of 10 m/s^2 and a jerk of 10 m/s^3.
- Car does not have collisions. The car must not come into contact with any of the other cars on the road.
- The car stays in its lane, except for the time between changing lanes. The car doesn't spend more than a 3 second length out side the lane lanes during changing lanes, and every other time the car stays inside one of the 3 lanes on the right hand side of the road.
- The car is able to change lanes. The car is able to smoothly change lanes when it makes sense to do so, such as when behind a slower moving car and an adjacent lane is clear of other traffic.

# Project Reflection

 The implementation of this path planner has been performed in 2 separate steps:
- Prediction & Behaviour Planning
- Trajetory Generation

At the begining the vehicle is given certain amount of acceleation(.224) to start moving. At each cycle the surrounding vehicle state data are retrieved and stored for the prediction and behaviour planning step. 
(The code lines from 265-293 in main.cpp corresponds to the mentioned operations)

### Prediction & Behaviour Planning

It first finds out vehicles which:
- is in front in a proximity which may lead to a collision. A distance below 30 meters is considered as unsafe and
prone to collision. 
- is in the left lane front side which may cause lane change unsafe.
- is in the left lane rear side which may cause lane change unsafe.
- is in the right lane front side which may cause lane change unsafe.
- is in the right lane rear side which may cause lane change unsafe.
(The code lines from 82 - 103 in planner.cpp corresponds to the functionalities mentioned here)

Once we find out the distance from vehicles which may create collision during maneuver, we use a cost function to find minimum cost maneuver for finding the
best possible next state. The cost function caters the following:
- Penalize if other vehicle are in dangerous proximity(front side 30 meters and rear 15 meters).
- Rewards if the vehicle keep moving in middle lane.
- penalize to make sure we do not do lane change very often.
(The code lines 8 - 78 in planner.cpp has the features mentioned here)

Once a best movement maneuver direction is found, it is then checked if there is any dangerous proximity to front vehicle. If there is not any such situation and 
the vehicle is already in middle lane, the planner ignores the maneuver. this may happen due to difference upto merely decimal place among the forward, left and right movement cost.
And if there is no lane change predicted from previous, the velocity is incremented or decremented based on dangerous proximity of vehicle in front(within 30 meter).
(The code lines from 301 - 332 in main.cpp)

### Trajectory Generation
The trajectory is calculated based on car velocity, car localized position and past waypoints.

At the beginning, when there is no previous path point available, one extra path point is generated using backtracking calculation along with current car position.
Otherwise, two previous path points are used to create a line of vehicle movement and orientation is calculated(lines 339 - 370 in main.cpp). After that three
faraway points are taken from current frenet s position. The corresponding X,Y co-ordinates are found using getXY() function using map data(Lines 371- 374 in main.cpp).

These data are used to generate jerk minimizing trajectory using spline functions to ensure more continuity in waypoint. In order to spline function working properly, the X,Y co-ordinates are transformed from 
vehicle co-ordinate system to cartesian co-ordinate system. Once the interpolated points are found in between current location to farway location, the points
are transformed back to vehicle co-ordinate system and used for provind to simulator. The velocity here decides the distance between points and thus ensures the speed in controlled.
(lines 410 - 434 in main.cpp)

 



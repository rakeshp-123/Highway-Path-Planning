#ifndef COMMON_H
#define COMMON_H

#include<iostream>

using namespace std;

enum class lane:int
{
	LEFT,
	CENTER,
	RIGHT,
	END
};

enum class Movement:int
{
	LANE_CHANGE_LEFT,
	LANE_CHANGE_RIGHT,
	KEEP_LANE
};

#endif

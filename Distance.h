#pragma once
#include <cmath>
double Distance(double latitude1, double longtitude1,
	double latitude2, double longtitude2)
{
	latitude1 *= (3.1415926535 / 180);
	latitude2 *= (3.1415926535 / 180);
	longtitude1 *= (3.1415926535 / 180);
	longtitude2 *= (3.1415926535 / 180);
	return acos(sin(latitude1) * sin(latitude2) +
		   cos(latitude1) * cos(latitude2) *
		   cos(abs(longtitude1 - longtitude2))) *
		   6371000;
}
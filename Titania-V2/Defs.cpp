#include "Defs.h"
#include <TL-Engine.h>	// TL-Engine include file and namespace
#include <iostream>
using namespace tle;

//COLLISION DETECTION
bool sphere2sphere( IModel* Ship, IModel* Object, float shipRad, float objectRad) //Calculates distance between two spheres and if they have collided
{
	int s1xPos = Ship->GetLocalX();	
	int s1yPos = Ship->GetLocalY();
	int s1zPos = Ship->GetLocalZ();

	int s2xPos = Object->GetLocalX();
	int s2yPos = Object->GetLocalY();
	int s2zPos = Object->GetLocalZ();

	float distX = s2xPos - s1xPos;
	float distZ = s2zPos - s1zPos;
	float distY = s2yPos - s1yPos;
	float distance = sqrt(distX * distX + distZ * distZ + distY * distY);

	return (distance < (shipRad + objectRad));
}

// Return a random number in the range between rangeMin and rangeMax inclusive
// range_min <= random number <= range_max
float random(int rangeMin, int rangeMax)
{
	float result = (float)rand() / (float)(RAND_MAX + 1);
	result *= (float)(rangeMax - rangeMin);
	result += rangeMin;

	return result;
}



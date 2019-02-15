#include "Defs.h"
#include <iostream>
//COLLISION DETECTION
bool sphere2sphere(float s1xPos, float s1zPos, float s1rad, float s2xPos, float s2zPos, float s2rad) //Calculates distance between two spheres and if they have collided
{
	float distX = s2xPos - s1xPos;
	float distZ = s2zPos - s1zPos;
	float distance = sqrt(distX * distX + distZ * distZ);

	return (distance < (s1rad + s2rad));
}


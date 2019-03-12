#pragma once
#include <TL-Engine.h>	// TL-Engine include file and namespace
using namespace tle;
enum eCameraPos { behind, topDown };
bool sphere2sphere(IModel* Ship, IModel* Object, float shipRad, float objectRad); //collision function for any sphere on sphere collisions
float random(int rangeMin, int rangeMax);
#pragma once
#include <TL-Engine.h>	// TL-Engine include file and namespace
#include <SFML/Audio.hpp>
using namespace tle;

enum eCameraPos { behind, topDown };
enum PowerUpState { None, Speed, Shield };
bool sphere2sphere(IModel* Ship, IModel* Object, float shipRad, float objectRad); //collision function for any sphere on sphere collisions
float random(int rangeMin, int rangeMax);


const float PLAYERSHIPRADIUS = 3.0f;
const float PLACEMENTPOWERUPRADIUS = 2.0f;
const float ENEMYSHIPRADIUS = 8.0f;
const float BULLETRADIUS = 8.0f;

struct BulletData
{
	IModel* model;
	float xVel, yVel, zVel;
	float life = 3.0;
};
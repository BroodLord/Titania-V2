#pragma once
#include <TL-Engine.h>
#include <SFML/Audio.hpp>
#include <deque>
using namespace tle;


struct BulletData
{
	IModel* model;
	float xVel, yVel, zVel;
	float life = 3.0;
};

const int maxBullets = 30;


void Shooting(bool moveCamTop, bool moveCamBehind, float frameTime, I3DEngine*& myEngine, IModel* playerShip, int& numBullets, IMesh*& bulletMesh, float playerShipSpeed, sf::Sound& shootingSound, deque <BulletData>& bullets);
#pragma once
#include <TL-Engine.h>
#include <SFML/Audio.hpp>
using namespace tle;

struct BulletData
{
	IModel* model;
	float xVel, yVel, zVel;
	float life;
};

void Shooting(bool moveCamTop, bool moveCamBehind, float frameTime, I3DEngine*& myEngine, IModel* playerShip, int& numBullets, IMesh*& bulletMesh, float playerShipSpeed, sf::Sound& shootingSound);
#pragma once
#include <TL-Engine.h>
#include <SFML/Audio.hpp>
#include <deque>
#include "Defs.h"
using namespace tle;

const int maxBullets = 12;

void Shooting(bool moveCamTop, bool moveCamBehind, float frameTime, I3DEngine*& myEngine, IModel* playerShip, int& numBullets, IMesh*& bulletMesh, float playerShipSpeed, sf::Sound& shootingSound, deque <CBulletData>& bullets);
//void EnemyShooting(bool moveCamTop, bool moveCamBehind, float frameTime, I3DEngine*& myEngine, IModel* enemyShip, IMesh*& bulletMesh);
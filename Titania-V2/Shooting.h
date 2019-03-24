#pragma once
#include <TL-Engine.h>
#include <SFML/Audio.hpp>
#include <deque>
#include "Defs.h"
#include "Spawn.h"
using namespace tle;


const int maxBullets = 12;

void Shooting(bool moveCamTop, bool moveCamBehind, float frameTime, I3DEngine*& myEngine, IModel* playerShip, IMesh*& bulletMesh, float playerShipSpeed, sf::Sound& shootingSound);
void EnemyShooting(bool moveCamTop, bool moveCamBehind, float frameTime, I3DEngine*& myEngine, deque <unique_ptr <CShips>>& ship, IMesh*& bulletMesh);
void MoveBullet(float frameTime, IMesh*& bulletMesh);
void FiveShot(bool moveCamTop, bool moveCamBehind, float frameTime, I3DEngine*& myEngine, deque <unique_ptr <CShips>>& ship, IMesh*& bulletMesh);
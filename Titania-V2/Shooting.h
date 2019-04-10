#pragma once
#include <TL-Engine.h>
#include <SFML/Audio.hpp>
#include <deque>
#include "Defs.h"
#include "Spawn.h"
using namespace tle;

const int maxBullets = 20;
const int maxBulletsP2 = 20;

void Shooting(bool moveCamTop, bool moveCamBehind, float frameTime, I3DEngine*& myEngine, IModel* playerShip, IMesh*& bulletMesh, float playerShipSpeed, sf::Sound& shootingSound);
void Shooting2(bool moveCamTop, bool moveCamBehind, float frameTime, I3DEngine*& myEngine, IModel* playerShip2, IMesh*& bulletMesh, float playerShipSpeed, sf::Sound& shootingSound);
void EnemyShooting(bool moveCamTop, bool moveCamBehind, float frameTime, I3DEngine*& myEngine, deque <unique_ptr <CShips>>& ship, IMesh*& bulletMesh);
void MoveBullet(float frameTime, IMesh*& bulletMesh, IModel* player);
void FiveShot(bool moveCamTop, bool moveCamBehind, float frameTime, I3DEngine*& myEngine, deque <unique_ptr <CShips>>& ship, IMesh*& bulletMesh);
void OrbitShot(bool moveCamTop, bool moveCamBehind, float frameTime, I3DEngine*& myEngine, deque <unique_ptr <CShips>>& ship, IMesh*& bulletMesh);
void BeamShot(bool moveCamTop, bool moveCamBehind, float frameTime, I3DEngine*& myEngine, deque <unique_ptr <CShips>>& ship, IMesh*& bulletMesh);
#pragma once
#include <TL-Engine.h>
#include <SFML/Audio.hpp>
#include <deque>
#include "Defs.h"
#include "Spawn.h"
using namespace tle;

const int maxBullets = 20;
const int maxBulletsP2 = 20;

void Shooting(I3DEngine*& myEngine, IModel* playerShip, IMesh*& bulletMesh,
	float playerShipSpeed, sf::Sound& shootingSound, EKeyCode shootKey, float& playerFireRate, bool tripleShot);
void EnemyShooting(I3DEngine*& myEngine, deque <unique_ptr <CShips>>& ship, IMesh*& bulletMesh);
void MoveBullet(IMesh*& bulletMesh, IModel* player);
void FiveShot(I3DEngine*& myEngine, deque <unique_ptr <CShips>>& ship, IMesh*& bulletMesh);
void OrbitShot(I3DEngine*& myEngine, deque <unique_ptr <CShips>>& ship, IMesh*& bulletMesh);
void BeamShot(I3DEngine*& myEngine, deque <unique_ptr <CShips>>& ship, IMesh*& bulletMesh);
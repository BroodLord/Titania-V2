#pragma once
#include <TL-Engine.h>
#include <deque>
#include "Defs.h"
using namespace tle;

enum EnemyShipState { Spawning, Active, Deactivated };

struct LightEnemyShip
{
	IModel* lightShip[50];
	int firingSpeed = 5.0f;
	int Health = 2;
};
struct MediumEnemyShip
{
	IModel* MediumShip[30];
	int firingSpeed = 3.0f;
	int Health = 4;
};
struct HeavyEnemyShip
{
	IModel* HeavyShip[20];
	int firingSpeed = 1.5f;
	int Health = 6;
};



void CreateEnemies(I3DEngine*& myEngine, IMesh* lightMesh, IMesh* MediumMesh, IMesh* HeavyMesh);
void SpawnEnemies(int numBullets, deque <CBulletData> bullets, bool moveCamTop, bool moveCamBehind, float frameTime);
#include "Spawn.h"
#include "Defs.h"

static int lightCounter = 0;
static int MedCounter = 0;
static int HeavyCounter = 0;

HeavyEnemyShip heavyShip;
MediumEnemyShip mediumShip;
LightEnemyShip lightShip;

EnemyShipState currentEnemyShipState;


int spawnArray[30] = { 1,3,2,1,2,3,3,1,2,1,3,2,2,1,3,2,1,1,3,2,3,2,1,2,3,1,2,3,2,1, };

int spawnCounter = 0;

float closeCounter = 2, farCounter = 2.8, MidCounter = 2.4;


void CreateEnemies(I3DEngine*& myEngine, IMesh* lightMesh, IMesh* MediumMesh, IMesh* HeavyMesh)
{
	currentEnemyShipState = Active;
	for (int i = 0; i < 20; i++)
	{
		heavyShip.HeavyShip[i] = lightMesh->CreateModel(120.0f, -30.0f, 700.0f);
		heavyShip.HeavyShip[i]->Scale(2);
		heavyShip.HeavyShip[i]->RotateY(180);
	}
	for (int i = 0; i < 30; i++)
	{
		mediumShip.MediumShip[i] = MediumMesh->CreateModel(-120.0f, -30.0f, 700.0f);
		mediumShip.MediumShip[i]->Scale(1.5);
		mediumShip.MediumShip[i]->RotateY(180);

	}
	for (int i = 0; i < 50; i++)
	{
		lightShip.lightShip[i] = HeavyMesh->CreateModel(120.0f, -30.0f, 700.0f);
		lightShip.lightShip[i]->Scale(1.5);
		lightShip.lightShip[i]->RotateY(180);
	}
}

void SpawnEnemies(int numBullets, deque <BulletData> bullets, bool moveCamTop, bool moveCamBehind, float frameTime)
{
	if (currentEnemyShipState == Active)
	{
		for (int i = 0; i < 50; i++)
		{
			for (int j = 0; j < numBullets; j++)
			{
				float mama = bullets[j].model->GetLocalX();

				if (sphere2sphere(lightShip.lightShip[i], bullets[j].model, PLAYERSHIPRADIUS, BULLETRADIUS))
				{
					currentEnemyShipState = Deactivated;

				}
				if (currentEnemyShipState == Deactivated)
				{
					lightShip.lightShip[i]->MoveLocalZ(-1000.0f);
					currentEnemyShipState = Active;
				}
			}
		}
		for (int i = 0; i < 30; i++)
		{
			for (int j = 0; j < numBullets; j++)
			{
				if (sphere2sphere(mediumShip.MediumShip[i], bullets[j].model, PLAYERSHIPRADIUS, BULLETRADIUS))
				{
					currentEnemyShipState = Deactivated;
				}
				if (currentEnemyShipState == Deactivated)
				{
					mediumShip.MediumShip[i]->MoveLocalZ(-1000.0f);
					currentEnemyShipState = Active;
				}
			}
		}
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < numBullets; j++)
			{
				if (sphere2sphere(heavyShip.HeavyShip[i], bullets[j].model, PLAYERSHIPRADIUS, BULLETRADIUS))
				{
					currentEnemyShipState = Deactivated;
				}
				if (currentEnemyShipState == Deactivated)
				{
					heavyShip.HeavyShip[i]->MoveLocalZ(-1000.0f);
					currentEnemyShipState = Active;
				}
			}
		}
	}
	if (moveCamTop != true && moveCamBehind != true)
	{
		if (spawnArray[spawnCounter] == 1)
		{
			closeCounter -= frameTime;
			if (closeCounter >= 0)
			{
				lightShip.lightShip[lightCounter]->MoveX(-50 * frameTime);
			}

			MidCounter -= frameTime;
			if (MidCounter >= 0)
			{
				heavyShip.HeavyShip[HeavyCounter]->MoveX(-50 * frameTime);
			}
			if (closeCounter >= 0)
			{
				mediumShip.MediumShip[MedCounter]->MoveX(50 * frameTime);

			}
			if (closeCounter < -1 && MidCounter < -1)
			{
				if (MedCounter != 29)
				{
					MedCounter++;
				}
				if (HeavyCounter != 19)
				{
					HeavyCounter++;
				}
				if (lightCounter != 49)
				{
					lightCounter++;
				}
				closeCounter = 2;
				MidCounter = 2.4;
			}
		}
	}
}
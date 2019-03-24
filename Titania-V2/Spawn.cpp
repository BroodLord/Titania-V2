#include "Spawn.h"
#include "Defs.h"
#include "Shooting.h"

static int lightCounter = 0;
static int MedCounter = 0;
static int HeavyCounter = 0;

//HeavyEnemyShip heavyShip;
//MediumEnemyShip mediumShip;
//LightEnemyShip lightShip;

EnemyShipState currentEnemyShipState;

extern deque <CBulletData> bullets;
extern deque <CBulletData> lightBullets;
extern deque <CBulletData>  mediumBullets;
extern deque <CBulletData> heavyBullets;

extern deque <unique_ptr <CShips>> HeavyShipList;
extern deque <unique_ptr <CShips>> MediumShipList;
extern deque <unique_ptr <CShips>> LightShipList;
extern deque <unique_ptr <CShips>> SpawnedShipList;

int spawnArray[30] = { 1,3,2,1,2,3,3,1,2,1,3,2,2,1,3,2,1,1,3,2,3,2,1,2,3,1,2,3,2,1, };

int spawnCounter = 0;

float closeCounter = 2, farCounter = 2.8, MidCounter = 2.4;
extern float lightFireRate;
extern float mediumFireRate;
extern float heavyFireRate;

extern int gPlayerScore;

void CreateEnemies(I3DEngine*& myEngine)
{
	currentEnemyShipState = Active;
	for (int i = 0; i < 20; i++)
	{
		unique_ptr <CHeavyEnemyShip> heavyTemp(new CHeavyEnemyShip(myEngine));

		heavyTemp->mShipModel = heavyTemp->mShipMesh->CreateModel(120.0f, -30.0f, 700.0f);
		heavyTemp->mShipModel->Scale(2);
		heavyTemp->mShipModel->RotateY(180);
		HeavyShipList.push_back(move(heavyTemp));
	}
	for (int i = 0; i < 30; i++)
	{
		unique_ptr <CMediumEnemyShip> mediumTemp(new CMediumEnemyShip(myEngine));

		mediumTemp->mShipModel = mediumTemp->mShipMesh->CreateModel(-120.0f, -30.0f, 700.0f);
		mediumTemp->mShipModel->Scale(1.5f);
		mediumTemp->mShipModel->RotateY(180);
		MediumShipList.push_back(move(mediumTemp));
	}
	for (int i = 0; i < 50; i++)
	{
		unique_ptr <CLightEnemyShip> lightTemp(new CLightEnemyShip(myEngine));

		lightTemp->mShipModel = lightTemp->mShipMesh->CreateModel(120.0f, -30.0f, 700.0f);
		lightTemp->mShipModel->Scale(1.5f);
		lightTemp->mShipModel->RotateY(180);
		LightShipList.push_back(move(lightTemp));
	}
}

void SpawnEnemies(int& numBullets, deque <CBulletData>& bullets, bool moveCamTop, bool moveCamBehind, float frameTime, IMesh*& bulletMesh, I3DEngine*& myEngine)
{



	//for (auto it = LightShipList.begin(); it != LightShipList.end(); it++)
	//{
	//	for (int j = 0; j < numBullets; j++)
	//	{
	//		float mama = bullets[j].model->GetLocalX();

	//		if (sphere2sphere((*it)->mShipModel, bullets[j].model, PLAYERSHIPRADIUS, BULLETRADIUS))
	//		{
	//			currentEnemyShipState = Deactivated;
	//			SpawnPowerUp(random(0, 6), (*it)->mShipModel, myEngine);
	//		}
	//		if (currentEnemyShipState == Deactivated)
	//		{
	//			(*it)->mShipModel->MoveLocalZ(-1000.0f);
	//			currentEnemyShipState = Active;
	//		}
	//	}
	//}

	/*if (currentEnemyShipState == Active)
	{*/
	for (auto it = LightShipList.begin(); it != LightShipList.end(); it++)
	{
		for (int j = 0; j < numBullets; j++)
		{
			float mama = bullets[j].model->GetLocalX();

			if (sphere2sphere((*it)->mShipModel, bullets[j].model, ENEMYSHIPRADIUS, BULLETRADIUS))
			{
				bulletMesh->RemoveModel(bullets[j].model);
				Erase(bullets, bullets[j].model);
				(*it)->mHealth = (*it)->mHealth - 1;
				if ((*it)->mHealth <= 0)
				{
					(*it)->mDead = Deactivated;
					SpawnPowerUp(random(0, 6), (*it)->mShipModel, myEngine);
				}

				if ((*it)->mDead == Deactivated)
				{
					(*it)->mShipModel->SetPosition(120.0f, -30.0f, 700.0f);
					(*it)->mDead = Active;
					(*it)->mHealth = 2;
					gPlayerScore = gPlayerScore + (*it)->mScore;

				}
				numBullets--;
				break;
			}
		}
	}
	for (auto it = MediumShipList.begin(); it != MediumShipList.end(); it++)
	{
		for (int j = 0; j < numBullets; j++)
		{
			if (sphere2sphere((*it)->mShipModel, bullets[j].model, ENEMYSHIPRADIUS, BULLETRADIUS))
			{
				bulletMesh->RemoveModel(bullets[j].model);
				Erase(bullets, bullets[j].model);
				(*it)->mHealth = (*it)->mHealth - 1;
				if ((*it)->mHealth <= 0)
				{
					(*it)->mDead = Deactivated;
					SpawnPowerUp(random(0, 6), (*it)->mShipModel, myEngine);
				}
				if ((*it)->mDead == Deactivated)
				{
					(*it)->mShipModel->SetPosition(-120.0f, -30.0f, 700.0f);
					(*it)->mDead = Active;
					(*it)->mHealth = 6;
					gPlayerScore = gPlayerScore + (*it)->mScore;
				}
				numBullets--;
				break;
			}
		}
	}
	for (auto it = HeavyShipList.begin(); it != HeavyShipList.end(); it++)
	{
		for (int j = 0; j < numBullets; j++)
		{
			if (sphere2sphere((*it)->mShipModel, bullets[j].model, ENEMYSHIPRADIUS, BULLETRADIUS))
			{
				bulletMesh->RemoveModel(bullets[j].model);
				Erase(bullets, bullets[j].model);
				(*it)->mHealth = (*it)->mHealth - 1;
				if ((*it)->mHealth <= 0)
				{
					(*it)->mDead = Deactivated;
					SpawnPowerUp(random(0, 6), (*it)->mShipModel, myEngine);
				}

				if ((*it)->mDead == Deactivated)
				{
					(*it)->mShipModel->SetPosition(120.0f, -30.0f, 700.0f);
					(*it)->mDead = Active;
					(*it)->mHealth = 10;
					gPlayerScore = gPlayerScore + (*it)->mScore;
				}
				numBullets--;
				break;
			}
		}
	}
	//}

}

void ActivateEnemies(bool moveCamTop, bool moveCamBehind, float frameTime, I3DEngine*& myEngine, IMesh*& bulletMesh)
{
	if (moveCamTop != true && moveCamBehind != true)
	{
		if (LightShipList.front()->mShipModel->GetX() > 20.0f)
		{
			
			LightShipList.front()->mShipModel->MoveX(-50.0f * frameTime);
		}
		else
		{
			if (lightFireRate < 0.0f)
			{
				LightShipList.front()->mShipModel->SetX(20.0f);
				OrbitShot(moveCamTop, moveCamBehind, frameTime, myEngine, LightShipList, bulletMesh);
				lightFireRate = LightShipList.front()->mFireRate;
			}
		}

		if (HeavyShipList.front()->mShipModel->GetX() > 0.0f)
		{
			
			HeavyShipList.front()->mShipModel->MoveX(-50.0f * frameTime);
		}
		else
		{
			if (heavyFireRate < 0.0f)
			{
				EnemyShooting(moveCamTop, moveCamBehind, frameTime, myEngine, HeavyShipList, bulletMesh);
				HeavyShipList.front()->mShipModel->SetX(0.0f);
				heavyFireRate = HeavyShipList.front()->mFireRate;
			}
		}

		if (MediumShipList.front()->mShipModel->GetX() < -20.0f)
		{			
			MediumShipList.front()->mShipModel->MoveX(50.0f * frameTime);
		}
		else
		{
			if (mediumFireRate < 0.0f)
			{
				FiveShot(moveCamTop, moveCamBehind, frameTime, myEngine, MediumShipList, bulletMesh);
				MediumShipList.front()->mShipModel->SetX(-20.0f);
				mediumFireRate = MediumShipList.front()->mFireRate;
			}
			
		}
		MoveBullet(frameTime, bulletMesh);
	}
}

//bool FindActive(deque <unique_ptr<CShips>>& current, EnemyShipState& ship)
//{
//	auto p = current.begin(); // set p to the beginning of the loop
//	while (p != current.end()) // while not at the end of the loop
//	{
//		if ((*p)->mDead == Deactivated)
//		{
//			return true;
//		}
//		p++;
//	}
//	return false;
//}

void Erase(deque <CBulletData>& bullets, IModel* newBullet)
{
	auto p = bullets.begin(); // set p to the beginning of the loop
	while (p != bullets.end()) // while not at the end of the loop
	{
		if ((*p).model == newBullet)
		{
			bullets.erase(p);
			break;
		}
		p++;

	}
}
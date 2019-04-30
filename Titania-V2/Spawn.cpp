#include "Spawn.h"
#include "Defs.h"
#include "Shooting.h"

extern float GLOBAL_Y;
static int lightCounter = 0;
static int MedCounter = 0;
static int HeavyCounter = 0;

const float ENEMY_X = 120.0f;
const float ENEMY_Y = GLOBAL_Y;
const float ENEMY_Z = 710.0f;

const float LEFT_LIST_X = 120.0f;
const float LEFT_LIST_Y = GLOBAL_Y;
const float LEFT_LIST_Z = 710.0f;

const float RIGHT_LIST_X = -120.0f;
const float RIGHT_LIST_Y = GLOBAL_Y;
const float RIGHT_LIST_Z = 710.0f;

const float MIDDLE_LIST_X = 0.0f;
const float MIDDLE_LIST_Y = -10.0f;
const float MIDDLE_LIST_Z = 850.0f;

EnemyShipState currentEnemyShipState;

extern deque <CBulletData> bullets;
extern deque <CBulletData> lightBullets;
extern deque <CBulletData>  mediumBullets;
extern deque <CBulletData> heavyBullets;
extern deque <CBulletData> BossBullets;

extern deque <unique_ptr <CShips>> BossShipList;
extern deque <unique_ptr <CShips>> HeavyShipList;
extern deque <unique_ptr <CShips>> MediumShipList;
extern deque <unique_ptr <CShips>> LightShipList;
extern deque <unique_ptr <CShips>> SpawnedShipList;

extern deque <unique_ptr <CShips>> RightList;
extern deque <unique_ptr <CShips>> MiddleList;
extern deque <unique_ptr <CShips>> LeftList;
extern deque <unique_ptr <CShips>> DeadList;
bool moveLeft = true;

int spawnArray[30] = { 1,3,2,1,2,3,3,1,2,1,3,2,2,1,3,2,1,1,3,2,3,2,1,2,3,1,2,3,2,1, };
int spawnCounter = 0;

float closeCounter = 2, farCounter = 2.8, MidCounter = 2.4;
extern float lightFireRate;
extern float mediumFireRate;
extern float heavyFireRate;
extern float bossFireRate;
extern bool moveCamTop;
extern bool moveCamBehind;
extern float frameTime;
extern int gPlayerScore;

void CreateEnemies(I3DEngine*& myEngine)
{
	currentEnemyShipState = Active;
	for (int i = 0; i < 30; i++)
	{
		unique_ptr <CHeavyEnemyShip> heavyTemp(new CHeavyEnemyShip(myEngine));

		heavyTemp->mShipModel = heavyTemp->mShipMesh->CreateModel(ENEMY_X, ENEMY_Y, ENEMY_Z);
		heavyTemp->mShipModel->Scale(2);
		heavyTemp->mShipModel->RotateY(180);
		HeavyShipList.push_back(move(heavyTemp));
	}
	for (int i = 0; i < 30; i++)
	{
		unique_ptr <CMediumEnemyShip> mediumTemp(new CMediumEnemyShip(myEngine));

		mediumTemp->mShipModel = mediumTemp->mShipMesh->CreateModel(ENEMY_X, ENEMY_Y, ENEMY_Z);
		mediumTemp->mShipModel->Scale(1.5f);
		mediumTemp->mShipModel->RotateY(180);
		MediumShipList.push_back(move(mediumTemp));
	}
	for (int i = 0; i < 30; i++)
	{
		unique_ptr <CLightEnemyShip> lightTemp(new CLightEnemyShip(myEngine));

		lightTemp->mShipModel = lightTemp->mShipMesh->CreateModel(ENEMY_X, ENEMY_Y, ENEMY_Z);
		lightTemp->mShipModel->Scale(1.5f);
		lightTemp->mShipModel->RotateY(180);
		LightShipList.push_back(move(lightTemp));
	}
	
		unique_ptr <CBossEnemyShip> bossTemp(new CBossEnemyShip(myEngine));
		bossTemp->mShipModel = bossTemp->mShipMesh->CreateModel(0.0f, 30.0f, 690);
		bossTemp->mShipModel->Scale(5.0f);
		bossTemp->mShipModel->RotateY(180.0f);
		BossShipList.push_back(move(bossTemp));


	int i = random(1, 4);
	int j = random(1, 4);
	int k = random(1, 4);

	RandomEnemies(i, j, k);
}

void SpawnEnemies(int& numBullets, deque <CBulletData>& bullets, IMesh*& bulletMesh, I3DEngine*& myEngine)
{

	int l = random(1, 4);
	int m = random(1, 4);
	int n = random(1, 4);

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
	if (!LeftList.empty())
	{
		for (int j = 0; j < numBullets; j++)
		{
			float mama = bullets[j].model->GetLocalX();

			if (sphere2sphere(LeftList.front()->mShipModel, bullets[j].model, LeftList.front()->ShipRadius, BULLETRADIUS))
			{
				bulletMesh->RemoveModel(bullets[j].model);
				Erase(bullets, bullets[j].model);
				LeftList.front()->mHealth = LeftList.front()->mHealth - 1;
				if (LeftList.front()->mHealth <= 0)
				{
					LeftList.front()->mDead = Deactivated;
					SpawnPowerUp(random(0, 6), LeftList.front()->mShipModel, myEngine);
				}

				if (LeftList.front()->mDead == Deactivated)
				{
					LeftList.front()->mShipModel->SetPosition(120.0f, GLOBAL_Y, 700.0f);
					//(*it)->mDead = Active;
					//(*it)->mHealth = 2;
					gPlayerScore = gPlayerScore + LeftList.front()->mScore;
					DeadList.push_back(move(LeftList.front()));
					LeftList.pop_front();
					RandomEnemies(l, m, n);
				}
				numBullets--;
				break;
			}
		}
	}

	if (!RightList.empty())
	{
			for (int j = 0; j < numBullets; j++)
			{
				if (sphere2sphere(RightList.front()->mShipModel, bullets[j].model, RightList.front()->ShipRadius, BULLETRADIUS))
				{
					bulletMesh->RemoveModel(bullets[j].model);
					Erase(bullets, bullets[j].model);
					RightList.front()->mHealth = RightList.front()->mHealth - 1;
					if (RightList.front()->mHealth <= 0)
					{
						RightList.front()->mDead = Deactivated;
						SpawnPowerUp(random(0, 6), RightList.front()->mShipModel, myEngine);
					}
					if (RightList.front()->mDead == Deactivated)
					{
						RightList.front()->mShipModel->SetPosition(120.0f, GLOBAL_Y, 700.0f);
						//(*it)->mDead = Active;
						//(*it)->mHealth = 6;
						gPlayerScore = gPlayerScore + RightList.front()->mScore;
						DeadList.push_back(move(RightList.front()));
						RightList.pop_front();
						RandomEnemies(l, m, n);
					}
					numBullets--;
					break;
				}
			}
		}

	if (!MiddleList.empty())
	{
			for (int j = 0; j < numBullets; j++)
			{
				if (sphere2sphere(MiddleList.front()->mShipModel, bullets[j].model, MiddleList.front()->ShipRadius, BULLETRADIUS))
				{
					bulletMesh->RemoveModel(bullets[j].model);
           					Erase(bullets, bullets[j].model);
					MiddleList.front()->mHealth = MiddleList.front()->mHealth - 1;
					if (MiddleList.front()->mHealth <= 0)
					{
						MiddleList.front()->mDead = Deactivated;
                    						SpawnPowerUp(random(0, 6), MiddleList.front()->mShipModel, myEngine);
					}

					if (MiddleList.front()->mDead == Deactivated)
					{
						MiddleList.front()->mShipModel->SetPosition(120.0f, GLOBAL_Y, 700.0f);
						//(*it)->mDead = Active;
						//(*it)->mHealth = 10;
						gPlayerScore = gPlayerScore + MiddleList.front()->mScore;
						DeadList.push_back(move(MiddleList.front()));
						MiddleList.pop_front();
						RandomEnemies(l, m, n);
					}
					numBullets--;
					break;
				}
			}
		}
	
	//}

}

void ActivateEnemies(I3DEngine*& myEngine, IMesh*& bulletMesh)
{
	if (!LeftList.empty())
	{
		if (!moveCamBehind && !moveCamTop)
		{
			if (LeftList.front()->mShipModel->GetX() > 20.0f)
			{

				LeftList.front()->mShipModel->MoveX(-50.0f * frameTime);
			}
			else
			{
				if (lightFireRate < 0.0f)
				{
					LeftList.front()->mShipModel->SetX(20.0f);
					LeftList.front()->ShipShooting(myEngine, LeftList, bulletMesh);
					lightFireRate = LeftList.front()->mFireRate;
				}
			}
		}
	}
		if (!MiddleList.empty())
		{



			if (MiddleList.front()->mName != "BossShip")
			{
				if (MiddleList.front()->mShipModel->GetZ() > 710.0f)
				{

					MiddleList.front()->mShipModel->MoveZ(-50.0f * frameTime);
				}
				else if (MiddleList.front()->mShipModel->GetY() > GLOBAL_Y)
				{

					MiddleList.front()->mShipModel->MoveY(-50.0f * frameTime);
				}
				else
				{
					if (heavyFireRate < 0.0f)
					{
						heavyFireRate = MiddleList.front()->mFireRate;
						MiddleList.front()->mShipModel->SetPosition(0.0f, GLOBAL_Y, 710.0f);
						MiddleList.front()->ShipShooting(myEngine, MiddleList, bulletMesh);

					}
				}
			}
			else
			{
				if (MiddleList.front()->mShipModel->GetZ() > 710.0f)
				{

					MiddleList.front()->mShipModel->MoveZ(-50.0f * frameTime);
				}
				else if (MiddleList.front()->mShipModel->GetY() > GLOBAL_Y)
				{

					MiddleList.front()->mShipModel->MoveY(-50.0f * frameTime);
				}
				else if(moveLeft)
				{
					MiddleList.front()->mShipModel->MoveX(40.0f * frameTime);					
					if (MiddleList.front()->mShipModel->GetX() > 30.0f)
					{
						moveLeft = false;
					}					
				}
				else if (!moveLeft)
				{
					MiddleList.front()->mShipModel->MoveX(-40.0f * frameTime);
					if (MiddleList.front()->mShipModel->GetX() < -30.0f)
					{
						moveLeft = true;
					}
				}

				if (heavyFireRate < 0.0f)
				{
					heavyFireRate = MiddleList.front()->mFireRate;
					
					MiddleList.front()->ShipShooting(myEngine, MiddleList, bulletMesh);

				}

			}
		}

		if (!RightList.empty())
		{
			if (RightList.front()->mShipModel->GetX() < -20.0f)
			{
				RightList.front()->mShipModel->MoveX(50.0f * frameTime);
			}
			else
			{
				if (mediumFireRate < 0.0f)
				{
					RightList.front()->mShipModel->SetX(-20.0f);
					RightList.front()->ShipShooting(myEngine, RightList, bulletMesh);
					mediumFireRate = RightList.front()->mFireRate;
				}

			}
		}
		if (RightList.empty() == true && MiddleList.empty() == true && LeftList.empty() == true)
		{

			if (LeftList.empty() && MiddleList.empty() && RightList.empty())
			{
				MiddleList.push_back(move(BossShipList.front()));
			}

		/*	if (BossShipList.front()->mShipModel->GetY() > GLOBAL_Y)
			{
				BossShipList.front()->mShipModel->MoveLocalY(-50.0f * frameTime);
			}
			if (bossFireRate < 0.0f)
			{
				BossShipList.front()->mShipModel->SetY(GLOBAL_Y);
				BossShipList.front()->ShipShooting(myEngine, BossShipList, bulletMesh);
				bossFireRate = BossShipList.front()->mFireRate;
			}*/
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

void RandomEnemies(int& i, int& j, int& k)
{
	while (RightList.empty() || LeftList.empty() || MiddleList.empty())
	{
		if (LightShipList.empty() && MediumShipList.empty() && HeavyShipList.empty() && BossShipList.empty())
		{
			break;
		}
		if (i == 1)
		{
			if (!LightShipList.empty() && RightList.empty())
			{
				LightShipList.front()->mShipModel->SetPosition(RIGHT_LIST_X, RIGHT_LIST_Y, RIGHT_LIST_Z);
				RightList.push_back(move(LightShipList.front()));
				LightShipList.pop_front();
			}
			else
			{
				i = random(1, 4);
			}
		}
		else if (i == 2)
		{
			if (!MediumShipList.empty() && RightList.empty())
			{
				MediumShipList.front()->mShipModel->SetPosition(RIGHT_LIST_X, RIGHT_LIST_Y, RIGHT_LIST_Z);
				RightList.push_back(move(MediumShipList.front()));
				MediumShipList.pop_front();
			}
			else
			{
				i = random(1, 4);
			}
		}
		else if (i == 3)
		{
			if (!HeavyShipList.empty() && RightList.empty())
			{
				HeavyShipList.front()->mShipModel->SetPosition(RIGHT_LIST_X, RIGHT_LIST_Y, RIGHT_LIST_Z);
				RightList.push_back(move(HeavyShipList.front()));
				HeavyShipList.pop_front();
			}
			else
			{
				i = random(1, 4);
			}
		}

		if (j == 1)
		{
			if (!LightShipList.empty() && MiddleList.empty())
			{
				LightShipList.front()->mShipModel->SetPosition(MIDDLE_LIST_X, MIDDLE_LIST_Y, MIDDLE_LIST_Z);
				MiddleList.push_back(move(LightShipList.front()));
				LightShipList.pop_front();
			}
			else
			{
				j = random(1, 4);
			}
		}
		else if (j == 2)
		{
			if (!MediumShipList.empty() && MiddleList.empty())
			{
				MediumShipList.front()->mShipModel->SetPosition(MIDDLE_LIST_X, MIDDLE_LIST_Y, MIDDLE_LIST_Z);
				MiddleList.push_back(move(MediumShipList.front()));
				MediumShipList.pop_front();
			}
			else
			{
				j = random(1, 4);
			}
		}
		else if (j == 3)
		{
			if (!HeavyShipList.empty() && MiddleList.empty())
			{
				HeavyShipList.front()->mShipModel->SetPosition(MIDDLE_LIST_X, MIDDLE_LIST_Y, MIDDLE_LIST_Z);
				MiddleList.push_back(move(HeavyShipList.front()));
				HeavyShipList.pop_front();
			}
			else
			{
				j = random(1, 4);
			}
		}
		
		if (k == 1)
		{
			if (!LightShipList.empty() && LeftList.empty())
			{
				LightShipList.front()->mShipModel->SetPosition(LEFT_LIST_X, LEFT_LIST_Y, LEFT_LIST_Z);
				LeftList.push_back(move(LightShipList.front()));
				LightShipList.pop_front();
			}
			else
			{
				k = random(1, 4);
			}
		}
		else if (k == 2)
		{
			if (!MediumShipList.empty() && LeftList.empty())
			{
				MediumShipList.front()->mShipModel->SetPosition(LEFT_LIST_X, LEFT_LIST_Y, LEFT_LIST_Z);
				LeftList.push_back(move(MediumShipList.front()));
				MediumShipList.pop_front();
			}
			else
			{
				k = random(1, 4);
			}
		}
		else if (k == 3)
		{
			if (!HeavyShipList.empty() && LeftList.empty())
			{
				HeavyShipList.front()->mShipModel->SetPosition(LEFT_LIST_X, LEFT_LIST_Y, LEFT_LIST_Z);
				LeftList.push_back(move(HeavyShipList.front()));
				HeavyShipList.pop_front();
			}
			else
			{
				k = random(1, 4);
			}
		}
		
		

	}
}

void CLightEnemyShip::ShipShooting(I3DEngine*& myEngine, deque <unique_ptr <CShips>>& ship, IMesh*& bulletMesh)
{
	OrbitShot(myEngine, ship, bulletMesh);
}

void CMediumEnemyShip::ShipShooting(I3DEngine*& myEngine, deque <unique_ptr <CShips>>& ship, IMesh*& bulletMesh)
{
	FiveShot(myEngine, ship, bulletMesh);
}

void CHeavyEnemyShip::ShipShooting(I3DEngine*& myEngine, deque <unique_ptr <CShips>>& ship, IMesh*& bulletMesh)
{
	EnemyShooting(myEngine, ship, bulletMesh);
}
void CBossEnemyShip::ShipShooting(I3DEngine*& myEngine, deque <unique_ptr <CShips>>& ship, IMesh*& bulletMesh)
{
	BeamShot(myEngine, ship, bulletMesh);
}
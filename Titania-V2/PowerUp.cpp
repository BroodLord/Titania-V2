#include "PowerUp.h"

float PowerUpTimer = 0.0f;

extern deque <unique_ptr <CPowerUp>> SpeedList;
extern deque <unique_ptr <CPowerUp>> ShieldList;
extern deque <unique_ptr <CPowerUp>> TripleList;
extern deque <unique_ptr <CPowerUp>> CurrentlySpawned;


void SpawnPowerUp(int randNum, IModel*& enemeyShip, I3DEngine*& myEngine)
{
	if (randNum == 1)
	{
		SpeedList.front()->mModel->SetPosition(enemeyShip->GetX(), enemeyShip->GetY(), enemeyShip->GetZ());
		CurrentlySpawned.push_back(move(SpeedList.front()));
		SpeedList.pop_front();
	}
	else if (randNum == 2)
	{
		ShieldList.front()->mModel->SetPosition(enemeyShip->GetX(), enemeyShip->GetY(), enemeyShip->GetZ());
		CurrentlySpawned.push_back(move(ShieldList.front()));
		ShieldList.pop_front();
	}
	else if (randNum == 3)
	{
		TripleList.front()->mModel->SetPosition(enemeyShip->GetX(), enemeyShip->GetY(), enemeyShip->GetZ());
		CurrentlySpawned.push_back(move(TripleList.front()));
		TripleList.pop_front();
	}

}

void CSpeed::Power(I3DEngine*& myEngine, int current)
{
	SpeedPowerUP(myEngine);
	mModel->SetPosition(0.0f, 500.0f, 900.0f);
	//SpeedList.push_back(move(CurrentlySpawned[0]));
}

void CShield::Power(I3DEngine*& myEngine, int current)
{
	ShieldPowerUP(myEngine);
	mModel->SetPosition(0.0f, 500.0f, 900.0f);
	//ShieldList.push_back(move(CurrentlySpawned[0]));
}

void CTriple::Power(I3DEngine*& myEngine, int current)
{
	BulletPowerUP(myEngine);
	mModel->SetPosition(0.0f, 500.0f, 900.0f);
	//CurrentlySpawned[0]->mModel->SetPosition(0.0f, 500.0f, 785.0f);
	//TripleList.push_back(move(CurrentlySpawned[0]));
}
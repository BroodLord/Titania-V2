#pragma once
#include <TL-Engine.h>
#include <deque>
#include "Defs.h"
#include "PowerUp.h"
using namespace tle;

enum EnemyShipState { Spawning, Active, Deactivated };

class CShips
{
public:
	//CShips();
	//~CShips();
	string mName;
	IModel* mShipModel;
	IMesh* mShipMesh;
	int mHealth;
	float mFireRate;
	EnemyShipState mDead = Active;
	int mScore;
	float mBulletRadius;
	float mBulletSize;
	float mBulletHealth;
	float mBulletSpeed;
	virtual void ShipShooting(bool moveCamTop, bool moveCamBehind, float frameTime, I3DEngine*& myEngine, deque <unique_ptr <CShips>>& ship, IMesh*& bulletMesh) = 0;
private:

};

//CShips::CShips()
//{
//}

//CShips::~CShips()
//{
//}

class CLightEnemyShip : public CShips
{
public:
	CLightEnemyShip(I3DEngine*& myEngine)
{
		mName = "LightShip";
	mShipMesh = myEngine->LoadMesh("enemyShip.x");
	mHealth = 4;
	mFireRate = 2.0f;
	mScore = 1;
	mBulletRadius = 1.0f;
	mBulletSize = mBulletRadius * 0.6;
	mBulletHealth = 3.0f;
	mBulletSpeed = 1.0f;

}
	void ShipShooting(bool moveCamTop, bool moveCamBehind, float frameTime, I3DEngine*& myEngine, deque <unique_ptr <CShips>>& ship, IMesh*& bulletMesh);
	//~CLightEnemyShip();

private:

};



//CLightEnemyShip::~CLightEnemyShip()
//{
//}

class CMediumEnemyShip : public CShips
{
public:
	CMediumEnemyShip(I3DEngine*& myEngine)
	{
		mName = "MediumShip";
		mShipMesh = myEngine->LoadMesh("enemyShip1.x");
		mHealth = 6;
		mFireRate = 2.0f;
		mScore = 2;
		mBulletRadius = 1.0f;
		mBulletSize = mBulletRadius * 0.6;
		mBulletHealth = 1.0f;
		mBulletSpeed = 2.0f;
	}
	void ShipShooting(bool moveCamTop, bool moveCamBehind, float frameTime, I3DEngine*& myEngine, deque <unique_ptr <CShips>>& ship, IMesh*& bulletMesh);
	//~CMediumEnemyShip();

private:

};

//CMediumEnemyShip::~CMediumEnemyShip()
//{
//}

class CHeavyEnemyShip : public CShips
{
public:
	CHeavyEnemyShip(I3DEngine*& myEngine)
	{
		mName = "HeavyShip";
		mShipMesh = myEngine->LoadMesh("enemyShip2.x");
		mHealth = 10;
		mFireRate = 4.5f;
		mScore = 4;
		mBulletRadius = 5;
		mBulletSize = mBulletRadius * 0.6;
		mBulletHealth = 5.0f;
		mBulletSpeed = 1.0f;
	}
	void ShipShooting(bool moveCamTop, bool moveCamBehind, float frameTime, I3DEngine*& myEngine, deque <unique_ptr <CShips>>& ship, IMesh*& bulletMesh);
	//~CHeavyEnemyShip();

private:

};

class CBossEnemyShip : public CShips
{
public:
	CBossEnemyShip(I3DEngine*& myEngine)
	{
		mName = "BossShip";
		mShipMesh = myEngine->LoadMesh("Boss.x");
		mHealth = 200;
		mFireRate = 0.5f;
		mScore = 100;
		mBulletRadius = 1.0f;
		mBulletSize = mBulletRadius * 1.0;
		mBulletHealth = 3.0f;
		mBulletSpeed = 2.0f;

	}
	void ShipShooting(bool moveCamTop, bool moveCamBehind, float frameTime, I3DEngine*& myEngine, deque <unique_ptr <CShips>>& ship, IMesh*& bulletMesh);
	//~CLightEnemyShip();

private:

};




//CHeavyEnemyShip::~CHeavyEnemyShip()
//{
//}

//struct LightEnemyShip
//{
//	IModel* lightShip[50];
//	int firingSpeed = 5.0f;
//	int Health = 2;
//};
//struct MediumEnemyShip
//{
//	IModel* MediumShip[30];
//	int firingSpeed = 3.0f;
//	int Health = 4;
//};
//struct HeavyEnemyShip
//{
//	IModel* HeavyShip[20];
//	int firingSpeed = 1.5f;
//	int Health = 6;
//};

void CreateEnemies(I3DEngine*& myEngine);
void SpawnEnemies(int& numBullets, deque <CBulletData>& bullets, bool moveCamTop, bool moveCamBehind, float frameTime, IMesh*& bulletMesh, I3DEngine*& myEngine);
void ActivateEnemies(bool moveCamTop, bool moveCamBehind, float frameTime, I3DEngine*& myEngine, IMesh*& bulletMesh);
//bool FindActive(deque <unique_ptr<CShips>>& current, string& active);
void Erase(deque <CBulletData>& bullets, IModel* newBullet);
void RandomEnemies(int& i, int& j, int& k);
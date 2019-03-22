#pragma once
#include <TL-Engine.h>
#include "Defs.h"
#include "Hud.h"
#include "Spawn.h"
#include <deque>
using namespace tle;


class CPowerUp
{
public:
	//CPowerUp();
	//virtual ~CPowerUp() = 0;
	string mName;
	PowerUpState mPowerType;
	IModel* mModel;
	IMesh* mMesh;
	float mTimer;
	virtual void Power(I3DEngine*& myEngine, int current) = 0;
private:

};

//CPowerUp::CPowerUp()
//{
//}

//CPowerUp::~CPowerUp()
//{
//}

class CSpeed : public CPowerUp
{
public:
	CSpeed(I3DEngine*& myEngine)
	{
		mName = "Speed";
		mPowerType = Speed;
		mTimer = 5.0f;
		mMesh = myEngine->LoadMesh("SpeedPowerUp.x");

	}
	//~CSpeed();
	void Power(I3DEngine*& myEngine, int current);
private:

};



//CSpeed::~CSpeed()
//{
//}

class CShield : public CPowerUp
{
public:
	CShield(I3DEngine*& myEngine)
	{
		mName = "Shield";
		mPowerType = Shield;
		mTimer = 9.0f;
		mMesh = myEngine->LoadMesh("ShieldPowerUp.x");
	}
	//~CShield();
	void Power(I3DEngine*& myEngine, int current);
private:

};



//CShield::~CShield()
//{
//}

class CTriple : public CPowerUp
{
public:
	CTriple(I3DEngine*& myEngine)
	{
	
			mName = "Triple";
			mPowerType = Bullet;
			mTimer = 5.0f;
		mMesh = myEngine->LoadMesh("BulletPowerUp.x");
		
	}
	//~CTriple();
	void Power(I3DEngine*& myEngine, int current);
private:

};



//CTriple::~CTriple()
//{
//}

void SpawnPowerUp(int randNum, IModel*& enemeyShip, I3DEngine*& myEngine);
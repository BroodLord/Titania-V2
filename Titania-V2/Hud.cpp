#include "Hud.h"
using namespace tle;

ISprite* firstHeart;
ISprite* secondHeart;
ISprite* thirdHeart;
ISprite* ScreenCrack1;
ISprite* ScreenCrack2;
ISprite* ScreenCrack3;
ISprite* ScreenCrack4;
ISprite* speedPup;
ISprite* shieldPup;
ISprite* bulletPup;
ISprite* NospeedPup;
ISprite* NoshieldPup;
ISprite* NobulletPup;


const float POWER_UP_COORDS = 150.0f;

void fullHealth(I3DEngine*& myEngine, AmountLives Health)
{
	if (Health == ThreeLives)
	{
		firstHeart = myEngine->CreateSprite("Heart2.png", 140.0f, 25.0f);
		secondHeart = myEngine->CreateSprite("Heart2.png", 170.0f, 25.0f);
		thirdHeart = myEngine->CreateSprite("Heart2.png", 200.0f, 25.0f);		
	}
}

void removeHeart(I3DEngine*& myEngine, AmountLives& Health)
{
	if (Health == ThreeLives)
	{
		myEngine->RemoveSprite(thirdHeart);
		Health = TwoLives;
		ScreenCrack1 = myEngine->CreateSprite("smallGlass.png", -100.0f, -100.0f);
		ScreenCrack3 = myEngine->CreateSprite("smallGlass2.png", 1700.0f, 0.0f);
	}
	else if (Health == TwoLives)
	{
		myEngine->RemoveSprite(secondHeart);
		Health = OneLife;
		
		ScreenCrack2 = myEngine->CreateSprite("Crack3.png", -300.0f, 700.0f);
		ScreenCrack4 = myEngine->CreateSprite("Crack3.png", 500.0f, -900.0f);
		ScreenCrack4 = myEngine->CreateSprite("Crack5.png", 1000.0f, 700.0f);
	}
	else if (Health == OneLife)
	{
		myEngine->RemoveSprite(firstHeart);
		Health = Dead;
	}
}

void SpawnSprites(I3DEngine*& myEngine)
{
	speedPup = myEngine->CreateSprite("Speed2.png", 15.0f, POWER_UP_COORDS, 1.0f);
	shieldPup = myEngine->CreateSprite("Shield2.png", 85.0f, POWER_UP_COORDS, 1.0f);
	NospeedPup = myEngine->CreateSprite("NoSpeed2.png", 15.0f, POWER_UP_COORDS, 0.8f);
	NoshieldPup = myEngine->CreateSprite("NoShield2.png", 85.0f, POWER_UP_COORDS, 0.8f);
	NobulletPup = myEngine->CreateSprite("NoBullets2.png", 155.0f, POWER_UP_COORDS, 0.8f);
	bulletPup = myEngine->CreateSprite("Bullets2.png", 155.0f, POWER_UP_COORDS, 1.0f);
}

void SpeedPowerUP(I3DEngine*& myEngine)
{
	speedPup->SetZ(0.7f);
}

void RemoveSpeedPowerUP(I3DEngine*& myEngine)
{
	speedPup->SetZ(1.0f);
}

void BulletPowerUP(I3DEngine*& myEngine)
{
	bulletPup->SetZ(0.7f);
}

void RemoveBulletPowerUP(I3DEngine*& myEngine)
{
	bulletPup->SetZ(1.0f);
}

void NoPowerUP(I3DEngine*& myEngine)
{
	
}

void ShieldPowerUP(I3DEngine*& myEngine)
{
	shieldPup->SetZ(0.7f);
}

void RemoveShieldPowerUP(I3DEngine*& myEngine)
{
	shieldPup->SetZ(1.0f);
}
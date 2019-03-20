#include "Hud.h"
using namespace tle;

ISprite* firstHeart;
ISprite* secondHeart;
ISprite* thirdHeart;
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
	}
	else if (Health == TwoLives)
	{
		myEngine->RemoveSprite(secondHeart);
		Health = OneLife;
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
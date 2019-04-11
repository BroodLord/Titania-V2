#include "Hud.h"
using namespace tle;

ISprite* firstHeart;
ISprite* secondHeart;
ISprite* thirdHeart;

ISprite* firstHeartP2;
ISprite* secondHeartP2;
ISprite* thirdHeartP2;

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

ISprite* speedPupP2;
ISprite* shieldPupP2;
ISprite* bulletPupP2;
ISprite* NospeedPupP2;
ISprite* NoshieldPupP2;
ISprite* NobulletPupP2;


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

//PLAYER 2

void fullHealthP2(I3DEngine*& myEngine, AmountLives HealthP2)
{
	if (HealthP2 == ThreeLives)
	{
		firstHeartP2 = myEngine->CreateSprite("Heart2.png", 1600.0f, 25.0f);
		secondHeartP2 = myEngine->CreateSprite("Heart2.png", 1630.0f, 25.0f);
		thirdHeartP2 = myEngine->CreateSprite("Heart2.png", 1660.0f, 25.0f);
	}
}

void removeHeartP2(I3DEngine*& myEngine, AmountLives& HealthP2)
{
	if (HealthP2 == ThreeLives)
	{
		myEngine->RemoveSprite(thirdHeartP2);
		HealthP2 = TwoLives;
		ScreenCrack1 = myEngine->CreateSprite("smallGlass.png", -100.0f, -100.0f);
		ScreenCrack3 = myEngine->CreateSprite("smallGlass2.png", 1700.0f, 0.0f);
	}
	else if (HealthP2 == TwoLives)
	{
		myEngine->RemoveSprite(secondHeartP2);
		HealthP2 = OneLife;

		ScreenCrack2 = myEngine->CreateSprite("Crack3.png", -300.0f, 700.0f);
		ScreenCrack4 = myEngine->CreateSprite("Crack3.png", 500.0f, -900.0f);
		ScreenCrack4 = myEngine->CreateSprite("Crack5.png", 1000.0f, 700.0f);
	}
	else if (HealthP2 == OneLife)
	{
		myEngine->RemoveSprite(firstHeartP2);
		HealthP2 = Dead;
	}
}

void SpawnSpritesP2(I3DEngine*& myEngine)
{
	speedPupP2 = myEngine->CreateSprite("Speed2.png", 1615.0f, POWER_UP_COORDS, 1.0f);
	shieldPupP2 = myEngine->CreateSprite("Shield2.png", 1685.0f, POWER_UP_COORDS, 1.0f);
	NospeedPupP2 = myEngine->CreateSprite("NoSpeed2.png", 1615.0f, POWER_UP_COORDS, 0.8f);
	NoshieldPupP2 = myEngine->CreateSprite("NoShield2.png", 1685.0f, POWER_UP_COORDS, 0.8f);
	NobulletPupP2 = myEngine->CreateSprite("NoBullets2.png", 1755.0f, POWER_UP_COORDS, 0.8f);
	bulletPupP2 = myEngine->CreateSprite("Bullets2.png", 1755.0f, POWER_UP_COORDS, 1.0f);
}

void SpeedPowerUPP2(I3DEngine*& myEngine)
{
	speedPupP2->SetZ(1.7f);
}

void RemoveSpeedPowerUPP2(I3DEngine*& myEngine)
{
	speedPupP2->SetZ(1.0f);
}

void BulletPowerUPP2(I3DEngine*& myEngine)
{
	bulletPupP2->SetZ(1.7f);
}

void RemoveBulletPowerUPP2(I3DEngine*& myEngine)
{
	bulletPupP2->SetZ(1.0f);
}

void NoPowerUPP2(I3DEngine*& myEngine)
{

}

void ShieldPowerUPP2(I3DEngine*& myEngine)
{
	shieldPupP2->SetZ(1.7f);
}

void RemoveShieldPowerUPP2(I3DEngine*& myEngine)
{
	shieldPupP2->SetZ(1.0f);
}
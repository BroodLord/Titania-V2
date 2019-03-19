#include "Hud.h"
using namespace tle;

ISprite* firstHeart;
ISprite* secondHeart;
ISprite* thirdHeart;
ISprite* speedPup;
ISprite* shieldPup;
ISprite* NospeedPup;
ISprite* NoshieldPup;

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

void SpeedPowerUP(I3DEngine*& myEngine)
{
	speedPup = myEngine->CreateSprite("Speed2.png", 15.0f, POWER_UP_COORDS, 0.7f);
	shieldPup = myEngine->CreateSprite("test2.png", 85.0f, POWER_UP_COORDS, 0.7f);
}

void RemoveSpeedPowerUP(I3DEngine*& myEngine)
{
	myEngine->RemoveSprite(speedPup);
	myEngine->RemoveSprite(shieldPup);
}

void NoPowerUP(I3DEngine*& myEngine)
{
	NospeedPup = myEngine->CreateSprite("NoSpeed2.png", 15.0f, POWER_UP_COORDS, 0.8f);
	NoshieldPup = myEngine->CreateSprite("NoShield2.png", 85.0f, POWER_UP_COORDS, 0.8f);
}
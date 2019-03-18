#include "Hud.h"
using namespace tle;



ISprite* firstHeart;
ISprite* secondHeart;
ISprite* thirdHeart;
ISprite* speedPup;
ISprite* shieldPup;
ISprite* NospeedPup;
ISprite* NoshieldPup;

void fullHealth(I3DEngine*& myEngine, AmountLives Health)
{
	if (Health == ThreeLives)
	{
		firstHeart = myEngine->CreateSprite("Heart2.png", 105.0f, 15.0f);
		secondHeart = myEngine->CreateSprite("Heart2.png", 135.0f, 15.0f);
		thirdHeart = myEngine->CreateSprite("Heart2.png", 165.0f, 15.0f);
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

void speedPowerUP(I3DEngine*& myEngine)
{	
		speedPup = myEngine->CreateSprite("Speed.png", 15.0f, 600.0f);	
		shieldPup = myEngine->CreateSprite("test.png", 145.0f, 600.0f);
	//	speedPup = myEngine->CreateSprite("Speed.png", 15.0f, 600.0f);
		//shieldPup = myEngine->CreateSprite("test.png", 145.0f, 600.0f);
		//speedPup->s
}

void NoPowerUP(I3DEngine*& myEngine)
{
	NospeedPup = myEngine->CreateSprite("NoSpeed.png", 15.0f, 600.0f, 0.9f);
	NoshieldPup = myEngine->CreateSprite("NoShield.png", 145.0f, 600.0f, 0.9f);
	

		speedPup = myEngine->CreateSprite("Speed.png", 15.0f, 600.0f);
	shieldPup = myEngine->CreateSprite("test.png", 145.0f, 600.0f);
	//speedPup->s
}
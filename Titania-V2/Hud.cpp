#include "Hud.h"
using namespace tle;



ISprite* firstHeart;
ISprite* secondHeart;
ISprite* thirdHeart;

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
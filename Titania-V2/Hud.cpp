#include "Hud.h"
using namespace tle;



ISprite* firstHeart;
ISprite* secondHeart;
ISprite* thirdHeart;

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
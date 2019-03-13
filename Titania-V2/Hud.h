#pragma once
#include <TL-Engine.h>
using namespace tle;

extern enum AmountLives { ThreeLives, TwoLives, OneLife, Dead };
extern enum RemoveLives { RemoveHeart, Pause };

void fullHealth(I3DEngine*& myEngine, AmountLives Health);
void removeHeart(I3DEngine*& myEngine, AmountLives& Health);
void speedPowerUP(I3DEngine*& myEngine);
void NoPowerUP(I3DEngine*& myEngine);
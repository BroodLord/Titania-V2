#pragma once
#include <TL-Engine.h>
#include "Defs.h"
using namespace tle;


extern enum AmountLives { ThreeLives, TwoLives, OneLife, Dead };
extern enum RemoveLives { RemoveHeart, Pause };

void fullHealth(I3DEngine*& myEngine, AmountLives Health);
void removeHeart(I3DEngine*& myEngine, AmountLives& Health);

void SpeedPowerUP(I3DEngine*& myEngine);
void NoPowerUP(I3DEngine*& myEngine);
void RemoveSpeedPowerUP(I3DEngine*& myEngine);
void SpawnSprites(I3DEngine*& myEngine);
void ShieldPowerUP(I3DEngine*& myEngine);
void RemoveShieldPowerUP(I3DEngine*& myEngine);
void RemoveBulletPowerUP(I3DEngine*& myEngine);
void BulletPowerUP(I3DEngine*& myEngine);
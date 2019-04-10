#pragma once
#include <TL-Engine.h>
#include "Defs.h"
using namespace tle;


extern enum AmountLives { ThreeLives, TwoLives, OneLife, Dead, ThreeLivesP2, TwoLivesP2, OneLifeP2, DeadP2};
extern enum RemoveLives { RemoveHeart, Pause, RemoveHeartP2, PauseP2};

void fullHealth(I3DEngine*& myEngine, AmountLives Health);
void removeHeart(I3DEngine*& myEngine, AmountLives& Health);

void fullHealthP2(I3DEngine*& myEngine, AmountLives HealthP2);
void removeHeartP2(I3DEngine*& myEngine, AmountLives& HealthP2);

void SpeedPowerUP(I3DEngine*& myEngine);
void NoPowerUP(I3DEngine*& myEngine);
void RemoveSpeedPowerUP(I3DEngine*& myEngine);
void SpawnSprites(I3DEngine*& myEngine);
void ShieldPowerUP(I3DEngine*& myEngine);
void RemoveShieldPowerUP(I3DEngine*& myEngine);
void RemoveBulletPowerUP(I3DEngine*& myEngine);
void BulletPowerUP(I3DEngine*& myEngine);

void SpeedPowerUPP2(I3DEngine*& myEngine);
void NoPowerUPP2(I3DEngine*& myEngine);
void RemoveSpeedPowerUPP2(I3DEngine*& myEngine);
void ShieldPowerUPP2(I3DEngine*& myEngine);
void RemoveShieldPowerUPP2(I3DEngine*& myEngine);
void RemoveBulletPowerUPP2(I3DEngine*& myEngine);
void BulletPowerUPP2(I3DEngine*& myEngine);
void SpawnSpritesP2(I3DEngine*& myEngine);
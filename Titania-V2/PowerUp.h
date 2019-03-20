#pragma once
#include <TL-Engine.h>
#include "Defs.h"
#include "Hud.h"
using namespace tle;

void ActivatePower(float frameTime, PowerUpState& currentPowerUpState, float powerTime, I3DEngine*& myEngine, sf::Sound powerDownMusic);
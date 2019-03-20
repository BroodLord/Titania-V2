#include "PowerUp.h"

float PowerUpTimer = 0.0f;

void ActivatePower(float frameTime, PowerUpState& currentPowerUpState, float powerTime, I3DEngine*& myEngine, sf::Sound powerDownMusic)
{
	

	while (powerTime > 0.0f)
	{
		powerTime -= frameTime;
		if (powerDownMusic.getStatus() == powerDownMusic.Stopped)
		{
			powerDownMusic.play();
		}

		/*if (PowerUpTimer <= 0.0f)
		{
			if (currentPowerUpState == Speed)
			{
				RemoveSpeedPowerUP(myEngine);
			}
			else if (currentPowerUpState == Shield)
			{
				RemoveShieldPowerUP(myEngine);
			}
		}*/
	}
	RemoveSpeedPowerUP(myEngine);

	currentPowerUpState = None;
}
#include "Shooting.h"
#include <SFML/Audio.hpp>
using namespace tle;

float matrix[16];
const float bulletSize = 0.008f;
const float bulletSpeed = 6.0f;

const int maxBullets = 15;
BulletData bullets[maxBullets];
BulletData bullets2[maxBullets];
int num1Bullets = 0;
int num2Bullets = 0;

void Shooting(bool moveCamTop, bool moveCamBehind, float frameTime, I3DEngine*& myEngine, IModel* playerShip, int& numBullets, IMesh*& bulletMesh, float playerShipSpeed, sf::Sound& shootingSound)
{

	if (moveCamTop != true && moveCamBehind != true)
	{
		for (int i = 0; i < num1Bullets; i++)
		{
			// Move bullet
			bullets[i].model->Move(-bullets[i].xVel * frameTime, -bullets[i].yVel * frameTime,
				-bullets[i].zVel * frameTime * 5.0f);
			bullets[i].model->RotateZ(500.0f * frameTime);

			// Decrease life and see if bullet is dead
			bullets[i].life -= frameTime;
			if (bullets[i].life <= 0)
			{
				// Destroy bullet
				bulletMesh->RemoveModel(bullets[i].model);

				// Copy last bullet into this dead slot to keep all live bullets in one block
				bullets[i].model = bullets[num1Bullets - 1].model;
				bullets[i].xVel = bullets[num1Bullets - 1].xVel;
				bullets[i].yVel = bullets[num1Bullets - 1].yVel;
				bullets[i].zVel = bullets[num1Bullets - 1].zVel;
				bullets[i].life = bullets[num1Bullets - 1].life;

				// Decrease number of bullets
				num1Bullets--;
			}
		}

		if ((myEngine->KeyHit(Key_Space) || myEngine->KeyHit(Mouse_LButton)) &&
			num1Bullets < maxBullets)
		{
			shootingSound.play();
			//*******************************
			// Play shooting sound here
			//*******************************

			// Create bullet 1
			float x = playerShip->GetX() - 0.015f * matrix[0] + 0.01f * matrix[8];
			float y = playerShip->GetY() - 0.015f * matrix[1] + 0.01f * matrix[9];
			float z = playerShip->GetZ() - 0.015f * matrix[2] + 0.01f * matrix[10];
			bullets[num1Bullets].model = bulletMesh->CreateModel(x - 1.5, y - 1, z - 4.5f);
			bullets[num1Bullets].model->Scale(bulletSize * 75.0f);


			// Get ship direction from matrix (x and z axes)
			playerShip->GetMatrix(matrix);
			float bulletSpeedX = playerShipSpeed;
			float bulletSpeedZ = playerShipSpeed + bulletSpeed;
			bullets[num1Bullets].xVel = bulletSpeedX * matrix[0] + bulletSpeedZ * matrix[8];
			bullets[num1Bullets].yVel = bulletSpeedX * matrix[1] + bulletSpeedZ * matrix[9];
			bullets[num1Bullets].zVel = bulletSpeedX * matrix[2] + bulletSpeedZ * matrix[10];

			// Length of bullet's life measured in seconds
			bullets[num1Bullets].life = 3.0f;
			++num1Bullets;



			// Create bullets in pairs - enough space for one more bullet?
			if (num1Bullets < maxBullets)
			{
				// Create bullet 2
				x = playerShip->GetX() + 0.015f * matrix[0] + 0.01f * matrix[8];
				y = playerShip->GetY() + 0.015f * matrix[1] + 0.01f * matrix[9];
				z = playerShip->GetZ() + 0.015f * matrix[2] + 0.01f * matrix[10];

				bullets[num1Bullets].model = bulletMesh->CreateModel(x, y, z);
				bullets[num1Bullets].model->Scale(bulletSize);


				// Get ship direction from matrix (x and z axes)
				bullets[num1Bullets].xVel = bulletSpeedX * matrix[0] + bulletSpeedZ * matrix[8];
				bullets[num1Bullets].yVel = bulletSpeedX * matrix[1] + bulletSpeedZ * matrix[9];
				bullets[num1Bullets].zVel = bulletSpeedX * matrix[2] + bulletSpeedZ * matrix[10];

				// Length of bullet's life measured in seconds
				bullets[num1Bullets].life = 1.5f;
				num1Bullets++;
			}
			for (int i = 0; i < num1Bullets; i++)
			{
				// Move bullet
				bullets[i].model->Move(-bullets[i].xVel * frameTime, -bullets[i].yVel * frameTime,
					-bullets[i].zVel * frameTime * 5.0f);
				bullets[i].model->RotateZ(500.0f * frameTime);

				// Decrease life and see if bullet is dead
				bullets[i].life -= frameTime;
				if (bullets[i].life <= 0)
				{
					// Destroy bullet
					bulletMesh->RemoveModel(bullets[i].model);

					// Copy last bullet into this dead slot to keep all live bullets in one block
					bullets[i].model = bullets[num1Bullets - 1].model;
					bullets[i].xVel = bullets[num1Bullets - 1].xVel;
					bullets[i].yVel = bullets[num1Bullets - 1].yVel;
					bullets[i].zVel = bullets[num1Bullets - 1].zVel;
					bullets[i].life = bullets[num1Bullets - 1].life;

					// Decrease number of bullets
					num1Bullets--;
				}
			}

			//////////***********************************************

			for (int i = 0; i < num2Bullets; i++)
			{
				// Move bullet
				bullets2[i].model->Move(-bullets2[i].xVel * frameTime, -bullets2[i].yVel * frameTime,
					-bullets2[i].zVel * frameTime * 5.0f);
				bullets2[i].model->RotateZ(500.0f * frameTime);
			
				// Decrease life and see if bullet is dead
				bullets2[i].life -= frameTime;
				if (bullets2[i].life <= 0)
				{
					// Destroy bullet
					bulletMesh->RemoveModel(bullets2[i].model);
			
					// Copy last bullet into this dead slot to keep all live bullets in one block
					bullets2[i].model = bullets2[num2Bullets - 1].model;
					bullets2[i].xVel = bullets2[num2Bullets - 1].xVel;
					bullets2[i].yVel = bullets2[num2Bullets - 1].yVel;
					bullets2[i].zVel = bullets2[num2Bullets - 1].zVel;
					bullets2[i].life = bullets2[num2Bullets - 1].life;
			
					// Decrease number of bullets
					num2Bullets--;
				}
			}
				shootingSound.play();
				//*******************************
				// Play shooting sound here
				//*******************************
			
				// Create bullet 1
				float x2 = playerShip->GetX() - 0.015f * matrix[0] + 0.01f * matrix[8];
				float y2 = playerShip->GetY() - 0.015f * matrix[1] + 0.01f * matrix[9];
				float z2 = playerShip->GetZ() - 0.015f * matrix[2] + 0.01f * matrix[10];
				bullets2[num2Bullets].model = bulletMesh->CreateModel(x + 1.5, y - 1, z - 4.5f);
				bullets2[num2Bullets].model->Scale(bulletSize * 75.0f);
			
			
				// Get ship direction from matrix (x and z axes)
				playerShip->GetMatrix(matrix);
				float bulletSpeedX2 = playerShipSpeed;
				float bulletSpeedZ2 = playerShipSpeed + bulletSpeed;
				bullets2[num2Bullets].xVel = bulletSpeedX * matrix[0] + bulletSpeedZ * matrix[8];
				bullets2[num2Bullets].yVel = bulletSpeedX * matrix[1] + bulletSpeedZ * matrix[9];
				bullets2[num2Bullets].zVel = bulletSpeedX * matrix[2] + bulletSpeedZ * matrix[10];
			
				// Length of bullet's life measured in seconds
				bullets2[num2Bullets].life = 3.0f;
				++num2Bullets;
			
			
			
				// Create bullets in pairs - enough space for one more bullet?
				if (num2Bullets < maxBullets)
				{
					// Create bullet 2
					x = playerShip->GetX() + 0.015f * matrix[0] + 0.01f * matrix[8];
					y = playerShip->GetY() + 0.015f * matrix[1] + 0.01f * matrix[9];
					z = playerShip->GetZ() + 0.015f * matrix[2] + 0.01f * matrix[10];
			
					bullets2[num2Bullets].model = bulletMesh->CreateModel(x, y, z);
					bullets2[num2Bullets].model->Scale(bulletSize);
			
			
					// Get ship direction from matrix (x and z axes)
					bullets2[num2Bullets].xVel = bulletSpeedX * matrix[0] + bulletSpeedZ * matrix[8];
					bullets2[num2Bullets].yVel = bulletSpeedX * matrix[1] + bulletSpeedZ * matrix[9];
					bullets2[num2Bullets].zVel = bulletSpeedX * matrix[2] + bulletSpeedZ * matrix[10];
			
					// Length of bullet's life measured in seconds
					bullets2[num2Bullets].life = 1.5f;
					num2Bullets++;
				}
				for (int i = 0; i < num2Bullets; i++)
				{
					// Move bullet
					bullets2[i].model->Move(-bullets2[i].xVel * frameTime, -bullets2[i].yVel * frameTime,
						-bullets2[i].zVel * frameTime * 5.0f);
					bullets2[i].model->RotateZ(500.0f * frameTime);
			
					// Decrease life and see if bullet is dead
					bullets2[i].life -= frameTime;
					if (bullets2[i].life <= 0)
					{
						// Destroy bullet
						bulletMesh->RemoveModel(bullets[i].model);
			
						// Copy last bullet into this dead slot to keep all live bullets in one block
						bullets2[i].model = bullets2[num2Bullets - 1].model;
						bullets2[i].xVel = bullets2[num2Bullets - 1].xVel;
						bullets2[i].yVel = bullets2[num2Bullets - 1].yVel;
						bullets2[i].zVel = bullets2[num2Bullets - 1].zVel;
						bullets2[i].life = bullets2[num2Bullets - 1].life;
			
						// Decrease number of bullets
						num2Bullets--;
					}
			}
		}
	}
	numBullets = num2Bullets + num1Bullets;

}
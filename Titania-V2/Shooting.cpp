#include "Shooting.h"

float matrix[16];
const float bulletSize = 0.008f;
const float bulletSpeed = 6.0f;
extern bool tripleBullet;

void Shooting(bool moveCamTop, bool moveCamBehind, float frameTime, I3DEngine*& myEngine, IModel* playerShip, int& numBullets, IMesh*& bulletMesh, float playerShipSpeed, sf::Sound& shootingSound, deque <CBulletData>& bullets)
{
	float x = playerShip->GetX() - 0.015f * matrix[0] + 0.01f * matrix[8];
	float y = playerShip->GetY() - 0.015f * matrix[1] + 0.01f * matrix[9];
	float z = playerShip->GetZ() - 0.015f * matrix[2] + 0.01f * matrix[10];
	
	
	float bulletSpeedX = playerShipSpeed;
	float bulletSpeedZ = playerShipSpeed + bulletSpeed;
	
	playerShip->GetMatrix(matrix);
	float xSpeed = bulletSpeedX * matrix[0] + bulletSpeedZ * matrix[8];
	float ySpeed = bulletSpeedX * matrix[1] + bulletSpeedZ * matrix[9];
	float zSpeed = bulletSpeedX * matrix[2] + bulletSpeedZ * matrix[10];


	if (moveCamTop != true && moveCamBehind != true)
	{


		CBulletData temp;
		CBulletData temp2;
		CBulletData temp3;

		for (int i = 0; i < numBullets; i++)
		{
			// Move bullet
			bullets[i].model->Move(-bullets[i].xVel * frameTime, -bullets[i].yVel * frameTime,
				-bullets[i].zVel * frameTime * 5.0f);
			bullets[i].model->RotateZ(500.0f * frameTime);
		}

		for (int i = 0; i < numBullets; i++)
		{
			// Decrease life and see if bullet is dead
			bullets[i].life -= frameTime;
			if (bullets[i].life <= 0)
			{
				// Destroy bullet
				bulletMesh->RemoveModel(bullets.front().model);

				// Copy last bullet into this dead slot to keep all live bullets in one block
				/*bullets[i].model = bullets[numBullets - 1].model;
				bullets[i].xVel = bullets[numBullets - 1].xVel;
				bullets[i].yVel = bullets[numBullets - 1].yVel;
				bullets[i].zVel = bullets[numBullets - 1].zVel;
				bullets[i].life = bullets[numBullets - 1].life;*/

				// Decrease number of bullets
				bullets.pop_front();
				numBullets--;
			}
		}

		if ((myEngine->KeyHit(Key_Space) || myEngine->KeyHit(Mouse_LButton)) && numBullets < maxBullets)
		{

				shootingSound.play();
				//*******************************
				// Play shooting sound here
				//*******************************

				// Create bullet 1

				temp.model = bulletMesh->CreateModel(x - 1.5f, y - 1.0f, z - 4.5f);
				temp.model->Scale(bulletSize * 75.0f);


				// Get ship direction from matrix (x and z axes)


				temp.xVel = xSpeed;
				temp.yVel = ySpeed;
				temp.zVel = zSpeed;

				// Length of bullet's life measured in seconds
				numBullets++;
				bullets.push_back(temp);


				// Create bullets in pairs - enough space for one more bullet?
				if (numBullets < maxBullets)
				{
					// Create bullet 2
					temp2.model = bulletMesh->CreateModel(x + 1.5f, y - 1.0f, z - 4.5f);
					temp2.model->Scale(bulletSize * 75.0f);

					// Get ship direction from matrix (x and z axes)

					temp2.xVel = xSpeed;
					temp2.yVel = ySpeed;
					temp2.zVel = zSpeed;

					// Length of bullet's life measured in seconds
					numBullets++;
					bullets.push_back(temp2);
				}

				if (tripleBullet == true && numBullets < maxBullets)
				{
					// bullet 3
					temp3.model = bulletMesh->CreateModel(x, y - 1.0f, z - 4.5f);
					temp3.model->Scale(bulletSize * 75.0f);


					// Get ship direction from matrix (x and z axes)


					temp3.xVel = xSpeed;
					temp3.yVel = ySpeed;
					temp3.zVel = zSpeed;

					// Length of bullet's life measured in seconds
					numBullets++;
					bullets.push_back(temp3);

				}

			}
		}
	
}
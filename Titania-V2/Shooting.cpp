#include "Shooting.h"
#include "Spawn.h"
#include <cmath>

float matrix[16];
const float bulletSize = 0.008f;
const float bulletSpeed = 6.0f;
extern bool tripleBullet;
extern int enemyShots;
extern sf::SoundBuffer shootingBuffer;
extern sf::Sound shootingSound;
extern deque <CBulletData> enemybullets;
extern deque <CBulletData> bullets;
extern deque <CBulletData> bullets2;
extern int numBullets;
extern int numBulletsP2;
extern float playerFireRate;
extern float player2FireRate;

void Shooting(bool moveCamTop, bool moveCamBehind, float frameTime, I3DEngine*& myEngine, IModel* playerShip, IMesh*& bulletMesh, float playerShipSpeed, sf::Sound& shootingSound)
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

		for (auto PlayerShots = bullets.begin(); PlayerShots != bullets.end(); PlayerShots++)
		{
			// Move bullet
			PlayerShots->model->Move(-PlayerShots->xVel * frameTime, -PlayerShots->yVel * frameTime,
				-PlayerShots->zVel * frameTime * 5.0f);
			PlayerShots->model->RotateZ(500.0f * frameTime);

		}
		for (auto PlayerShots = bullets.begin(); PlayerShots != bullets.end(); PlayerShots++)
		{

			// Decrease life and see if bullet is dead
			PlayerShots->life -= frameTime;
			if (PlayerShots->life <= 0)
			{
				// Destroy bullet
				bulletMesh->RemoveModel(bullets.front().model);

				// Copy last bullet into this dead slot to keep all live bullets in one block
				/*PlayerShots->model = bullets[numBullets - 1].model;
				PlayerShots->xVel = bullets[numBullets - 1].xVel;
				PlayerShots->yVel = bullets[numBullets - 1].yVel;
				PlayerShots->zVel = bullets[numBullets - 1].zVel;
				PlayerShots->life = bullets[numBullets - 1].life;*/

				// Decrease number of bullets
				bullets.pop_front();
				numBullets--;
				break;
			}
		}

		if ((myEngine->KeyHeld(Key_Space)) && numBullets + 2 < maxBullets && playerFireRate < 0.0f)
		{
			playerFireRate = 0.15f;
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


			if (tripleBullet == true && numBullets < maxBullets)
			{
				// bullet 3
				temp3.model = bulletMesh->CreateModel(x, y - 1.0f, z - 4.5f);
				temp3.model->Scale(bulletSize * 75.0f);
				temp3.model->SetSkin("GreenFire.jpg");

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

void Shooting2(bool moveCamTop, bool moveCamBehind, float frameTime, I3DEngine*& myEngine, IModel* playerShip2, IMesh*& bulletMesh, float playerShipSpeed, sf::Sound& shootingSound)
{
	float x = playerShip2->GetX() - 0.015f * matrix[0] + 0.01f * matrix[8];
	float y = playerShip2->GetY() - 0.015f * matrix[1] + 0.01f * matrix[9];
	float z = playerShip2->GetZ() - 0.015f * matrix[2] + 0.01f * matrix[10];


	float bulletSpeedX = playerShipSpeed;
	float bulletSpeedZ = playerShipSpeed + bulletSpeed;

	playerShip2->GetMatrix(matrix);
	float xSpeed = bulletSpeedX * matrix[0] + bulletSpeedZ * matrix[8];
	float ySpeed = bulletSpeedX * matrix[1] + bulletSpeedZ * matrix[9];
	float zSpeed = bulletSpeedX * matrix[2] + bulletSpeedZ * matrix[10];


	if (moveCamTop != true && moveCamBehind != true)
	{


		CBulletData temp;
		CBulletData temp2;
		CBulletData temp3;

		//for (int i = 0; i < numBulletsP2; i++)
		//{
		//	// Move bullet
		//	bullets2[i].model->Move(-bullets2[i].xVel * frameTime, -bullets2[i].yVel * frameTime,
		//		-bullets2[i].zVel * frameTime * 5.0f);
		//	bullets2[i].model->RotateZ(500.0f * frameTime);
		//}

		//for (int i = 0; i < numBulletsP2; i++)
		//{
		//	// Decrease life and see if bullet is dead
		//	bullets2[i].life -= frameTime;
		//	if (bullets2[i].life <= 0)
		//	{
		//		// Destroy bullet
		//		bulletMesh->RemoveModel(bullets2.front().model);

		//		// Copy last bullet into this dead slot to keep all live bullets in one block
		//		/*bullets[i].model = bullets[numBullets - 1].model;
		//		bullets[i].xVel = bullets[numBullets - 1].xVel;
		//		bullets[i].yVel = bullets[numBullets - 1].yVel;
		//		bullets[i].zVel = bullets[numBullets - 1].zVel;
		//		bullets[i].life = bullets[numBullets - 1].life;*/

		//		// Decrease number of bullets
		//		bullets.pop_front();
		//		numBulletsP2--;
		//	}
		//}

		if ((myEngine->KeyHeld(Mouse_MButton)) && numBulletsP2 + 2 < maxBulletsP2 && player2FireRate < 0.0f)
		{
			player2FireRate = 0.15f;
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
			numBulletsP2++;
			bullets.push_back(temp);


			// Create bullets in pairs - enough space for one more bullet?
			if (numBulletsP2 < maxBulletsP2)
			{
				// Create bullet 2
				temp2.model = bulletMesh->CreateModel(x + 1.5f, y - 1.0f, z - 4.5f);
				temp2.model->Scale(bulletSize * 75.0f);


				// Get ship direction from matrix (x and z axes)

				temp2.xVel = xSpeed;
				temp2.yVel = ySpeed;
				temp2.zVel = zSpeed;

				// Length of bullet's life measured in seconds
				numBulletsP2++;
				bullets.push_back(temp2);
			}

			if (tripleBullet == true && numBulletsP2 < maxBulletsP2)
			{
				// bullet 3
				temp3.model = bulletMesh->CreateModel(x, y - 1.0f, z - 4.5f);
				temp3.model->Scale(bulletSize * 75.0f);
				temp3.model->SetSkin("GreenFire.jpg")
					;
				// Get ship direction from matrix (x and z axes)


				temp3.xVel = xSpeed;
				temp3.yVel = ySpeed;
				temp3.zVel = zSpeed;

				// Length of bullet's life measured in seconds
				numBulletsP2++;
				bullets.push_back(temp3);

			}
		}
	}
}

void EnemyShooting(bool moveCamTop, bool moveCamBehind, float frameTime, I3DEngine*& myEngine, deque <unique_ptr <CShips>>& ship, IMesh*& bulletMesh)
{
	float x = ship.front()->mShipModel->GetX() - 0.015f * matrix[0] + 0.01f * matrix[8];
	float y = ship.front()->mShipModel->GetY() - 0.015f * matrix[1] + 0.01f * matrix[9];
	float z = ship.front()->mShipModel->GetZ() - 0.015f * matrix[2] + 0.01f * matrix[10];


	float bulletSpeedX = 0;
	float bulletSpeedZ = bulletSpeed;

	float xSpeed = bulletSpeedX * matrix[0] + bulletSpeedZ * matrix[8];
	float ySpeed = bulletSpeedX * matrix[1] + bulletSpeedZ * matrix[9];
	float zSpeed = bulletSpeedX * matrix[2] + bulletSpeedZ * matrix[10];
	int i;

	if (moveCamTop != true && moveCamBehind != true)
	{
		CBulletData temp;

		//*******************************
		// Play shooting sound here
		//*******************************
		shootingSound.play();
		// Create bullet 1
		temp.mHealth = ship.front()->mBulletHealth;
		temp.mRadius = ship.front()->mBulletRadius;
		temp.model = bulletMesh->CreateModel(x, y - 1.0f, z);
		temp.model->Scale(ship.front()->mBulletSize);
		temp.model->SetSkin("ice.jpg");
		temp.mOwner = "HeavyShot";
		temp.mSpeed = ship.front()->mBulletSpeed;
		i = random(0, 4);

		if (i == 2)
		{
			temp.model->SetSkin("Pinkfire.jpg");
			temp.mImmune = true;
		}
		// Get ship direction from matrix (x and z axes)


		temp.xVel = -xSpeed;
		temp.yVel = -ySpeed;
		temp.zVel = -zSpeed;

		// Length of bullet's life measured in seconds
		enemyShots++;
		enemybullets.push_back(temp);
	}

	/*for (auto it = enemybullets.begin(); it != enemybullets.end(); it++)
	{
	for (auto jt = bullets.begin(); jt != bullets.end(); jt++)
	{

	}
	}
	*/


}

void BeamShot(bool moveCamTop, bool moveCamBehind, float frameTime, I3DEngine*& myEngine, deque <unique_ptr <CShips>>& ship, IMesh*& bulletMesh)
{
	float x = ship.front()->mShipModel->GetX() - 0.015f * matrix[0] + 0.01f * matrix[8];
	float y = ship.front()->mShipModel->GetY() - 0.015f * matrix[1] + 0.01f * matrix[9];
	float z = ship.front()->mShipModel->GetZ() - 0.015f * matrix[2] + 0.01f * matrix[10];


	float bulletSpeedX = 0;
	float bulletSpeedZ = bulletSpeed;

	float xSpeed = bulletSpeedX * matrix[0] + bulletSpeedZ * matrix[8];
	float ySpeed = bulletSpeedX * matrix[1] + bulletSpeedZ * matrix[9];
	float zSpeed = bulletSpeedX * matrix[2] + bulletSpeedZ * matrix[10];

	if (moveCamTop != true && moveCamBehind != true)
	{
		CBulletData BossShipShots;

		//*******************************
		// Play shooting sound here
		//*******************************
		shootingSound.play();
		// Create bullet 1
		BossShipShots.mHealth = ship.front()->mBulletHealth;
		BossShipShots.mRadius = ship.front()->mBulletRadius;
		BossShipShots.model = bulletMesh->CreateModel(x - 13.0, y - 1.0f, z + 13);
		BossShipShots.model->Scale(ship.front()->mBulletSize);
		BossShipShots.model->SetSkin("ice.jpg");
		BossShipShots.mOwner = "Middle";
		BossShipShots.mSpeed = ship.front()->mBulletSpeed;


		// Get ship direction from matrix (x and z axes)


		BossShipShots.xVel = -xSpeed;
		BossShipShots.yVel = -ySpeed;
		BossShipShots.zVel = -zSpeed;

		// Length of bullet's life measured in seconds
		enemyShots++;
		enemybullets.push_back(BossShipShots);

		// Create bullets in pairs - enough space for one more bullet?

		// Create bullet 2
		BossShipShots.mHealth = ship.front()->mBulletHealth;
		BossShipShots.mRadius = ship.front()->mBulletRadius;
		BossShipShots.model = bulletMesh->CreateModel(x + 13.0f, y - 1.0f, z + 13);
		BossShipShots.model->Scale(ship.front()->mBulletSize);
		BossShipShots.model->SetSkin("ice.jpg");
		BossShipShots.mOwner = "Owner";
		BossShipShots.mSpeed = ship.front()->mBulletSpeed;

		// Get ship direction from matrix (x and z axes)

		BossShipShots.xVel = -xSpeed;
		BossShipShots.yVel = -ySpeed;
		BossShipShots.zVel = -zSpeed;

		// Length of bullet's life measured in seconds
		enemyShots++;
		enemybullets.push_back(BossShipShots);

		BossShipShots.mHealth = ship.front()->mBulletHealth;
		BossShipShots.mRadius = ship.front()->mBulletRadius;
		BossShipShots.model = bulletMesh->CreateModel(x + 13.0f, y - 1.0f, z + 15);
		BossShipShots.model->Scale(ship.front()->mBulletSize);
		BossShipShots.model->SetSkin("ice.jpg");
		BossShipShots.mOwner = "Owner";
		BossShipShots.mSpeed = ship.front()->mBulletSpeed;

		// Get ship direction from matrix (x and z axes)

		BossShipShots.xVel = -xSpeed;
		BossShipShots.yVel = -ySpeed;
		BossShipShots.zVel = -zSpeed;

		// Length of bullet's life measured in seconds
		enemyShots++;
		enemybullets.push_back(BossShipShots);

		BossShipShots.mHealth = ship.front()->mBulletHealth;
		BossShipShots.mRadius = ship.front()->mBulletRadius;
		BossShipShots.model = bulletMesh->CreateModel(x - 13.0f, y - 1.0f, z + 15);
		BossShipShots.model->Scale(ship.front()->mBulletSize);
		BossShipShots.model->SetSkin("ice.jpg");
		BossShipShots.mOwner = "Owner";
		BossShipShots.mSpeed = ship.front()->mBulletSpeed;

		// Get ship direction from matrix (x and z axes)

		BossShipShots.xVel = -xSpeed;
		BossShipShots.yVel = -ySpeed;
		BossShipShots.zVel = -zSpeed;

		// Length of bullet's life measured in seconds
		enemyShots++;
		enemybullets.push_back(BossShipShots);

		BossShipShots.mHealth = ship.front()->mBulletHealth;
		BossShipShots.mRadius = ship.front()->mBulletRadius;
		BossShipShots.model = bulletMesh->CreateModel(x + 13.0f, y - 1.0f, z + 17);
		BossShipShots.model->Scale(ship.front()->mBulletSize);
		BossShipShots.model->SetSkin("ice.jpg");
		BossShipShots.mOwner = "Owner";
		BossShipShots.mSpeed = ship.front()->mBulletSpeed;

		// Get ship direction from matrix (x and z axes)

		BossShipShots.xVel = -xSpeed;
		BossShipShots.yVel = -ySpeed;
		BossShipShots.zVel = -zSpeed;

		// Length of bullet's life measured in seconds
		enemyShots++;
		enemybullets.push_back(BossShipShots);

		BossShipShots.mHealth = ship.front()->mBulletHealth;
		BossShipShots.mRadius = ship.front()->mBulletRadius;
		BossShipShots.model = bulletMesh->CreateModel(x - 13.0f, y - 1.0f, z + 17);
		BossShipShots.model->Scale(ship.front()->mBulletSize);
		BossShipShots.model->SetSkin("ice.jpg");
		BossShipShots.mOwner = "Owner";
		BossShipShots.mSpeed = ship.front()->mBulletSpeed;

		// Get ship direction from matrix (x and z axes)

		BossShipShots.xVel = -xSpeed;
		BossShipShots.yVel = -ySpeed;
		BossShipShots.zVel = -zSpeed;

		// Length of bullet's life measured in seconds
		enemyShots++;
		enemybullets.push_back(BossShipShots);

		BossShipShots.mHealth = ship.front()->mBulletHealth;
		BossShipShots.mRadius = ship.front()->mBulletRadius;
		BossShipShots.model = bulletMesh->CreateModel(x + 13.0f, y - 1.0f, z + 19);
		BossShipShots.model->Scale(ship.front()->mBulletSize);
		BossShipShots.model->SetSkin("ice.jpg");
		BossShipShots.mOwner = "Owner";
		BossShipShots.mSpeed = ship.front()->mBulletSpeed;

		// Get ship direction from matrix (x and z axes)

		BossShipShots.xVel = -xSpeed;
		BossShipShots.yVel = -ySpeed;
		BossShipShots.zVel = -zSpeed;

		// Length of bullet's life measured in seconds
		enemyShots++;
		enemybullets.push_back(BossShipShots);

		BossShipShots.mHealth = ship.front()->mBulletHealth;
		BossShipShots.mRadius = ship.front()->mBulletRadius;
		BossShipShots.model = bulletMesh->CreateModel(x - 13.0f, y - 1.0f, z + 19);
		BossShipShots.model->Scale(ship.front()->mBulletSize);
		BossShipShots.model->SetSkin("ice.jpg");
		BossShipShots.mOwner = "Owner";
		BossShipShots.mSpeed = ship.front()->mBulletSpeed;

		// Get ship direction from matrix (x and z axes)

		BossShipShots.xVel = -xSpeed;
		BossShipShots.yVel = -ySpeed;
		BossShipShots.zVel = -zSpeed;

		// Length of bullet's life measured in seconds
		enemyShots++;
		enemybullets.push_back(BossShipShots);
	}
}


void FiveShot(bool moveCamTop, bool moveCamBehind, float frameTime, I3DEngine*& myEngine, deque <unique_ptr <CShips>>& ship, IMesh*& bulletMesh)
{
	float x = ship.front()->mShipModel->GetX() - 0.015f * matrix[0] + 0.01f * matrix[8];
	float y = ship.front()->mShipModel->GetY() - 0.015f * matrix[1] + 0.01f * matrix[9];
	float z = ship.front()->mShipModel->GetZ() - 0.015f * matrix[2] + 0.01f * matrix[10];


	float bulletSpeedX = 0;
	float bulletSpeedZ = bulletSpeed;

	float xSpeed = bulletSpeedX * matrix[0] + bulletSpeedZ * matrix[8];
	float ySpeed = bulletSpeedX * matrix[1] + bulletSpeedZ * matrix[9];
	float zSpeed = bulletSpeedX * matrix[2] + bulletSpeedZ * matrix[10];

	int i;

	if (moveCamTop != true && moveCamBehind != true)
	{
		CBulletData MiddleShipShots;

		//*******************************
		// Play shooting sound here
		//*******************************
		shootingSound.play();
		// Create bullet 1
		MiddleShipShots.mHealth = ship.front()->mBulletHealth;
		MiddleShipShots.mRadius = ship.front()->mBulletRadius;
		MiddleShipShots.model = bulletMesh->CreateModel(x, y - 1.0f, z);
		MiddleShipShots.model->Scale(ship.front()->mBulletSize);
		MiddleShipShots.model->SetSkin("ice.jpg");
		MiddleShipShots.mOwner = "Middle";
		MiddleShipShots.mSpeed = ship.front()->mBulletSpeed;
		i = random(0, 4);

		if (i == 2)
		{
			MiddleShipShots.model->SetSkin("Pinkfire.jpg");
			MiddleShipShots.mImmune = true;
		}

		// Get ship direction from matrix (x and z axes)


		MiddleShipShots.xVel = -xSpeed;
		MiddleShipShots.yVel = -ySpeed;
		MiddleShipShots.zVel = -zSpeed;

		// Length of bullet's life measured in seconds
		enemyShots++;
		enemybullets.push_back(MiddleShipShots);

		// Create bullets in pairs - enough space for one more bullet?

		// Create bullet 2
		MiddleShipShots.mHealth = ship.front()->mBulletHealth;
		MiddleShipShots.mRadius = ship.front()->mBulletRadius;
		MiddleShipShots.model = bulletMesh->CreateModel(x + 1.5f, y - 1.0f, z);
		MiddleShipShots.model->Scale(ship.front()->mBulletSize);
		MiddleShipShots.model->SetSkin("ice.jpg");
		MiddleShipShots.mOwner = "MiddleRight";
		MiddleShipShots.mSpeed = ship.front()->mBulletSpeed;
		i = random(0, 4);

		if (i == 2)
		{
			MiddleShipShots.model->SetSkin("Pinkfire.jpg");
			MiddleShipShots.mImmune = true;
		}

		// Get ship direction from matrix (x and z axes)

		MiddleShipShots.xVel = -xSpeed;
		MiddleShipShots.yVel = -ySpeed;
		MiddleShipShots.zVel = -zSpeed;

		// Length of bullet's life measured in seconds
		enemyShots++;
		enemybullets.push_back(MiddleShipShots);


		// bullet 3
		MiddleShipShots.mHealth = ship.front()->mBulletHealth;
		MiddleShipShots.mRadius = ship.front()->mBulletRadius;
		MiddleShipShots.model = bulletMesh->CreateModel(x - 1.5f, y - 1.0f, z);
		MiddleShipShots.model->Scale(ship.front()->mBulletSize);
		MiddleShipShots.model->SetSkin("ice.jpg");
		MiddleShipShots.mOwner = "MiddleLeft";
		MiddleShipShots.mSpeed = ship.front()->mBulletSpeed;
		i = random(0, 4);

		if (i == 2)
		{
			MiddleShipShots.model->SetSkin("Pinkfire.jpg");
			MiddleShipShots.mImmune = true;
		}

		// Get ship direction from matrix (x and z axes)


		MiddleShipShots.xVel = -xSpeed;
		MiddleShipShots.yVel = -ySpeed;
		MiddleShipShots.zVel = -zSpeed;

		// Length of bullet's life measured in seconds
		enemyShots++;
		enemybullets.push_back(MiddleShipShots);

		// bullet 4
		MiddleShipShots.mHealth = ship.front()->mBulletHealth;
		MiddleShipShots.mRadius = ship.front()->mBulletRadius;
		MiddleShipShots.model = bulletMesh->CreateModel(x - 2.5f, y - 1.0f, z);
		MiddleShipShots.model->Scale(ship.front()->mBulletSize);
		MiddleShipShots.model->SetSkin("ice.jpg");
		MiddleShipShots.mOwner = "Left";
		MiddleShipShots.mSpeed = ship.front()->mBulletSpeed;
		i = random(0, 4);

		if (i == 2)
		{
			MiddleShipShots.model->SetSkin("Pinkfire.jpg");
			MiddleShipShots.mImmune = true;
		}

		// Get ship direction from matrix (x and z axes)


		MiddleShipShots.xVel = -xSpeed;
		MiddleShipShots.yVel = -ySpeed;
		MiddleShipShots.zVel = -zSpeed;

		// Length of bullet's life measured in seconds
		enemyShots++;
		enemybullets.push_back(MiddleShipShots);

		// bullet 5
		MiddleShipShots.mHealth = ship.front()->mBulletHealth;
		MiddleShipShots.mRadius = ship.front()->mBulletRadius;
		MiddleShipShots.model = bulletMesh->CreateModel(x + 2.5f, y - 1.0f, z);
		MiddleShipShots.model->Scale(ship.front()->mBulletSize);
		MiddleShipShots.model->SetSkin("ice.jpg");
		MiddleShipShots.mOwner = "Right";
		MiddleShipShots.mSpeed = ship.front()->mBulletSpeed;
		i = random(0, 4);

		if (i == 2)
		{
			MiddleShipShots.model->SetSkin("Pinkfire.jpg");
			MiddleShipShots.mImmune = true;
		}

		// Get ship direction from matrix (x and z axes)


		MiddleShipShots.xVel = -xSpeed;
		MiddleShipShots.yVel = -ySpeed;
		MiddleShipShots.zVel = -zSpeed;

		// Length of bullet's life measured in seconds
		enemyShots++;
		enemybullets.push_back(MiddleShipShots);



	}





}

void OrbitShot(bool moveCamTop, bool moveCamBehind, float frameTime, I3DEngine*& myEngine, deque <unique_ptr <CShips>>& ship, IMesh*& bulletMesh)
{
	float x = ship.front()->mShipModel->GetX() - 0.015f * matrix[0] + 0.01f * matrix[8];
	float y = ship.front()->mShipModel->GetY() - 0.015f * matrix[1] + 0.01f * matrix[9];
	float z = ship.front()->mShipModel->GetZ() - 0.015f * matrix[2] + 0.01f * matrix[10];


	float bulletSpeedX = 0;
	float bulletSpeedZ = bulletSpeed;

	float xSpeed = bulletSpeedX * matrix[0] + bulletSpeedZ * matrix[8];
	float ySpeed = bulletSpeedX * matrix[1] + bulletSpeedZ * matrix[9];
	float zSpeed = bulletSpeedX * matrix[2] + bulletSpeedZ * matrix[10];

	int i;

	if (moveCamTop != true && moveCamBehind != true)
	{
		CBulletData LightShipShots;
		CBulletData LightShipShots2;
		CBulletData LightShipShots3;

		//*******************************
		// Play shooting sound here
		//*******************************
		shootingSound.play();
		// Create bullet 1
		LightShipShots.mHealth = ship.front()->mBulletHealth;
		LightShipShots.mRadius = ship.front()->mBulletRadius;
		LightShipShots.model = bulletMesh->CreateModel(x, y - 1.0f, z);
		LightShipShots.model->Scale(ship.front()->mBulletSize * 2);
		LightShipShots.model->SetSkin("ice.jpg");
		LightShipShots.mOwner = "LightMiddle";
		LightShipShots.mSpeed = ship.front()->mBulletSpeed;
		i = random(0, 4);

		if (i == 2)
		{
			LightShipShots.model->SetSkin("Pinkfire.jpg");
			LightShipShots.mImmune = true;
		}

		// Get ship direction from matrix (x and z axes)


		LightShipShots.xVel = -xSpeed;
		LightShipShots.yVel = -ySpeed;
		LightShipShots.zVel = -zSpeed;

		// Length of bullet's life measured in seconds


		// Create bullets in pairs - enough space for one more bullet?

		// Create bullet 2
		LightShipShots2.mHealth = ship.front()->mBulletHealth;
		LightShipShots2.mRadius = ship.front()->mBulletRadius;
		LightShipShots2.model = bulletMesh->CreateModel(x, y - 1.0f, z);
		LightShipShots2.model->Scale(ship.front()->mBulletSize);
		LightShipShots2.model->SetSkin("ice.jpg");
		LightShipShots2.mOwner = "LightRight";
		LightShipShots2.mSpeed = ship.front()->mBulletSpeed;
		i = random(0, 4);

		if (i == 2)
		{
			LightShipShots2.model->SetSkin("Pinkfire.jpg");
			LightShipShots2.mImmune = true;
		}

		// Get ship direction from matrix (x and z axes)

		LightShipShots2.xVel = -xSpeed;
		LightShipShots2.yVel = -ySpeed;
		LightShipShots2.zVel = -zSpeed;

		// Length of bullet's life measured in seconds

		// bullet 3
		LightShipShots3.mHealth = ship.front()->mBulletHealth;
		LightShipShots3.mRadius = ship.front()->mBulletRadius;
		LightShipShots3.model = bulletMesh->CreateModel(x, y - 1.0f, z);
		LightShipShots3.model->SetSkin("ice.jpg");
		LightShipShots3.model->Scale(ship.front()->mBulletSize);
		LightShipShots3.mOwner = "LightLeft";
		LightShipShots3.mSpeed = ship.front()->mBulletSpeed;
		i = random(0, 4);

		if (i == 2)
		{
			LightShipShots3.model->SetSkin("Pinkfire.jpg");
			LightShipShots3.mImmune = true;
		}

		// Get ship direction from matrix (x and z axes)


		LightShipShots3.xVel = -xSpeed;
		LightShipShots3.yVel = -ySpeed;
		LightShipShots3.zVel = -zSpeed;

		//LightShipShots2.model->AttachToParent(LightShipShots.model);
		//LightShipShots3.model->AttachToParent(LightShipShots.model);

		// Length of bullet's life measured in seconds
		enemyShots++;
		enemybullets.push_back(LightShipShots3);

		enemyShots++;
		enemybullets.push_back(LightShipShots2);

		enemyShots++;
		enemybullets.push_back(LightShipShots);


		/*for (auto it = enemybullets.begin(); it != enemybullets.end(); it++)
		{
		for (auto jt = bullets.begin(); jt != bullets.end(); jt++)
		{

		}
		}
		*/
	}

}

void MoveBullet(float frameTime, IMesh*& bulletMesh, IModel* player)
{
	//for(auto it = enemybullets.begin(); it != enemybullets.end(); it++)
	//{
	//	// Move bullet
	//	(*it).model->Move(-(*it).xVel * frameTime, -(*it).yVel * frameTime,
	//		-(*it).zVel * frameTime * 5.0f);
	//(*it).model->RotateZ(500.0f * frameTime);
	//}

	//for (auto it = enemybullets.begin(); it != enemybullets.end(); it++)
	//{
	//	// Decrease life and see if bullet is dead
	//	(*it).life -= frameTime;
	//	if ((*it).life <= 0)
	//	{
	//		// Destroy bullet
	//		Erase(enemybullets, (*it).model);
	//	}
	//}

	for (int i = 0; i < enemyShots; i++)
	{
		/*if (enemybullets[i].mOwner != "LightRight" && enemybullets[i].mOwner != "LightLeft" && enemybullets[i].mOwner != "LightMiddle")
		{
			if (player->GetX() > enemybullets[i].model->GetX())
			{
				enemybullets[i].model->MoveX((10.0f * enemybullets[i].mSpeed) * frameTime);

			}
			if (player->GetX() < enemybullets[i].model->GetX())
			{
				enemybullets[i].model->MoveX((10.0f * -enemybullets[i].mSpeed) * frameTime);
			}
		}*/

		//if (enemybullets[i].mOwner == "Owner")
		//{
		//	enemybullets[i].xVel = enemybullets[i].xVel + 0.06f;
		//	enemybullets[i].model->MoveX(-enemybullets[i].xVel * frameTime * 0.1f);
		//}
		if (enemybullets[i].mOwner == "Owner")
		{

		}

		if (enemybullets[i].mOwner == "Left")
		{
			enemybullets[i].xVel = enemybullets[i].xVel + 0.06f;
			enemybullets[i].model->MoveX(-enemybullets[i].xVel * frameTime * 0.1f);

			enemybullets[i].model->Move(-enemybullets[i].xVel * frameTime, -enemybullets[i].yVel * frameTime,
				-enemybullets[i].zVel * frameTime * (5.0f * enemybullets[i].mSpeed));
			enemybullets[i].model->RotateZ(500.0f * frameTime);
		}
		else if (enemybullets[i].mOwner == "Right")
		{
			enemybullets[i].xVel = enemybullets[i].xVel - 0.06f;
			enemybullets[i].model->MoveX(-enemybullets[i].xVel * frameTime * 0.1f);

			enemybullets[i].model->Move(-enemybullets[i].xVel * frameTime, -enemybullets[i].yVel * frameTime,
				-enemybullets[i].zVel * frameTime * (5.0f * enemybullets[i].mSpeed));
			enemybullets[i].model->RotateZ(500.0f * frameTime);
		}
		else if (enemybullets[i].mOwner == "MiddleRight")
		{
			enemybullets[i].xVel = enemybullets[i].xVel - 0.03f;
			enemybullets[i].model->MoveX(-enemybullets[i].xVel * frameTime * 0.1f);

			enemybullets[i].model->Move(-enemybullets[i].xVel * frameTime, -enemybullets[i].yVel * frameTime,
				-enemybullets[i].zVel * frameTime * (5.0f * enemybullets[i].mSpeed));
			enemybullets[i].model->RotateZ(500.0f * frameTime);
		}
		else if (enemybullets[i].mOwner == "MiddleLeft")
		{
			enemybullets[i].xVel = enemybullets[i].xVel + 0.03f;
			enemybullets[i].model->MoveX(-enemybullets[i].xVel * frameTime * 0.1f);

			enemybullets[i].model->Move(-enemybullets[i].xVel * frameTime, -enemybullets[i].yVel * frameTime,
				-enemybullets[i].zVel * frameTime * (5.0f * enemybullets[i].mSpeed));
			enemybullets[i].model->RotateZ(500.0f * frameTime);
		}
		else if (enemybullets[i].mOwner == "LightRight")
		{
			if (enemybullets.size() > i + 1 && enemybullets[i + 1].mOwner == "LightMiddle")
			{
				float bulletXpos = enemybullets[i + 1].model->GetX() - cos(enemybullets[i].angle) * -enemybullets[i].mDistance;
				float bulletZpos = enemybullets[i + 1].model->GetZ() + sin(enemybullets[i].angle) * -enemybullets[i].mDistance;
				//rotate -= 0.7f * frameTime;
				enemybullets[i].angle += 1.5f * frameTime;
				enemybullets[i].model->SetX(bulletXpos);
				enemybullets[i].model->SetZ(bulletZpos);
				enemybullets[i].mDistance -= 10.0f * frameTime;
			}

			enemybullets[i].model->Move(-enemybullets[i].xVel * frameTime, -enemybullets[i].yVel * frameTime,
				-enemybullets[i].zVel * frameTime * (5.0f * enemybullets[i].mSpeed));

		}
		else if (enemybullets[i].mOwner == "LightLeft")
		{
			if (enemybullets.size() > i + 2 && enemybullets[i + 2].mOwner == "LightMiddle")
			{
				float bulletXpos = enemybullets[i + 2].model->GetX() - cos(enemybullets[i].angle) * enemybullets[i].mDistance;
				float bulletZpos = enemybullets[i + 2].model->GetZ() + sin(enemybullets[i].angle) * enemybullets[i].mDistance;
				enemybullets[i].angle += 1.5f * frameTime;
				enemybullets[i].model->SetX(bulletXpos);
				enemybullets[i].model->SetZ(bulletZpos);
				enemybullets[i].mDistance -= 10.0f * frameTime;
			}
			else if (enemybullets.size() > i + 1 && enemybullets[i + 1].mOwner == "LightMiddle")
			{
				float bulletXpos = enemybullets[i + 1].model->GetX() - cos(enemybullets[i].angle) * enemybullets[i].mDistance;
				float bulletZpos = enemybullets[i + 1].model->GetZ() + sin(enemybullets[i].angle) * enemybullets[i].mDistance;
				//rotate -= 0.7f * frameTime;
				enemybullets[i].angle += 1.5f * frameTime;
				enemybullets[i].model->SetX(bulletXpos);
				enemybullets[i].model->SetZ(bulletZpos);
				enemybullets[i].mDistance -= 10.0f * frameTime;
			}


			enemybullets[i].model->Move(-enemybullets[i].xVel * frameTime, -enemybullets[i].yVel * frameTime,
				-enemybullets[i].zVel * frameTime * (5.0f * enemybullets[i].mSpeed));



		}
		else if (enemybullets[i].mOwner == "LightMiddle")
		{

			enemybullets[i].model->Move(-enemybullets[i].xVel * frameTime, -enemybullets[i].yVel * frameTime,
				-enemybullets[i].zVel * frameTime * (5.0f * enemybullets[i].mSpeed));
			enemybullets[i].model->RotateLocalY(200.0f * frameTime);

		}
		else if (enemybullets[i].mOwner == "HeavyShot")
		{

			if (player->GetX() > enemybullets[i].model->GetX())
			{
				enemybullets[i].model->MoveX((10.0f * enemybullets[i].mSpeed) * frameTime);

			}
			if (player->GetX() < enemybullets[i].model->GetX())
			{
				enemybullets[i].model->MoveX((10.0f * -enemybullets[i].mSpeed) * frameTime);
			}
			enemybullets[i].model->RotateZ(500.0f * frameTime);
			enemybullets[i].model->MoveZ(-enemybullets[i].zVel * frameTime * (5.0f * enemybullets[i].mSpeed));
			enemybullets[i].model->RotateZ(500.0f * frameTime);
		}
		else
		{
			// Move bullet
			enemybullets[i].model->Move(-enemybullets[i].xVel * frameTime, -enemybullets[i].yVel * frameTime,
				-enemybullets[i].zVel * frameTime * (5.0f * enemybullets[i].mSpeed));
			enemybullets[i].model->RotateZ(500.0f * frameTime);
		}
	}

	for (int i = 0; i < enemyShots; i++)
	{
		// Decrease life and see if bullet is dead
		enemybullets[i].life -= frameTime;
		if (enemybullets[i].life <= 0)
		{
			// Destroy bullet
			bulletMesh->RemoveModel(enemybullets.front().model);

			// Copy last bullet into this dead slot to keep all live bullets in one block
			

			// Decrease number of bullets
			enemybullets.pop_front();
			enemyShots--;
		}
	}

}
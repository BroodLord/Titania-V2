// Titania-V2.cpp: A program using the TL-Engine
#include <TL-Engine.h>	// TL-Engine include file and namespace
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include "Defs.h"
#include "Hud.h"
#include "Shooting.h"
#include <deque>
#include "Spawn.h"
#include "PowerUp.h"
using namespace tle;

struct particle
{
	IModel* flame;
	float moveVector[3];
};

sf::SoundBuffer shootingBuffer;
sf::Sound shootingSound;
sf::SoundBuffer mainMenuBuffer;
sf::Sound menuMusic;
sf::SoundBuffer battleBuffer;
sf::Sound battleMusic;
sf::SoundBuffer powerUpBuffer;
sf::Sound powerUpMusic;
sf::SoundBuffer powerDownBuffer;
sf::Sound powerDownMusic;

enum PlayerShipState { Normal, RollingLeft, RollingRight };

enum GameState { MainMenu, Play };
PlayerShipState currentPlayerShipState;

EKeyCode camSwitch = Key_1;
EKeyCode MoveUp = Key_W;
EKeyCode MoveRight = Key_D;
EKeyCode MoveDown = Key_S;
EKeyCode MoveLeft = Key_A;
EKeyCode Exit = Key_Escape;
EKeyCode RollRightKey = Key_E;
EKeyCode RollLeftKey = Key_Q;
EKeyCode kStartKey = Key_Return; //P key used to start the game

const float bulletSpeed = 6.0f;
const float bulletSize = 0.008f;
const float kCameraMove = 0.10f; // distance for the direction keys x and z axis
const float kMouseWheelMove = 10.0f; // distance for wheel movement z axis
const float kMouseRotation = 0.3f; // distance (in degrees) for rotation of the camera
bool mouseCaptureActive = false; // state of mouse capture
bool tripleBullet = false;

deque <CBulletData> bullets;
deque <CBulletData> lightBullets;
deque <CBulletData>  mediumBullets;
deque <CBulletData> heavyBullets;

int gPlayerScore = 0;
deque <unique_ptr <CPowerUp>> SpeedList;
deque <unique_ptr <CPowerUp>> ShieldList;
deque <unique_ptr <CPowerUp>> TripleList;
deque <unique_ptr <CPowerUp>> CurrentlySpawned;

deque <unique_ptr <CShips>> HeavyShipList;
deque <unique_ptr <CShips>> MediumShipList;
deque <unique_ptr <CShips>> LightShipList;
deque <unique_ptr <CShips>> SpawnedShipList;

void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine(kTLX);
	myEngine->StartFullscreen(1920, 1080);

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder(".\\Media");
	//myEngine->AddMediaFolder("C:\\Users\\danny\\Desktop\\Titania-V2\\Titania-V2\\Media");

	/**** Set up your scene here ****/
	ICamera* playerCamera = myEngine->CreateCamera(kManual);

	//** Meshes ** 
	IMesh* playerShipMesh;
	IMesh* floorMesh;
	IMesh* camBlockMesh;
	IMesh* skyBoxMesh;
	IMesh* towerTwoMesh;
	IMesh* towerNineMesh;
	IMesh* flameMesh;
	IMesh* bulletMesh;
	IMesh* lightMesh;
	IMesh* MediumMesh;
	IMesh* HeavyMesh;
	//IMesh* speedPowerUpMesh;
	//IMesh* shieldPowerUpMesh;
	//IMesh* bulletPowerUpMesh;
	IMesh* sphereMesh;

	//** Models
	IModel* playerShip;
	IModel* flame;
	IModel* floor;
	IModel* topDownCamBlock;
	IModel* skyBox;
	IModel* towerNine;
	IModel* towerTwo;
	IModel* Road[25];
	//IModel* speedPowerUp;
	//IModel* shieldPowerUp;
	//IModel* bulletPowerUp;
	IModel* shield;

	int numBullets = 0;
	int enemyBullets = 0;
	//BulletData bullets[maxBullets];

	//BulletData bullets2[maxBullets];

	float matrix[16];

	bool moveCamTop = false;
	bool barrelRollColdDown = false;
	bool moveCamBehind = false;

	float startingz = 802.0f;
	float startingZ = -840.0f;
	float startingx = 400.0f;
	float countDown = 1.8f;
	float currentX = 0.0f;
	float barrelRollCountDown = 2.0f;
	//float shieldPowerUpTimer = 9.0f;
	//float speedPowerUpTimer = 5.0f;
	//float bulletPowerUpTimer = 5.0f;
	float shieldPowerUpTimer = 0.0f;
	float speedPowerUpTimer = 0.0f;
	float bulletPowerUpTimer = 0.0f;
	float rollingTimer = 0.4f;


	int speedDisplay = 0;
	int shieldDisplay = 0;
	int bulletDisplay = 0;

	bool gameOver = false;

	PowerUpState currentSpeedPowerUpState = None;
	PowerUpState currentShieldPowerUpState = None;
	PowerUpState currentBulletPowerUpState = None;
	PowerUpState currentPowerUpState = None;

	//**** Hud Things ****
	AmountLives Health = ThreeLives;
	RemoveLives loseHealth = Pause;

	mainMenuBuffer.loadFromFile("Sound Affects\\mainMusic.wav");
	menuMusic.setBuffer(mainMenuBuffer);
	menuMusic.setVolume(30.0f);
	menuMusic.setLoop(true);

	battleBuffer.loadFromFile("Sound Affects\\Night.ogg");
	battleMusic.setBuffer(battleBuffer);
	battleMusic.setVolume(30.0f);
	battleMusic.setLoop(true);

	shootingBuffer.loadFromFile("Sound Affects\\shoot.wav");
	shootingSound.setBuffer(shootingBuffer);
	shootingSound.setPitch(0.5);
	shootingSound.setVolume(20.0f);

	powerUpBuffer.loadFromFile("Sound Affects\\Plug-in.wav");
	powerUpMusic.setBuffer(powerUpBuffer);
	powerUpMusic.setVolume(50.0f);

	powerDownBuffer.loadFromFile("Sound Affects\\Plug-out.wav");
	powerDownMusic.setBuffer(powerDownBuffer);
	powerDownMusic.setVolume(50.0f);


	IFont* Lives = myEngine->LoadFont("Arial", 28); //Loading in a font to use in text strings

	ISprite* backGround = myEngine->CreateSprite("background.jpg", 0.0f, 0.0f); //Simple box used as UI to make text stand out


	IFont* myFont = myEngine->LoadFont("Arial", 36); //Loading in a font to use in text strings
	IFont* deathFont = myEngine->LoadFont("Arial", 70); //Loading in a font to use in text strings
	IFont* preGameFont = myEngine->LoadFont("Arial", 36); //Loading in a font to use in text strings


	/* QUICK NOTE, Because of the camera being flipped the pluses and minus are swaped. (going left is pos)(going right is negative) */

	camBlockMesh = myEngine->LoadMesh("cube.x");
	lightMesh = myEngine->LoadMesh("enemyShip.x");
	MediumMesh = myEngine->LoadMesh("enemyShip1.x");
	HeavyMesh = myEngine->LoadMesh("enemyShip2.x");
	//shieldPowerUpMesh = myEngine->LoadMesh("PowerUp.x");

	CreateEnemies(myEngine);

	floorMesh = myEngine->LoadMesh("floor.x");
	floor = floorMesh->CreateModel(0.0f, -130.0f, 0.0f);
	floor->SetSkin("pavement.png");

	topDownCamBlock = camBlockMesh->CreateModel(0.0f, -35.0f, 750.0f);

	for (int i = 0; i < 5; i++)
	{
		
			unique_ptr <CSpeed> speedTemp (new CSpeed(myEngine));

		speedTemp->mModel = speedTemp->mMesh->CreateModel(0.0f, 500.0f, 785.0f);
		speedTemp->mModel->ScaleZ(0.01f);
		speedTemp->mModel->Scale(0.5f);
		speedTemp->mModel->RotateLocalX(90.0f);
		SpeedList.push_back(move(speedTemp));

		unique_ptr <CShield> shieldTemp (new CShield(myEngine));
		shieldTemp->mModel = shieldTemp->mMesh->CreateModel(0.0f, 500.0f, 785.0f);
		shieldTemp->mModel->ScaleZ(0.01f);
		shieldTemp->mModel->Scale(0.5f);
		shieldTemp->mModel->RotateLocalX(-90.0f);
		ShieldList.push_back(move(shieldTemp));

		unique_ptr <CTriple> tripleTemp (new CTriple(myEngine));
		tripleTemp->mModel = tripleTemp->mMesh->CreateModel(0.0f, 500.0f, 785.0f);
		tripleTemp->mModel->ScaleZ(0.01f);
		tripleTemp->mModel->Scale(0.5f);
		tripleTemp->mModel->RotateLocalX(90.0f);
		TripleList.push_back(move(tripleTemp));
	}

	for (int i = 0; i < 20; i++)
	{
		Road[i] = camBlockMesh->CreateModel(2.0f, 0.0f, startingz);
		Road[i]->SetSkin("background-1_0.png");
		Road[i]->ScaleX(10.0f);
		Road[i]->ScaleZ(10.0f);
		startingz -= 100.0f;
		Road[i]->AttachToParent(floor);
	}
	topDownCamBlock->Scale(0.01f);


	//powerupthing = myEngine->LoadMesh("PowerUpMiddle.x");
	//cubetest = powerupthing->CreateModel(0.0f, 0.0f, 0.0f);
	//cubetest->ScaleX(0.1f);
	//cubetest->AttachToParent(placementPowerUp);

	/*powerupthing = myEngine->LoadMesh("cube.x");
	cubetest = powerupthing->CreateModel(0.0f, 0.0f, 0.0f);
	cubetest->ScaleX(0.1f);*/


	playerShipMesh = myEngine->LoadMesh("gunShip.x");
	playerShip = playerShipMesh->CreateModel(0.0f, -30.0f, 785.0f);

	sphereMesh = myEngine->LoadMesh("Sphere.x");
	shield = sphereMesh->CreateModel(0.0f, 500.0f, 0.0f);
	shield->AttachToParent(playerShip);
	shield->Scale(0.6f);

	playerCamera->SetLocalPosition(0.0f, 49.0f, 771.0f);
	playerCamera->RotateLocalX(90.0f);
	playerCamera->RotateLocalZ(180.0f);
	int count = 0;
	int number = 0;
	towerNineMesh = myEngine->LoadMesh("skyscraper04.x");
	towerTwoMesh = myEngine->LoadMesh("skyscraper02.x");

	for (int i = 0; i < 100; i++)
	{
		number++;
		if (count == 3)
		{
			startingx -= 100.0f;
			startingx -= 100;
		}
		else
		{
			startingx -= 100;
		}
		if (number == 1)
		{

			towerNine = towerNineMesh->CreateModel(startingx, 0.0f, startingZ);
			towerNine->AttachToParent(floor);
			towerNine->ScaleY(0.4);
		}
		if (number == 2)
		{
			if (count == 3)
			{
				startingx += 25;
			}
			towerTwo = towerTwoMesh->CreateModel(startingx, 0.0f, startingZ);
			towerTwo->AttachToParent(floor);
			towerTwo->RotateLocalY(90);
			towerTwo->ScaleY(0.8);
		}
		count++;
		if (count != 6)
		{
			if (number == 2)
			{
				number = 0;
			}
		}
		if (count == 6)
		{
			count = 0;
			if (number == 1)
			{
				number = 0;
			}
			if (number == 2)
			{
				number = 1;
			}
			startingZ += 100.0f;
			startingx = 400.0f;
		}

	}

	bulletMesh = myEngine->LoadMesh("Flare.x");

	skyBoxMesh = myEngine->LoadMesh("Skybox 01.x");
	skyBox = skyBoxMesh->CreateModel(0.0f, -1050.0f, 0.0f);

	//fixedCamBlock->AttachToParent(playerShip);
	eCameraPos cameraPos;
	GameState currentGameState = MainMenu;
	cameraPos = topDown;



	//NoPowerUP(myEngine);
	SpawnSprites(myEngine);

	// The main game loop, repeat until engine is stopped
	myEngine->Timer();
	while (myEngine->IsRunning())
	{
		myEngine->DrawScene();
		currentX = playerShip->GetLocalX();
		float frameTime = myEngine->Timer();
		// Draw the scene
		SpawnEnemies(numBullets, bullets, moveCamTop, moveCamBehind, frameTime, bulletMesh, myEngine);
		stringstream powerUpStateText; //Text altered to present gamestate
		stringstream speedText; //Text altered to present gamestate
		stringstream shieldText; //Text altered to present gamestate
		stringstream tripleText; //Text altered to present gamestate

		string kPowerUpStateText = "PowerUp: ";
		string kNoneText = "None";
		string kSpeedText = "Speed";

		float playerShipSpeed = 50.0f * frameTime; // Player speed
		float floorResert = floor->GetLocalZ();

		//POWERUPS - DANNY LOOK AT THIS
		stringstream preGameText;

		string kPlayText = "Press Enter to Start";
		string kQuitText = "Press Esc to Quit";


		if (currentGameState == MainMenu)
		{
			battleMusic.stop();
			if (menuMusic.getStatus() == menuMusic.Stopped)
			{
				menuMusic.play();
			}
			menuMusic.setLoop(true);
			backGround->SetPosition(0, 0);
			playerCamera->LookAt(topDownCamBlock);
			preGameText << kPlayText << "   " << kQuitText;
			preGameFont->Draw(preGameText.str(), 400.0f, 300.0f, kWhite); //Game state text is set to go
			preGameText.str(""); // Clear myStream

			if (myEngine->KeyHit(kStartKey))
			{
				backGround->SetPosition(100000, 100000);
				currentGameState = Play;
				fullHealth(myEngine, Health);
				ISprite* myUI = myEngine->CreateSprite("backdrop2.png", -30.0f, -15.0f, 0.9f); //Simple box used as UI to make text stand out
			}
		}


		if (currentGameState == Play && gameOver == false)
		{

			if (Health != Dead)
			{
				Shooting(moveCamTop, moveCamBehind, frameTime, myEngine, playerShip, numBullets, bulletMesh, playerShipSpeed, shootingSound, bullets);
				ActivateEnemies(moveCamTop, moveCamBehind, frameTime, myEngine, bulletMesh);
			}


			menuMusic.stop();

		
			



			if (battleMusic.getStatus() == battleMusic.Stopped)
			{
				battleMusic.play();

			}

			Lives->Draw("Lives:", 70.0f, 23.0f, kCyan);

			if (Health == Dead)
			{
				gameOver = true;
			}

			//**** Hud Stuff ****
			powerUpStateText << "    Bullets: " << numBullets;
			myFont->Draw(powerUpStateText.str(), 15.0f, 70.0f, kWhite); //Game state text is set to go
			powerUpStateText.str(""); // Clear myStream

			powerUpStateText << "    Score: " << gPlayerScore;
			myFont->Draw(powerUpStateText.str(), 15.0f, 100.0f, kWhite); //Game state text is set to go
			powerUpStateText.str(""); // Clear myStream


			tripleText << bulletDisplay;
			myFont->Draw(tripleText.str(), 168.95f, 155.0f, kWhite); //Game state text is set to go
			tripleText.str(""); // Clear myStream

			shieldText << shieldDisplay;
			myFont->Draw(shieldText.str(), 103.0f, 155.0f, kWhite); //Game state text is set to go
			shieldText.str(""); // Clear myStream

			speedText << speedDisplay;
			myFont->Draw(speedText.str(), 37.5f, 155.0f, kWhite); //Game state text is set to go
			speedText.str(""); // Clear myStream

			if (moveCamTop != true && moveCamBehind != true)
			{
				int i = 0;
				for (auto it = CurrentlySpawned.begin(); it != CurrentlySpawned.end(); it++)
				{

					//** Power Up Collision **
					if (sphere2sphere(playerShip, (*it)->mModel, PLAYERSHIPRADIUS, PLACEMENTPOWERUPRADIUS)) //Collision with powerup
					{
						(*it)->mModel->SetY(500.0f);
						currentPowerUpState = (*it)->mPowerType;
						powerUpMusic.play();
						(*it)->Power(myEngine, i);
						//Erase(CurrentlySpawned, (*it)->mPowerType);
						//CurrentlySpawned.pop_front();
					}

					i++;
					if (currentPowerUpState == Speed)
					{
						currentSpeedPowerUpState = Speed;
						speedPowerUpTimer = 5.0f;
					}
					else if (currentPowerUpState == Shield)
					{
						currentShieldPowerUpState = Shield;
						shieldPowerUpTimer = 9.0f;
					}
					else if (currentPowerUpState == Bullet)
					{
						currentBulletPowerUpState = Bullet;
						bulletPowerUpTimer = 5.0f;
					}
				}


				currentPowerUpState = None;

				if (currentSpeedPowerUpState == Speed)
				{
					speedDisplay = speedPowerUpTimer + 1;
					if (speedPowerUpTimer > 0.0f)
					{
						playerShipSpeed = 75.0f * frameTime;
						speedPowerUpTimer -= frameTime;
						if (powerDownMusic.getStatus() == powerDownMusic.Stopped)
						{
							powerDownMusic.play();
						}
					}
					else if (speedPowerUpTimer < 0.0f)
					{
						RemoveSpeedPowerUP(myEngine);
						//speedPowerUpTimer = 5.0f;
						speedDisplay = 0;
						currentSpeedPowerUpState = None;
					}
				}

				if (currentShieldPowerUpState == Shield)
				{
					shieldDisplay = shieldPowerUpTimer + 1;

					shield->SetY(-30.0f);
					shield->RotateLocalY(250.0f * frameTime);

					if (shieldPowerUpTimer > 0.0f)
					{
						shieldPowerUpTimer -= frameTime;
						if (powerDownMusic.getStatus() == powerDownMusic.Stopped)
						{
							powerDownMusic.play();
						}
					}
					else if (shieldPowerUpTimer < 0.0f)
					{
						RemoveShieldPowerUP(myEngine);
						//shieldPowerUpTimer = 9.0f;
						shieldDisplay = 0;
						shield->SetY(500.0f);
						currentShieldPowerUpState = None;
					}
				}

				if (currentBulletPowerUpState == Bullet)
				{
					tripleBullet = true;
					bulletDisplay = bulletPowerUpTimer + 1;
					if (bulletPowerUpTimer > 0.0f)
					{
						bulletPowerUpTimer -= frameTime;
						if (powerDownMusic.getStatus() == powerDownMusic.Stopped)
						{
							powerDownMusic.play();
						}
					}
					else if (bulletPowerUpTimer < 0.0f)
					{
						RemoveBulletPowerUP(myEngine);
						//bulletPowerUpTimer = 5.0f;
						bulletDisplay = 0;
						currentBulletPowerUpState = None;
						tripleBullet = false;
					}
				}

				//if (behind)
				//{
				//	for (auto it = CurrentlySpawned.begin(); it != CurrentlySpawned.end(); it++)
				//	{						
				//		//(*it)->mModel->RotateLocalX(50.0f * frameTime);
				//		(*it)->mModel->RotateLocalX(-50.0f * frameTime);
				//	}
				//}
				//else if (topDown)
				//{
				//	for (auto it = CurrentlySpawned.begin(); it != CurrentlySpawned.end(); it++)
				//	{
				//		(*it)->mModel->RotateLocalX(50.0f * frameTime);
				//	}
				//}


				if (!CurrentlySpawned.empty())
				{
					if (CurrentlySpawned.front()->mModel->GetZ() > 800.0f)
					{
						if (CurrentlySpawned.front()->mPowerType == Speed)
						{
							CurrentlySpawned.front()->mModel->SetPosition(0.0f, 500.0f, 785.0f);
							SpeedList.push_back(move(CurrentlySpawned.front()));
						}
						else if (CurrentlySpawned.front()->mPowerType == Shield)
						{
							CurrentlySpawned.front()->mModel->SetPosition(0.0f, 500.0f, 785.0f);
							ShieldList.push_back(move(CurrentlySpawned.front()));
						}
						else if (CurrentlySpawned.front()->mPowerType == Bullet)
						{
							CurrentlySpawned.front()->mModel->SetPosition(0.0f, 500.0f, 785.0f);
							TripleList.push_back(move(CurrentlySpawned.front()));
						}

						CurrentlySpawned.pop_front();
					}
				}

			}


			if (moveCamTop != true && moveCamBehind != true)
			{
				if (barrelRollColdDown == false)
				{
					if (currentPlayerShipState == Normal)
					{
						if (myEngine->KeyHit(RollRightKey))
						{
							currentPlayerShipState = RollingRight;
						}

						if (myEngine->KeyHit(RollLeftKey))
						{
							currentPlayerShipState = RollingLeft;
						}
					}

					if (currentPlayerShipState == RollingRight)
					{
						rollingTimer -= frameTime;
						if (rollingTimer > 0)
						{
							playerShip->RotateZ(900.0f * frameTime);
							playerShip->MoveX(-playerShipSpeed);
						}
						if (rollingTimer <= 0)
						{
							rollingTimer = 0.4f;
							currentPlayerShipState = Normal;
							barrelRollColdDown = true;
							playerShip->ResetOrientation();
							//player invunerable
						}
					}

					if (currentPlayerShipState == RollingLeft)
					{
						rollingTimer -= frameTime;
						if (rollingTimer > 0)
						{
							playerShip->RotateZ(-900.0f * frameTime);
							playerShip->MoveX(50.0f * frameTime);
						}
						if (rollingTimer <= 0)
						{
							rollingTimer = 0.4f;
							currentPlayerShipState = Normal;
							barrelRollColdDown = true;
							playerShip->ResetOrientation();
							//player invunerable
						}
					}
				}

				//**** Health ****

				if (myEngine->KeyHit(Key_L))
				{
					loseHealth = RemoveHeart;
				}

				if (loseHealth == RemoveHeart)
				{
					removeHeart(myEngine, Health);
					loseHealth = Pause;
				}

			}

			if (currentX <= -27.0f)
			{
				playerShip->MoveX(playerShipSpeed);
			}
			if (currentX >= 27.0f)
			{
				playerShip->MoveX(-playerShipSpeed);
			}


			/* Camera Switching */
			switch (cameraPos)
			{
			case behind:
			{
				if (moveCamBehind != true)
				{
					floor->MoveLocalZ(80.0f * frameTime);

					for (auto it = CurrentlySpawned.begin(); it != CurrentlySpawned.end(); it++)
					{
						(*it)->mModel->RotateLocalY(50.0f * frameTime);
						(*it)->mModel->MoveZ(playerShipSpeed);
					}

					if (floorResert >= 200)
					{
						floor->SetLocalZ(0.0f);
					}
					if (currentPlayerShipState != RollingLeft && currentPlayerShipState != RollingRight)
					{
						if (myEngine->KeyHeld(MoveRight))
						{
							playerShip->MoveX(-playerShipSpeed);
						}
						if (myEngine->KeyHeld(MoveLeft))
						{
							playerShip->MoveX(playerShipSpeed);
						}
					}
				}
				if (moveCamBehind != true)
				{
					if (myEngine->KeyHit(camSwitch))
					{
						moveCamBehind = true;
						playerCamera->SetPosition(0.0f, -20.0f, 825.0f);
					}
				}
				if (moveCamBehind == true)
				{
					playerCamera->LookAt(topDownCamBlock);
					countDown -= frameTime;
					playerCamera->MoveLocalY(50.0 * frameTime);
					playerCamera->MoveLocalZ(-5.0 * frameTime);

					for (auto it = CurrentlySpawned.begin(); it != CurrentlySpawned.end(); it++)
					{
						(*it)->mModel->RotateLocalX(-50.0f * frameTime);
					}

					for (auto it = SpeedList.begin(); it != SpeedList.end(); it++)
					{
						(*it)->mModel->RotateLocalX(-50.0f * frameTime);
					}

					for (auto it = ShieldList.begin(); it != ShieldList.end(); it++)
					{
						(*it)->mModel->RotateLocalX(-50.0f * frameTime);
					}

					for (auto it = TripleList.begin(); it != TripleList.end(); it++)
					{
						(*it)->mModel->RotateLocalX(-50.0f * frameTime);
					}

					if (countDown <= 0)
					{
						moveCamBehind = false;
						countDown = 1.8;
						playerCamera->DetachFromParent();
						cameraPos = topDown;


					}
				}
				break;
			}
			case topDown:
			{

				playerCamera->LookAt(topDownCamBlock);
				if (moveCamTop != true)
				{
					floor->MoveLocalZ(80.0f * frameTime);
					for (auto it = CurrentlySpawned.begin(); it != CurrentlySpawned.end(); it++)
					{
						(*it)->mModel->RotateY(50.0f * frameTime);
						(*it)->mModel->MoveZ(playerShipSpeed);
					}

					if (floorResert >= 200)
					{
						floor->SetLocalZ(0.0f);
					}
					if (currentPlayerShipState != RollingLeft && currentPlayerShipState != RollingRight)
					{
						if (myEngine->KeyHeld(MoveRight))
						{
							playerShip->MoveX(-playerShipSpeed);
						}
						if (myEngine->KeyHeld(MoveLeft))
						{
							playerShip->MoveX(playerShipSpeed);
						}
					}
				}

				if (moveCamTop != true)
				{
					if (myEngine->KeyHit(camSwitch))
					{
						moveCamTop = true;
						playerCamera->ResetOrientation();
					}
				}
				if (moveCamTop == true)
				{
					countDown -= frameTime;
					playerCamera->MoveLocalY(-50.0 * frameTime);
					playerCamera->MoveLocalZ(5.0 * frameTime);

					for (auto it = CurrentlySpawned.begin(); it != CurrentlySpawned.end(); it++)
					{
						(*it)->mModel->RotateLocalX(50.0f * frameTime);
					}

					for (auto it = SpeedList.begin(); it != SpeedList.end(); it++)
					{
						(*it)->mModel->RotateLocalX(50.0f * frameTime);
					}

					for (auto it = ShieldList.begin(); it != ShieldList.end(); it++)
					{
						(*it)->mModel->RotateLocalX(50.0f * frameTime);
					}

					for (auto it = TripleList.begin(); it != TripleList.end(); it++)
					{
						(*it)->mModel->RotateLocalX(50.0f * frameTime);
					}
					if (countDown <= 0)
					{
						moveCamTop = false;
						countDown = 1.8;
						cameraPos = behind;
					}
				}
				break;
			}
			}
			if (barrelRollColdDown == true)
			{
				barrelRollCountDown -= frameTime;
				if (barrelRollCountDown <= 0)
				{
					barrelRollColdDown = false;
					barrelRollCountDown = 2.0f;
				}
			}
		}
		if (gameOver == true && Health == Dead)
		{
			deathFont->Draw("Game Over", 800.0f, 500.0f, kBlack);
			if (myEngine->KeyHit(Key_Return))
			{
				//speedPowerUp->SetPosition(0.0f, -30.0f, 730.0f);
				currentGameState = MainMenu;
				Health = ThreeLives;
				gameOver = false;

			}
		}

		/******************************/

		/**** Update your scene each frame here ****/
#ifndef DEBUG
		if (mouseCaptureActive)
		{
			int mouseMoveX = myEngine->GetMouseMovementX();
			playerCamera->RotateY(mouseMoveX * kMouseRotation); // the MouseRotation reduces the rotation speed

			int mouseMoveY = myEngine->GetMouseMovementY();
			playerCamera->RotateLocalX(mouseMoveY * kMouseRotation); // the MouseRotation reduces the rotation speed

			float mouseMoveWheel = myEngine->GetMouseWheelMovement();
			playerCamera->MoveLocalZ(mouseMoveWheel * kMouseWheelMove); // the MouseRotation reduces the rotation speed
		}

		// toggle mouse capture
		if (myEngine->KeyHit(Key_Tab))
		{
			if (mouseCaptureActive)
			{
				myEngine->StopMouseCapture();
				mouseCaptureActive = false;
			}
			else
			{
				myEngine->StartMouseCapture();
				mouseCaptureActive = true;
			}
		}

#endif // DEBUG

		// Exit the game when running
		if (myEngine->KeyHit(Exit))
		{
			myEngine->Stop();
		}

	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}
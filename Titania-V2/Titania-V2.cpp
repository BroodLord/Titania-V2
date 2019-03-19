// Titania-V2.cpp: A program using the TL-Engine
#include <TL-Engine.h>	// TL-Engine include file and namespace
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <SFML/Audio.hpp>
#include <cmath>
#include "Defs.h"
#include "Hud.h"
#include "Shooting.h"
#include <deque>
using namespace tle;

struct particle
{
	IModel* flame;
	float moveVector[3];
};

struct LightEnemyShip
{
	IModel* lightShip[50];
	int firingSpeed = 5.0f;
	int Health = 2;
};
struct MediumEnemyShip
{
	IModel* MediumShip[30];
	int firingSpeed = 3.0f;
	int Health = 4;
};
struct HeavyEnemyShip
{
	IModel* HeavyShip[20];
	int firingSpeed = 1.5f;
	int Health = 6;
};

int spawnArray[30] = { 1,3,2,1,2,3,3,1,2,1,3,2,2,1,3,2,1,1,3,2,3,2,1,2,3,1,2,3,2,1, };
int spawnCounter = 0;

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


enum PowerUpState { None, Speed };
enum PlayerShipState { Normal, RollingLeft, RollingRight };
enum EnemyShipState {Spawning, Active, Deactivated};
enum GameState { MainMenu, Play };
PlayerShipState currentPlayerShipState;
EnemyShipState currentEnemyShipState;

EKeyCode camSwitch = Key_1;
EKeyCode MoveUp = Key_W;
EKeyCode MoveRight = Key_D;
EKeyCode MoveDown = Key_S;
EKeyCode MoveLeft = Key_A;
EKeyCode Exit = Key_Escape;
EKeyCode RollRightKey = Key_E;
EKeyCode RollLeftKey = Key_Q;
EKeyCode kStartKey = Key_Return; //P key used to start the game

const float PLAYERSHIPRADIUS = 3.0f;
const float PLACEMENTPOWERUPRADIUS = 2.0f;
const float ENEMYSHIPRADIUS = 8.0f;
const float BULLETRADIUS = 8.0f;

const float bulletSpeed = 6.0f;
const float bulletSize = 0.008f;
const float kCameraMove = 0.10f; // distance for the direction keys x and z axis
const float kMouseWheelMove = 10.0f; // distance for wheel movement z axis
const float kMouseRotation = 0.3f; // distance (in degrees) for rotation of the camera
bool mouseCaptureActive = false; // state of mouse capture

deque <BulletData> bullets;
//deque <BulletData> bullets2;

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
	IMesh* powerUpMesh;
	IMesh* flameMesh;
	IMesh* bulletMesh;
	IMesh* lightMesh;
	IMesh* MediumMesh;
	IMesh* HeavyMesh;

	//** Models
	IModel* playerShip;
	IModel* flame;
	IModel* floor;
	IModel* topDownCamBlock;
	IModel* skyBox;
	IModel* towerNine;
	IModel* towerTwo;
	IModel* Road[25];
	IModel* placementPowerUp;

	int numBullets = 0;
	//BulletData bullets[maxBullets];
	HeavyEnemyShip heavyShip;
	MediumEnemyShip mediumShip;
	LightEnemyShip lightShip;
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
	float powerUpTimer = 5.0f;
	float rollingTimer = 0.4f;
	float closeCounter = 2, farCounter = 2.8, MidCounter = 2.4;



	bool gameOver = false;

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

	for (int i = 0; i < 20; i++)
	{
		heavyShip.HeavyShip[i] = lightMesh->CreateModel(120.0f, -30.0f, 700.0f);
		heavyShip.HeavyShip[i]->Scale(2);
		heavyShip.HeavyShip[i]->RotateY(180);
	}
	for (int i = 0; i < 30; i++)
	{
		mediumShip.MediumShip[i] = MediumMesh->CreateModel(-120.0f, -30.0f, 700.0f);
		mediumShip.MediumShip[i]->Scale(1.5);
		mediumShip.MediumShip[i]->RotateY(180);

	}
	for (int i = 0; i < 50; i++)
	{
		lightShip.lightShip[i] = HeavyMesh->CreateModel(120.0f, -30.0f, 700.0f);
		lightShip.lightShip[i]->Scale(1.5);
		lightShip.lightShip[i]->RotateY(180);
	}


	floorMesh = myEngine->LoadMesh("floor.x");
	floor = floorMesh->CreateModel(0.0f, -130.0f, 0.0f);
	floor->SetSkin("pavement.png");

	topDownCamBlock = camBlockMesh->CreateModel(0.0f, -35.0f, 750.0f);
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

	powerUpMesh = myEngine->LoadMesh("megagatt.x");
	placementPowerUp = powerUpMesh->CreateModel(0.0f, -30.0f, 600.0f);
	placementPowerUp->Scale(15.0f);

	playerShipMesh = myEngine->LoadMesh("gunShip.x");
	playerShip = playerShipMesh->CreateModel(0.0f, -30.0f, 785.0f);

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
	currentEnemyShipState = Active;

	NoPowerUP(myEngine);

	// The main game loop, repeat until engine is stopped
	myEngine->Timer();
	while (myEngine->IsRunning())
	{
		currentX = playerShip->GetLocalX();
		float frameTime = myEngine->Timer();
		// Draw the scene
		myEngine->DrawScene();

		stringstream powerUpStateText; //Text altered to present gamestate
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
			}

			menuMusic.stop();
			static int lightCounter = 0;
			static int MedCounter = 0;
			static int HeavyCounter = 0;

			if (currentEnemyShipState == Active)
			{
				for (int i = 0; i < 50; i++)
				{
					for (int j = 0; j < numBullets; j++)
					{
						float mama = bullets[j].model->GetLocalX();

						if (sphere2sphere(lightShip.lightShip[i], bullets[j].model, PLAYERSHIPRADIUS, BULLETRADIUS))
						{
							currentEnemyShipState = Deactivated;
							
						}
						if (currentEnemyShipState == Deactivated)
						{
							lightShip.lightShip[i]->MoveLocalZ(-1000.0f);
							currentEnemyShipState = Active;
						}
					}
				}
				for (int i = 0; i < 30; i++)
				{
					for (int j = 0; j < numBullets; j++)
					{
						if (sphere2sphere(mediumShip.MediumShip[i], bullets[j].model, PLAYERSHIPRADIUS, BULLETRADIUS))
						{
							currentEnemyShipState = Deactivated;
						}
						if (currentEnemyShipState == Deactivated)
						{
							mediumShip.MediumShip[i]->MoveLocalZ(-1000.0f);
							currentEnemyShipState = Active;
						}
					}
				}
				for (int i = 0; i < 20; i++)
				{
					for (int j = 0; j < numBullets; j++)
					{
						if (sphere2sphere(heavyShip.HeavyShip[i], bullets[j].model, PLAYERSHIPRADIUS, BULLETRADIUS))
						{
							currentEnemyShipState = Deactivated;
						}
						if (currentEnemyShipState == Deactivated)
						{
							heavyShip.HeavyShip[i]->MoveLocalZ(-1000.0f);
							currentEnemyShipState = Active;
						}
					}
				}
			}
			if (moveCamTop != true && moveCamBehind != true)
			{
				if (spawnArray[spawnCounter] == 1)
				{
					closeCounter -= frameTime;
					if (closeCounter >= 0)
					{
						lightShip.lightShip[lightCounter]->MoveX(-50 * frameTime);
					}

					MidCounter -= frameTime;
					if (MidCounter >= 0)
					{
						heavyShip.HeavyShip[HeavyCounter]->MoveX(-50 * frameTime);
					}
					if (closeCounter >= 0)
					{
						mediumShip.MediumShip[MedCounter]->MoveX(50 * frameTime);
	
					}
					if (closeCounter < -1 && MidCounter < -1)
					{
						if (MedCounter != 29)
						{
							MedCounter++;
						}
						if (HeavyCounter != 19)
						{
							HeavyCounter++;
						}
						if (lightCounter != 49)
						{
							lightCounter++;
						}
						closeCounter = 2;
						MidCounter = 2.4;
					}
				}
			}


			if (battleMusic.getStatus() == battleMusic.Stopped)
			{
				battleMusic.play();
				
			}

			Lives->Draw("Lives:", 70.0f, 23.0f, kCyan);

			if (Health == Dead)
			{
				gameOver = true;
			}

			

			if (currentPowerUpState == None)
			{

				powerUpStateText <<  "    Bullets: " << numBullets / 2;
				myFont->Draw(powerUpStateText.str(), 15.0f, 70.0f, kWhite); //Game state text is set to go
				powerUpStateText.str(""); // Clear myStream
			}

			if (sphere2sphere(playerShip, placementPowerUp, PLAYERSHIPRADIUS, PLACEMENTPOWERUPRADIUS)) //Collision with powerup
			{
				currentPowerUpState = Speed;
				powerUpMusic.play();
				SpeedPowerUP(myEngine);
			}

			if (currentPowerUpState == Speed)
			{
				powerUpStateText << "   Bullets: " << numBullets / 2;
				myFont->Draw(powerUpStateText.str(), 10.0f, 70.0f, kWhite); //Game state text is set to go
				powerUpStateText.str(""); // Clear myStream

				playerShipSpeed = 75.0f * frameTime;
				placementPowerUp->MoveLocalY(50.0f);
				powerUpTimer -= frameTime;
				if (powerUpTimer <= 0.0f)
				{
					currentPowerUpState = None;
					if (powerDownMusic.getStatus() == powerDownMusic.Stopped)
					{
						powerDownMusic.play();
					}
					powerUpTimer = 5.0f;
					RemoveSpeedPowerUP(myEngine);
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
					placementPowerUp->RotateY(50.0f * frameTime);
					placementPowerUp->MoveZ(50.0f * frameTime);
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
					placementPowerUp->RotateY(50.0f * frameTime);
					placementPowerUp->MoveZ(playerShipSpeed);
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
				placementPowerUp->SetPosition(0.0f, -30.0f, 730.0f);
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
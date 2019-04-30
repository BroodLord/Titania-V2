// Titania-V2.cpp: A program using the TL-Engine
#include <TL-Engine.h>	// TL-Engine include file and namespace
#include <iostream>
#include <memory>
#include <vector>
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

float GLOBAL_Y = -40.0f;

bool moveCamTop = false;
bool moveCamBehind = false;
float frameTime = 0.0f;

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
PlayerShipState currentPlayerShipState2;

EKeyCode camSwitch = Key_1;
EKeyCode MoveUp = Key_W;
EKeyCode MoveRight = Key_D;
EKeyCode MoveDown = Key_S;
EKeyCode MoveLeft = Key_A;
EKeyCode player2MoveUp = Key_Up;
EKeyCode player2MoveRight = Key_Right;
EKeyCode player2MoveDown = Key_Down;
EKeyCode player2MoveLeft = Key_Left;
EKeyCode player2RollRightKey = Mouse_RButton;
EKeyCode player2RollLeftKey = Mouse_LButton;
EKeyCode Exit = Key_Escape;
EKeyCode RollRightKey = Key_E;
EKeyCode RollLeftKey = Key_Q;
EKeyCode kStartKey = Key_Return; //P key used to start the game
EKeyCode p1Shooting = Key_Space;
EKeyCode p2Shooting = Mouse_MButton;

const float bulletSpeed = 6.0f;
const float bulletSize = 0.008f;
const float kCameraMove = 0.10f; // distance for the direction keys x and z axis
const float kMouseWheelMove = 10.0f; // distance for wheel movement z axis
const float kMouseRotation = 0.3f; // distance (in degrees) for rotation of the camera
bool mouseCaptureActive = false; // state of mouse capture
bool tripleBullet = false;
//bool gCoop = false;

float playerFireRate = 0.0f;
float player2FireRate = 0.0f;

deque <CBulletData> bullets;
deque <CBulletData> bullets2;
deque <CBulletData> lightBullets;
deque <CBulletData> mediumBullets;
deque <CBulletData> heavyBullets;
deque <CBulletData> bossBullets;

deque <CBulletData> enemybullets;

int gPlayerScore = 0;
int gPlayer2Score = 0;
deque <unique_ptr <CPowerUp>> SpeedList;
deque <unique_ptr <CPowerUp>> ShieldList;
deque <unique_ptr <CPowerUp>> TripleList;
deque <unique_ptr <CPowerUp>> CurrentlySpawned;

deque <unique_ptr <CShips>> BossShipList;
deque <unique_ptr <CShips>> HeavyShipList;
deque <unique_ptr <CShips>> MediumShipList;
deque <unique_ptr <CShips>> LightShipList;
deque <unique_ptr <CShips>> SpawnedShipList;

deque <unique_ptr <CShips>> RightList;
deque <unique_ptr <CShips>> MiddleList;
deque <unique_ptr <CShips>> LeftList;
deque <unique_ptr <CShips>> DeadList;

float lightFireRate = 0;
float mediumFireRate = 0;
float heavyFireRate = 0;
float bossFireRate = 0;

int enemyShots = 0;
int numBullets = 0;
int numBulletsP2 = 0;
bool gCoop = false;

float FIRST_TOWER = 300.0f;
float SECOND_TOWER = 200.0f;
float THIRD_TOWER = 100.0f;

string gCoopText = "(Disabled)";
vector <LeaderBoardClass*> leaderboard;
LeaderBoardClass* ptr = new LeaderBoardClass;



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
	IMesh* playerShip2Mesh;
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
	IModel* playerShip2;
	IModel* flame;
	IModel* floor;
	IModel* floor2;
	IModel* topDownCamBlock;
	IModel* skyBox;
	IModel* towerNine;
	IModel* towerTwo;
	IModel* Road[40];
	//IModel* speedPowerUp;
	//IModel* shieldPowerUp;
	//IModel* bulletPowerUp;
	IModel* shield;


	//BulletData bullets[maxBullets];

	//BulletData bullets2[maxBullets];

	float matrix[16];

	
	bool barrelRollColdDown = false;
	bool barrelRollColdDown2 = false;

	float startingz = 802.0f;
	float startingZ = -740.0f;
	float startingx = 400.0f;
	float road2MoveX = 1002.0f;


	float countDown = 1.8f;
	float currentX = 0.0f;
	float currentX2 = 0.0f;
	float barrelRollCountDown = 2.0f;
	float barrelRollCountDown2 = 2.0f;
	//float shieldPowerUpTimer = 9.0f;
	//float speedPowerUpTimer = 5.0f;
	//float bulletPowerUpTimer = 5.0f;
	float shieldPowerUpTimer = 0.0f;
	float speedPowerUpTimer = 0.0f;
	float bulletPowerUpTimer = 0.0f;
	float rollingTimer = 0.4f;
	float rollingTimer2 = 0.4f;
	float TimerFloat = 0.0f;

	string name;
    string test2;

	int speedDisplay = 0;
	int shieldDisplay = 0;
	int bulletDisplay = 0;

	bool gameOver = false;
	bool reset = false;
	bool test = false;

	PowerUpState currentSpeedPowerUpState = None;
	PowerUpState currentShieldPowerUpState = None;
	PowerUpState currentBulletPowerUpState = None;
	PowerUpState currentPowerUpState = None;

	//**** Hud Things ****
	AmountLives Health = ThreeLives;
	RemoveLives loseHealth = Pause;

	AmountLives HealthP2 = ThreeLives;
	RemoveLives loseHealthP2 = Pause;

	mainMenuBuffer.loadFromFile("Sound Affects\\mainMusic.wav");
	menuMusic.setBuffer(mainMenuBuffer);
	menuMusic.setVolume(30.0f);
	menuMusic.setLoop(true);

	battleBuffer.loadFromFile("Sound Affects\\Night.ogg");
	battleMusic.setBuffer(battleBuffer);
	battleMusic.setVolume(10.0f);
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
	ISprite* endGame = myEngine->CreateSprite("gameover.png", 1000.f, 10000.f);

	IFont* myFont = myEngine->LoadFont("Arial", 36); //Loading in a font to use in text strings
	IFont* Timer = myEngine->LoadFont("Arial", 36); //Loading in a font to use in text strings
	IFont* deathFont = myEngine->LoadFont("Arial", 50); //Loading in a font to use in text strings
	IFont* NameFont = myEngine->LoadFont("Arial", 50); //Loading in a font to use in text strings
	IFont* preGameFont = myEngine->LoadFont("Arial", 36); //Loading in a font to use in text strings

	ptr->LeaderBoardRead(leaderboard);

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

	/*floor2 = floorMesh->CreateModel(0.0f, -130.0f, -2000.0f);
	floor2->SetSkin("pavement.png");*/


	topDownCamBlock = camBlockMesh->CreateModel(0.0f, GLOBAL_Y -5.0f, 750.0f);

	for (int i = 0; i < 5; i++)
	{

		unique_ptr <CSpeed> speedTemp(new CSpeed(myEngine));

		speedTemp->mModel = speedTemp->mMesh->CreateModel(0.0f, 500.0f, 785.0f);
		speedTemp->mModel->ScaleZ(0.01f);
		speedTemp->mModel->Scale(0.5f);
		speedTemp->mModel->RotateLocalX(90.0f);
		SpeedList.push_back(move(speedTemp));

		unique_ptr <CShield> shieldTemp(new CShield(myEngine));
		shieldTemp->mModel = shieldTemp->mMesh->CreateModel(0.0f, 500.0f, 785.0f);
		shieldTemp->mModel->ScaleZ(0.01f);
		shieldTemp->mModel->Scale(0.5f);
		shieldTemp->mModel->RotateLocalX(-90.0f);
		ShieldList.push_back(move(shieldTemp));

		unique_ptr <CTriple> tripleTemp(new CTriple(myEngine));
		tripleTemp->mModel = tripleTemp->mMesh->CreateModel(0.0f, 500.0f, 785.0f);
		tripleTemp->mModel->ScaleZ(0.01f);
		tripleTemp->mModel->Scale(0.5f);
		tripleTemp->mModel->RotateLocalX(90.0f);
		TripleList.push_back(move(tripleTemp));
	}


	lightFireRate = LightShipList.front()->mFireRate;
	mediumFireRate = MediumShipList.front()->mFireRate;
	heavyFireRate = HeavyShipList.front()->mFireRate;
	bossFireRate = BossShipList.front()->mFireRate;


	for (int i = 0; i < 17; i++)
	{
		Road[i] = camBlockMesh->CreateModel(2.0f, 0.0f, startingz);
		Road[i]->SetSkin("background-1_0.png");
		Road[i]->ScaleX(10.0f);
		Road[i]->ScaleZ(10.0f);
		startingz -= 100.0f;
		Road[i]->AttachToParent(floor);
	}

	/*Road[20] = camBlockMesh->CreateModel(road2MoveX, 0.0f, 802.0f);
	Road[20]->SetSkin("RoadT.jpg");
	Road[20]->ScaleX(10.0f);
	Road[20]->ScaleZ(10.0f);
	Road[20]->RotateLocalY(-90.0f);
	road2MoveX -= 100.0f;
	Road[20]->AttachToParent(floor2);*/

	for (int i = 21; i < 40; i++)
	{
		Road[i] = camBlockMesh->CreateModel(road2MoveX, 0.2f, -852.0f);
		Road[i]->SetSkin("background-1_0.png");
		Road[i]->ScaleX(10.0f);
		Road[i]->ScaleZ(10.0f);
		Road[i]->RotateLocalY(90.0f);
		road2MoveX -= 100.0f;
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
	playerShip = playerShipMesh->CreateModel(0.0f, GLOBAL_Y, 785.0f);
	playerShip2Mesh = myEngine->LoadMesh("gunShip01.x");
	playerShip2 = playerShip2Mesh->CreateModel(-10000.0f, -10030.0f, -100785.0f);

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

	for (int i = 0; i < 10; i++)
	{
		
		for (int j = 0; j < 2; j++)
		{
			towerNine = towerNineMesh->CreateModel(FIRST_TOWER, 0.0f, startingZ);
			towerNine->ScaleY(0.4);
			towerNine->AttachToParent(floor);
			towerTwo = towerTwoMesh->CreateModel(SECOND_TOWER, 0.0f, startingZ);
			towerTwo->ScaleY(0.8);
			towerTwo->AttachToParent(floor);
			towerNine = towerNineMesh->CreateModel(THIRD_TOWER, 0.0f, startingZ);
			towerNine->ScaleY(0.4);
			towerNine->AttachToParent(floor);
			FIRST_TOWER = -FIRST_TOWER;
			SECOND_TOWER = -SECOND_TOWER;
			THIRD_TOWER = -THIRD_TOWER;

		}		
		startingZ = startingZ + 100.0f;

		for (int j = 0; j < 2; j++)
		{
			towerTwo = towerTwoMesh->CreateModel(FIRST_TOWER, 0.0f, startingZ);
			towerTwo->ScaleY(0.8);
			towerTwo->AttachToParent(floor);
			towerNine = towerNineMesh->CreateModel(SECOND_TOWER, 0.0f, startingZ);
			towerNine->ScaleY(0.4);
			towerNine->AttachToParent(floor);
			towerTwo = towerTwoMesh->CreateModel(THIRD_TOWER, 0.0f, startingZ);
			towerTwo->ScaleY(0.8);
			towerTwo->AttachToParent(floor);
			FIRST_TOWER = -FIRST_TOWER;
			SECOND_TOWER = -SECOND_TOWER;
			THIRD_TOWER = -THIRD_TOWER;

		}
		startingZ = startingZ + 100.0f;
	}

	//towerNine = towerNineMesh->CreateModel(0.0f, 0.2f, -952.0f);
	//towerNine->ScaleY(0.4);
	//towerNine->AttachToParent(floor);


	startingZ = -840.0f;

	/*for (int i = 0; i < 10; i++)
	{

		for (int j = 0; j < 2; j++)
		{
			towerNine = towerNineMesh->CreateModel(FIRST_TOWER, 0.0f, startingZ);
			towerNine->ScaleY(0.4);
			towerNine->AttachToParent(floor2);
			towerTwo = towerTwoMesh->CreateModel(SECOND_TOWER, 0.0f, startingZ);
			towerTwo->ScaleY(0.8);
			towerTwo->AttachToParent(floor2);
			towerNine = towerNineMesh->CreateModel(THIRD_TOWER, 0.0f, startingZ);
			towerNine->ScaleY(0.4);
			towerNine->AttachToParent(floor2);
			FIRST_TOWER = -FIRST_TOWER;
			SECOND_TOWER = -SECOND_TOWER;
			THIRD_TOWER = -THIRD_TOWER;

		}
		startingZ = startingZ + 100.0f;

		for (int j = 0; j < 2; j++)
		{
			towerTwo = towerTwoMesh->CreateModel(FIRST_TOWER, 0.0f, startingZ);
			towerTwo->ScaleY(0.8);
			towerTwo->AttachToParent(floor2);
			towerNine = towerNineMesh->CreateModel(SECOND_TOWER, 0.0f, startingZ);
			towerNine->ScaleY(0.4);
			towerNine->AttachToParent(floor2);
			towerTwo = towerTwoMesh->CreateModel(THIRD_TOWER, 0.0f, startingZ);
			towerTwo->ScaleY(0.8);
			towerTwo->AttachToParent(floor2);
			FIRST_TOWER = -FIRST_TOWER;
			SECOND_TOWER = -SECOND_TOWER;
			THIRD_TOWER = -THIRD_TOWER;

		}
		startingZ = startingZ + 100.0f;
	}*/

	bulletMesh = myEngine->LoadMesh("Flare.x");

	skyBoxMesh = myEngine->LoadMesh("Skybox 01.x");
	skyBox = skyBoxMesh->CreateModel(0.0f, -1050.0f, 0.0f);
	skyBox->Scale(1.5f);

	//fixedCamBlock->AttachToParent(playerShip);
	eCameraPos cameraPos;
	GameState currentGameState = MainMenu;
	cameraPos = behind;

	

	//NoPowerUP(myEngine);
	SpawnSprites(myEngine);

	// The main game loop, repeat until engine is stopped
	myEngine->Timer();
	while (myEngine->IsRunning())
	{
		myEngine->DrawScene();
		currentX = playerShip->GetLocalX();
		currentX2 = playerShip2->GetLocalX();
		frameTime = myEngine->Timer();
		// Draw the scene

		SpawnEnemies(numBullets, bullets, bulletMesh, myEngine);
		stringstream powerUpStateText; //Text altered to present gamestate
		stringstream speedText; //Text altered to present gamestate
		stringstream shieldText; //Text altered to present gamestate
		stringstream tripleText; //Text altered to present gamestate

		stringstream powerUpStateTextP2; //Text altered to present gamestate
		stringstream speedTextP2; //Text altered to present gamestate
		stringstream shieldTextP2; //Text altered to present gamestate
		stringstream tripleTextP2; //Text altered to present gamestate

		string kPowerUpStateText = "PowerUp: ";
		string kNoneText = "None";
		string kSpeedText = "Speed";

		float playerShipSpeed = 50.0f * frameTime; // Player speed
		float floorResert = floor->GetLocalZ();

		//POWERUPS - DANNY LOOK AT THIS
		stringstream preGameText;
		stringstream LeaderBoardText;
		stringstream TimerStream;
		stringstream EndScore;
		stringstream nameStream;
		TimerStream.precision(3);

		string kPlayText = "Press Enter to Start";
		string kCoopText = "Press Space to Toggle Coop:";
		string kLeaderBoard = "Press L to display leaderboard.";
		string kQuitText = "Press Esc to Quit";


		if (currentGameState == MainMenu)
		{
			endGame->SetPosition(10000, 10000);
			battleMusic.stop();
			if (menuMusic.getStatus() == menuMusic.Stopped)
			{
				menuMusic.play();
			}
			menuMusic.setLoop(true);
			backGround->SetPosition(0, 0);
			playerCamera->LookAt(topDownCamBlock);
			preGameText << kPlayText << "\n" << kCoopText << " " << gCoopText << "\n" << kLeaderBoard << "\n" << kQuitText;
			preGameFont->Draw(preGameText.str(), 400.0f, 300.0f, kWhite); //Game state text is set to go
			preGameText.str(""); // Clear myStream

			if (myEngine->KeyHeld(Key_L))
			{
				float height = 450.0f;
				for (auto it = leaderboard.begin(); it != leaderboard.end(); it++)
				{
					string name = (*it)->name;
					string score = to_string((*it)->score);
					string time = to_string((*it)->time);
					string place = name + " " + score + " " + time;
					LeaderBoardText << place << endl;
					preGameFont->Draw(LeaderBoardText.str(), 400.0f, height, kWhite);
					LeaderBoardText.str("");
					height += 50.0f;
				}
			}


			if (myEngine->KeyHit(Key_Space))
			{
				if (gCoop == false)
				{
					gCoop = true;
					gCoopText = "(Enabled)";
					playerShip2->SetPosition(0.0f, GLOBAL_Y, 785.0f);
					ISprite* myUI2 = myEngine->CreateSprite("Player2Backdrop.png", 1405.0f, -15.0f, 0.9f); //Simple box used as UI to make text stand out for P2
					SpawnSpritesP2(myEngine);
					Lives->Draw("P2 Lives:", 1480.0f, 23.0f, kCyan);
				}
				else
				{
					gCoop = false;
					gCoopText = "(Disabled)";
					playerShip2->SetPosition(0.0f, -300000.0f, 785.0f);
				}

				

			}

			if (myEngine->KeyHit(kStartKey))
			{
				backGround->SetPosition(100000, 100000);
				currentGameState = Play;
				fullHealth(myEngine, Health);
				ISprite* myUI = myEngine->CreateSprite("backdrop2.png", -30.0f, -15.0f, 0.9f); //Simple box used as UI to make text stand out
				if (gCoop == true)
				{
					fullHealthP2(myEngine, HealthP2);
				}

			}
		}



		if (currentGameState == Play && gameOver == false)
		{
			TimerFloat = TimerFloat += frameTime;
			TimerStream << "Timer: " << TimerFloat;
			Timer->Draw(TimerStream.str(), 230.0f, 70.0f, kWhite); //Game state text is set to go)
			TimerStream.str("");
			if (numBullets <= 0)
			{
				numBullets = 0;
			}
			if (numBulletsP2 <= 0)
			{
				numBulletsP2 = 0;
			}

			if (gCoop)
			{
				Lives->Draw("P2 Lives:", 1480.0f, 23.0f, kGreen);
				if (HealthP2 == Dead)
				{
					playerShip2->SetPosition(0.0f, -300000.0f, 785.0f);
					//HealthP2 = ThreeLivesP2;
				}
			}


			if (test == false)
			{
				if (test == false)
				{
					countDown -= frameTime;
					playerCamera->LookAt(topDownCamBlock);
					playerCamera->MoveLocalY(-50.0 * frameTime);
					playerCamera->MoveLocalZ(5.0 * frameTime);
					if (reset != true)
					{
						if (cameraPos == behind)
						{
							for (auto it = CurrentlySpawned.begin(); it != CurrentlySpawned.end(); it++)
							{
								(*it)->mModel->ResetOrientation();							
							}

							for (auto it = SpeedList.begin(); it != SpeedList.end(); it++)
							{
								(*it)->mModel->ResetOrientation();							
							}

							for (auto it = ShieldList.begin(); it != ShieldList.end(); it++)
							{
								(*it)->mModel->ResetOrientation();					
							}

							for (auto it = TripleList.begin(); it != TripleList.end(); it++)
							{
								(*it)->mModel->ResetOrientation();
							}
						}
						if (cameraPos == topDown)
						{
							//for (auto it = CurrentlySpawned.begin(); it != CurrentlySpawned.end(); it++)
							//{
							//	//(*it)->mModel->ResetOrientation();
							//	(*it)->mModel->RotateLocalX(-50.0f * frameTime);
							//}
							//
							//for (auto it = SpeedList.begin(); it != SpeedList.end(); it++)
							//{
							//	//(*it)->mModel->ResetOrientation();
							//	(*it)->mModel->RotateLocalX(-50.0f * frameTime);
							//}
							//
							//for (auto it = ShieldList.begin(); it != ShieldList.end(); it++)
							//{
							//	//(*it)->mModel->ResetOrientation();
							//	(*it)->mModel->RotateLocalX(-50.0f * frameTime);
							//}
							//
							//for (auto it = TripleList.begin(); it != TripleList.end(); it++)
							//{
							//	//(*it)->mModel->ResetOrientation();
							//	(*it)->mModel->RotateLocalX(-50.0f * frameTime);
							//}
						}

					}
					else
					{
						cout << " ";
					}
					if (countDown <= 0)
					{
						//playerCamera->SetLocalPosition(0.0f, 49.0f, 771.0f);
						test = true;
						countDown = 1.8;
						cameraPos = behind;
					}
				}
			}

			
				if (Health != Dead)
				{
					if (!moveCamBehind && !moveCamTop)
					{
						Shooting(myEngine, playerShip, bulletMesh, playerShipSpeed, shootingSound, p1Shooting, playerFireRate);
						if (gCoop)
						{
							Shooting(myEngine, playerShip2, bulletMesh, playerShipSpeed, shootingSound, p2Shooting, player2FireRate);
						}
						ActivateEnemies(myEngine, bulletMesh);
						MoveBullet(bulletMesh, playerShip);
						playerFireRate -= frameTime;
						player2FireRate -= frameTime;
					}

				



				auto bt = enemybullets.begin(); // set p to the beginning of the loop
				while (bt != enemybullets.end()) // while not at the end of the loop
				{
					bool bulletHit = false;

					auto jt = bullets.begin(); // set p to the beginning of the loop
					while (jt != bullets.end()) // while not at the end of the loop
					{
						if (sphere2sphere(bt->model, jt->model, bt->mRadius, BULLETRADIUS) && !bt->mImmune)
						{
							bulletMesh->RemoveModel(jt->model);
							Erase(bullets, jt->model);
							numBullets--;
							bt->mHealth--;
							if (bt->mHealth <= 0)
							{

								bulletMesh->RemoveModel(bt->model);
								Erase(enemybullets, bt->model);

								enemyShots--;

								bulletHit = true;

							}
							break;
						}
						jt++;
					}
					if (bulletHit)
					{
						bulletHit = false;
						break;
					}
					bt++;
				}

				auto kt = enemybullets.begin();
				while (kt != enemybullets.end())
				{
					if (sphere2sphere(playerShip, kt->model, PLAYERSHIPRADIUS, kt->mRadius))
					{
						bulletMesh->RemoveModel(kt->model);
						Erase(enemybullets, kt->model);
						enemyShots--;
						loseHealth = RemoveHeart;

						if (loseHealth == RemoveHeart)
						{
							removeHeart(myEngine, Health);
							loseHealth = Pause;
						}
						break;
					}

					if (sphere2sphere(playerShip2, kt->model, PLAYERSHIPRADIUS, kt->mRadius))
					{
						bulletMesh->RemoveModel(kt->model);
						Erase(enemybullets, kt->model);
						enemyShots--;
						loseHealthP2 = RemoveHeart;

						if (loseHealthP2 == RemoveHeart)
						{
							removeHeartP2(myEngine, HealthP2);
							loseHealthP2 = Pause;
						}
						break;
					}

					kt++;
				}

				menuMusic.stop();

				if (!moveCamBehind && !moveCamTop)
				{
					lightFireRate -= frameTime;
					mediumFireRate -= frameTime;
					heavyFireRate -= frameTime;
					bossFireRate -= frameTime;
				}

				//myEngine->StartMouseCapture();

				if (myEngine->KeyHit(Key_L))
				{
					RightList.clear();
					MiddleList.clear();
					LeftList.clear();
				}


				if (battleMusic.getStatus() == battleMusic.Stopped)
				{
					battleMusic.play();

				}

				Lives->Draw("Lives:", 70.0f, 23.0f, kGreen);
				

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

				if (gCoop)
				{
					//**** P2 Hud Stuff ****

					powerUpStateTextP2 << "    P2 Bullets: " << numBulletsP2;
					myFont->Draw(powerUpStateTextP2.str(), 1415.0f, 70.0f, kWhite); //Game state text is set to go
					powerUpStateTextP2.str(""); // Clear myStream

					powerUpStateTextP2 << "    P2 Score: " << gPlayer2Score;
					myFont->Draw(powerUpStateTextP2.str(), 1415.0f, 100.0f, kWhite); //Game state text is set to go
					powerUpStateTextP2.str(""); // Clear myStream


					tripleText << bulletDisplay;
					myFont->Draw(tripleText.str(), 1668.95f, 155.0f, kWhite); //Game state text is set to go
					tripleText.str(""); // Clear myStream

					shieldText << shieldDisplay;
					myFont->Draw(shieldText.str(), 1603.0f, 155.0f, kWhite); //Game state text is set to go
					shieldText.str(""); // Clear myStream

					speedText << speedDisplay;
					myFont->Draw(speedText.str(), 1837.5f, 155.0f, kWhite); //Game state text is set to go
					speedText.str(""); // Clear myStream
				}

				if (!moveCamBehind && !moveCamTop)
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
							for (auto bulletIT = bullets.begin(); bulletIT != bullets.end(); bulletIT++)
							{
								bulletIT->zVel = bulletIT->zVel + 75.0f * frameTime;
							}

							speedPowerUpTimer -= frameTime;
							if (powerDownMusic.getStatus() == powerDownMusic.Stopped)
							{
								powerDownMusic.play();
							}
						}
						else if (speedPowerUpTimer <= 0.0f)
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

						shield->SetY(GLOBAL_Y);
						shield->RotateLocalY(250.0f * frameTime);
						for (auto i = enemybullets.begin(); i != enemybullets.end(); i++)
						{
							if (sphere2sphere(playerShip, (*i).model, 8.0f, i->mRadius))
							{
								bulletMesh->RemoveModel((*i).model);
								Erase(enemybullets, (*i).model);
								enemyShots--;
								break;
							}
						}
						if (shieldPowerUpTimer > 0.0f)
						{
							shieldPowerUpTimer -= frameTime;
							if (powerDownMusic.getStatus() == powerDownMusic.Stopped)
							{
								powerDownMusic.play();
							}
						}
						else if (shieldPowerUpTimer <= 0.0f)
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
						else if (bulletPowerUpTimer <= 0.0f)
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


				if (!moveCamBehind && !moveCamTop)
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
						if (barrelRollColdDown2 == false)
						{
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
						if (gCoop == true)
						{

							if (currentPlayerShipState2 == Normal)
							{
								if (myEngine->KeyHit(player2RollRightKey))
								{
									currentPlayerShipState2 = RollingRight;
								}

								if (myEngine->KeyHit(player2RollLeftKey))
								{
									currentPlayerShipState2 = RollingLeft;
								}
							}

							if (currentPlayerShipState2 == RollingRight)
							{
								rollingTimer2 -= frameTime;
								if (rollingTimer2 > 0)
								{
									playerShip2->RotateZ(900.0f * frameTime);
									playerShip2->MoveX(-playerShipSpeed);
								}
								if (rollingTimer2 <= 0)
								{
									rollingTimer2 = 0.4f;
									currentPlayerShipState2 = Normal;
									barrelRollColdDown2 = true;
									playerShip2->ResetOrientation();
									//player invunerable
								}
							}

							if (currentPlayerShipState2 == RollingLeft)
							{
								rollingTimer2 -= frameTime;
								if (rollingTimer2 > 0)
								{
									playerShip2->RotateZ(-900.0f * frameTime);
									playerShip2->MoveX(50.0f * frameTime);
								}
								if (rollingTimer2 <= 0)
								{
									rollingTimer2 = 0.4f;
									currentPlayerShipState2 = Normal;
									barrelRollColdDown2 = true;
									playerShip->ResetOrientation();
									//player invunerable
								}
							}
						}
					}

					//**** Health ****



				}

				if (currentX < -27.0f)
				{
					playerShip->MoveX(playerShipSpeed);
					playerShip->SetX(-27.0f);
				}
				if (currentX > 27.0f)
				{
					playerShip->MoveX(-playerShipSpeed);
					playerShip->SetX(27.0f);
				}
				if (gCoop == true)
				{
					if (currentX2 < -27.0f)
					{
						playerShip2->MoveX(playerShipSpeed);
						playerShip2->SetX(-27.0f);
					}
					if (currentX2 > 27.0f)
					{
						playerShip2->MoveX(-playerShipSpeed);
						playerShip2->SetX(27.0f);
					}
				}

				/* Camera Switching */
				switch (cameraPos)
				{
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
						if (gCoop == true)
						{
							if (currentPlayerShipState2 != RollingLeft && currentPlayerShipState != RollingRight)
							{
								if (myEngine->KeyHeld(player2MoveRight))
								{
									playerShip2->MoveX(-playerShipSpeed);
								}
								if (myEngine->KeyHeld(player2MoveLeft))
								{
									playerShip2->MoveX(playerShipSpeed);
								}
							}
						}
						if (currentPlayerShipState != RollingLeft && currentPlayerShipState != RollingRight)
						{
							

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
						if (gCoop == true)
						{
							if (currentPlayerShipState2 != RollingLeft && currentPlayerShipState != RollingRight)
							{
								if (myEngine->KeyHeld(player2MoveRight))
								{
									playerShip2->MoveX(-playerShipSpeed);
								}
								if (myEngine->KeyHeld(player2MoveLeft))
								{
									playerShip2->MoveX(playerShipSpeed);
								}
							}
						}
						if (currentPlayerShipState != RollingLeft && currentPlayerShipState != RollingRight)
						{
						

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
				if (barrelRollColdDown2 == true)
				{
					barrelRollCountDown2 -= frameTime;
					if (barrelRollCountDown2 <= 0)
					{
						barrelRollColdDown2 = false;
						barrelRollCountDown2 = 2.0f;
					}
				}
			}
		}


		if (gameOver == true && Health == Dead)
		{
			endGame->SetPosition(0, 0);
			int totalScorce = gPlayerScore;
			EndScore << "Scorce: " << gPlayerScore << "\n" << "Time: " << TimerFloat << "\n" << "Total Score: " << totalScorce;
			deathFont->Draw(EndScore.str(), 800.0f, 300.0f, kWhite);
			preGameText << "Enter you name here!";
			deathFont->Draw(preGameText.str(), 700.0f, 500.0f, kWhite);

			static int nameCounter = 0;

			if (myEngine->AnyKeyHit())
			{

					test2 = keyEnter(myEngine);
					if (nameCounter < 8)
					{
						name = name += test2;
						nameCounter++;
					}

			}
			if (myEngine->KeyHit(Key_Back))
			{
				if (nameCounter > 0)
				{
					nameCounter -= 2;
				}
				if (nameCounter > 0)
				{
					string newname;
					for (int i = 0; i < name.size() - 2; i++)
					{
						newname += name[i];
					}
					name = newname;
				}
				//else
				//{
				//	name = "";
				//}
			}
			nameStream << name;
			NameFont->Draw(nameStream.str(), 700.0f, 600.0f, kWhite);

			if (myEngine->KeyHit(Key_Return))
			{
				nameCounter = 0;
				ptr->setter(name, totalScorce, TimerFloat);
				leaderboard.push_back(ptr);
				ptr->LeaderBoardWrite(leaderboard);
				name = "";
				nameStream.str("");
				preGameText.str("");
				EndScore.str("");
				TimerFloat = 0.0f;
				speedPowerUpTimer = 0.0f;
				shieldPowerUpTimer = 0.0f;
				bulletPowerUpTimer = 0.0f;
				currentGameState = MainMenu;
				playerCamera->SetLocalPosition(0.0f, 49.0f, 771.0f);
				//cameraPos = behind;
				Health = ThreeLives;
				HealthP2 = ThreeLives;
				gameOver = false;
				test = false;
				reset = true;
				for (auto PlayerShots = bullets.begin(); PlayerShots != bullets.end(); PlayerShots++)
				{
					PlayerShots->life = 0;
				}
				for (auto PlayerShots2 = bullets2.begin(); PlayerShots2 != bullets2.end(); PlayerShots2++)
				{
					PlayerShots2->life = 0;
				}
				for (auto enemyShots = enemybullets.begin(); enemyShots != enemybullets.end(); enemyShots++)
				{
					enemyShots->life = 0;
				}
				LightShipList.clear();
				MediumShipList.clear();
				HeavyShipList.clear();
				BossShipList.clear();
				RightList.front()->mShipModel->SetLocalPosition(120.0f, GLOBAL_Y, 700.0f);
				RightList.clear();
				MiddleList.front()->mShipModel->SetLocalPosition(120.0f, GLOBAL_Y, 700.0f);
				MiddleList.clear();
				LeftList.front()->mShipModel->SetLocalPosition(120.0f, GLOBAL_Y, 700.0f);
				LeftList.clear();
				resetCracks(myEngine);
				CreateEnemies(myEngine);
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

		// Pause, then exit
		if (myEngine->KeyHit(Exit))
		{
			if (currentGameState == MainMenu)
			{
				myEngine->Stop();
			}
			else
			{
				currentGameState = MainMenu;
			}
		}
	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}
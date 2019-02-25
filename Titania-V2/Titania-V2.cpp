// Titania-V2.cpp: A program using the TL-Engine
#include <TL-Engine.h>	// TL-Engine include file and namespace
#include <iostream>
#include <sstream>
#include "Defs.h"
using namespace tle;

enum PowerUpState { None, Speed };
enum PlayerShipState { Normal, RollingLeft, RollingRight};

EKeyCode camSwitch = Key_1;
EKeyCode MoveUp = Key_W;
EKeyCode MoveRight = Key_D;
EKeyCode MoveDown = Key_S;
EKeyCode MoveLeft = Key_A;
EKeyCode Exit = Key_Escape;
EKeyCode RollRightKey = Key_E;
EKeyCode RollLeftKey = Key_Q;

const float PLAYERSHIPRADIUS = 2.0f;
const float PLACEMENTPOWERUPRADIUS = 2.0f;

void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine(kTLX);
	myEngine->StartWindowed();

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder("C:\\ProgramData\\TL-Engine\\Media");
	myEngine->AddMediaFolder("D:\\DKavanagh2\\Documents\\GitHub\\Titania-V2\\Assets\\Vehicles\\Sci-Fi Gunships\\Sci-Fi_Gunships_collection");
	myEngine->AddMediaFolder("D:\\DKavanagh2\\\Documents\\GitHub\\Titania-V2\\Assets\\Model Packs\\Architecture\\SciFi");
	myEngine->AddMediaFolder("D:\\DKavanagh2\\\Documents\\GitHub\\Titania-V2\\Assets\\SkyBox");
	myEngine->AddMediaFolder("D:\\DKavanagh2\\\Documents\\GitHub\\Titania-V2\\Assets\\Model Packs\\Architecture\\Modern\\skyscraper04");
	myEngine->AddMediaFolder("D:\\DKavanagh2\\\Documents\\GitHub\\Titania-V2\\Assets\\Model Packs\\Weapons\\Scifi\\megagatt");

	/**** Set up your scene here ****/
	ICamera* playerCamera = myEngine->CreateCamera(kManual);

	//** Meshes ** 
	IMesh* playerShipMesh;
	IMesh* floorMesh;
	IMesh* camBlockMesh;
	IMesh* skyBoxMesh;
	IMesh* towerMesh;
	IMesh* powerUpMesh;
	

	//** Models
	IModel* playerShip;
	IModel* floor;
	IModel* topDownCamBlock;
	IModel* skyBox;
	IModel* tower[20];
	IModel* Road[25];
	IModel* placementPowerUp;

	bool moveCamTop = false;
	bool barrelRollColdDown = false;
	bool moveCamBehind = false;

	float startingz = 802.0f;
	float startingZ = -840.0f;
	float startingx = 400.0f;
	float countDown = 4.0f;
	float barrelRollCountDown = 2.0f;
	float powerUpTimer = 5.0f;
	float rollingTimer = 0.2f;

	PowerUpState currentPowerUpState = None;
	PlayerShipState currentPlayerShipState = Normal;

	IFont* myFont = myEngine->LoadFont("Arial", 36); //Loading in a font to use in text strings
	ISprite* myUI = myEngine->CreateSprite("ui_backdrop.jpg", 280.0f, 400.0f); //Simple box used as UI to make text stand out

	/* QUICK NOTE, Because of the camera being flipped the pluses and minus are swaped. (going left is pos)(going right is negative) */
	camBlockMesh = myEngine->LoadMesh("cube.x");

	topDownCamBlock = camBlockMesh->CreateModel(0.0f, -35.0f, 750.0f);
	for (int i = 0; i < 18; i++)
	{
		Road[i] = camBlockMesh->CreateModel(2.0f, -132.0f, startingz);
		Road[i]->SetSkin("background-1_0.png");
		Road[i]->ScaleX(10.0f);
		Road[i]->ScaleZ(10.0f);
		startingz -= 100.0f;
	}
	topDownCamBlock->Scale(0.01f);

	floorMesh = myEngine->LoadMesh("floor.x");
	floor = floorMesh->CreateModel(0.0f, -130.0f, 0.0f);
	floor->SetSkin("pavement.png");

	powerUpMesh = myEngine->LoadMesh("megagatt.x");
	placementPowerUp = powerUpMesh->CreateModel(0.0f, -30.0f, 730.0f);
	placementPowerUp->Scale(10.0f);

	playerShipMesh = myEngine->LoadMesh("gunShip.x");
	playerShip = playerShipMesh->CreateModel(0.0f, -30.0f, 785.0f);

	playerCamera->SetLocalPosition(0.0f, 49.0f, 771.0f);
	playerCamera->RotateLocalX(90.0f);
	playerCamera->RotateLocalZ(180.0f);

	skyBoxMesh = myEngine->LoadMesh("Skybox 01.x");
	skyBox = skyBoxMesh->CreateModel(0.0f, -1050.0f, 0.0f);

	towerMesh = myEngine->LoadMesh("skyscraper04.x");
	int count = 0;
	for (int i = 0; i < 12; i++)
	{
		if (count == 3)
		{
		startingx -= 100.0f;
		startingx -= 100;
		}
		else
		{
			startingx -= 100;
		}
		tower[i] = towerMesh->CreateModel(startingx, -140.0f, startingZ);
		count++;
		if (count == 6)
		{
			count = 0;
			startingZ += 100.0f;
			startingx = 400.0f;
		}
		
	}
	//fixedCamBlock->AttachToParent(playerShip);
	eCameraPos cameraPos;
	cameraPos = topDown;


	// The main game loop, repeat until engine is stopped
	myEngine->Timer();
	while (myEngine->IsRunning())
	{
		float frameTime = myEngine->Timer();
		// Draw the scene
		myEngine->DrawScene();

		stringstream powerUpStateText; //Text altered to present gamestate
		string kPowerUpStateText = "PowerUp: ";
		string kNoneText = "None";
		string kSpeedText = "Speed";

		float playerShipSpeed = 50.0f * frameTime; // Player speed

		//POWERUPS - DANNY LOOK AT THIS
		placementPowerUp->RotateY(50.0f * frameTime);

		if (currentPowerUpState == None)
		{
			powerUpStateText << kPowerUpStateText << kNoneText;
			myFont->Draw(powerUpStateText.str(), 300.0f, 670.0f); //Game state text is set to go
			powerUpStateText.str(""); // Clear myStream
		}

		if (sphere2sphere(playerShip->GetX(), playerShip->GetZ(), PLAYERSHIPRADIUS, placementPowerUp->GetX(), placementPowerUp->GetZ(), PLACEMENTPOWERUPRADIUS)) //Collision with powerup
		{
			currentPowerUpState = Speed;
		}

		if (currentPowerUpState == Speed)
		{
			powerUpStateText << kPowerUpStateText << kSpeedText;
			myFont->Draw(powerUpStateText.str(), 300.0f, 670.0f); //Game state text is set to go
			powerUpStateText.str(""); // Clear myStream

			playerShipSpeed = 75.0f * frameTime;
			placementPowerUp->MoveZ(0.5f);
			powerUpTimer -= frameTime;
			if (powerUpTimer <= 0.0f)
			{
				currentPowerUpState = None;
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
						playerShip->RotateZ(1810.0f * frameTime);
						playerShip->MoveX(-100.0f * frameTime);
					}
					if (rollingTimer <= 0)
					{
						rollingTimer = 0.2f;
						currentPlayerShipState = Normal;
						barrelRollColdDown = true;
						//player invunerable
					}
				}

				if (currentPlayerShipState == RollingLeft)
				{
					rollingTimer -= frameTime;
					if (rollingTimer > 0)
					{
						playerShip->RotateZ(-1810.0f * frameTime);
						playerShip->MoveX(100.0f * frameTime);
					}
					if (rollingTimer <= 0)
					{
						rollingTimer = 0.2f;
						currentPlayerShipState = Normal;
						barrelRollColdDown = true;
						//player invunerable
					}
				}
			}
		}


		/* Camera Switching */
			switch (cameraPos)
			{
			case behind:
			{
				if (moveCamBehind != true)
				{
					if (myEngine->KeyHeld(MoveRight))
					{
						playerShip->MoveX(-50.0f * frameTime);
					}
					if (myEngine->KeyHeld(MoveLeft))
					{
						playerShip->MoveX(50.0f * frameTime);
					}
				}
				if (moveCamBehind != true)
				{
					if (myEngine->KeyHit(camSwitch))
					{
						moveCamBehind = true;
						playerCamera->SetPosition(0.0f, -20.0f, 815.0f);
					}
				}
				if (moveCamBehind == true)
				{
					playerCamera->LookAt(topDownCamBlock);
					countDown -= frameTime;
					playerCamera->MoveLocalY(21.0 * frameTime);
					playerCamera->MoveLocalZ(-5.0 * frameTime);
					if (countDown <= 0)
					{
						moveCamBehind = false;
						countDown = 4;
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
					if (myEngine->KeyHeld(MoveUp))
					{
						playerShip->MoveZ(-playerShipSpeed);
					}
					if (myEngine->KeyHeld(MoveDown))
					{
						playerShip->MoveZ(playerShipSpeed);
					}
					if (myEngine->KeyHeld(MoveRight))
					{
						playerShip->MoveX(-playerShipSpeed);
					}
					if (myEngine->KeyHeld(MoveLeft))
					{
						playerShip->MoveX(playerShipSpeed);
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
					playerCamera->MoveLocalY(-21.0 * frameTime);
					playerCamera->MoveLocalZ(5.0 * frameTime);
					if (countDown <= 0)
					{
						moveCamTop = false;
						countDown = 4;
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
		/******************************/

		/**** Update your scene each frame here ****/

		// Exit the game when running
		if (myEngine->KeyHit(Exit))
		{
			myEngine->Stop();
		}

	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}
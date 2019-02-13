// Titania-V2.cpp: A program using the TL-Engine
#include <TL-Engine.h>	// TL-Engine include file and namespace
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include "Defs.h"
using namespace tle;

struct particle
{
	IModel* flame;
	float moveVector[3];
};
particle flameParticle;


enum PowerUpState { None, Speed };

EKeyCode camSwitch = Key_1;
EKeyCode MoveUp = Key_W;
EKeyCode MoveRight = Key_D;
EKeyCode MoveDown = Key_S;
EKeyCode MoveLeft = Key_A;
EKeyCode Exit = Key_Escape;

const float PLAYERSHIPRADIUS = 2.0f;
const float PLACEMENTPOWERUPRADIUS = 2.0f;

void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine(kTLX);
	myEngine->StartWindowed();

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder("C:\\ProgramData\\TL-Engine\\Media");
	myEngine->AddMediaFolder("D:\\DKavanagh2\\Documents\\GitHub\\Titania-V2\\Assest\\Sprites\\Fire\\Fire10\\10color");
	myEngine->AddMediaFolder("D:\\DKavanagh2\\Documents\\GitHub\\Titania-V2\\Assest\\Vehicles\\Sci-Fi Gunships\\Sci-Fi_Gunships_collection");
	myEngine->AddMediaFolder("D:\\DKavanagh2\\Documents\\GitHub\\Titania-V2\\Assest\\Model Packs\\Architecture\\SciFi");
	myEngine->AddMediaFolder("D:\\DKavanagh2\\Documents\\GitHub\\Titania-V2\\Assest\\SkyBox");
	myEngine->AddMediaFolder("D:\\DKavanagh2\\Documents\\GitHub\\Titania-V2\\Assest\\Model Packs\\Architecture\\Modern\\skyscraper04");
	myEngine->AddMediaFolder("D:\\DKavanagh2\\Documents\\GitHub\\Titania-V2\\Assest\\Model Packs\\Weapons\\Scifi\\megagatt");

	/**** Set up your scene here ****/
	ICamera* playerCamera = myEngine->CreateCamera(kManual);

	//** Meshes ** 
	IMesh* playerShipMesh;
	IMesh* floorMesh;
	IMesh* camBlockMesh;
	IMesh* skyBoxMesh;
	IMesh* towerMesh;
	IMesh* powerUpMesh;
	IMesh* flameMesh;

	//** Models
	IModel* flame;
	IModel* playerShip;
	IModel* floor;
	IModel* topDownCamBlock;
	IModel* skyBox;
	IModel* tower;
	IModel* Road[20];
	IModel* placementPowerUp;

	float startingz = 802.0f;
	float countDown = 4.0f;
	float powerUpTimer = 5.0f;
	float particleV = 70.0f;
	float particleG = 50.0f;
	float particleCount = 3.0f;


	PowerUpState currentPowerUpState = None;

	IFont* myFont = myEngine->LoadFont("Arial", 36); //Loading in a font to use in text strings
	ISprite* myUI = myEngine->CreateSprite("ui_backdrop.jpg", 280.0f, 660.0f); //Simple box used as UI to make text stand out

	/* QUICK NOTE, Because of the camera being flipped the pluses and minus are swaped. (going left is pos)(going right is negative) */
	camBlockMesh = myEngine->LoadMesh("cube.x");

	topDownCamBlock = camBlockMesh->CreateModel(0.0f, -35.0f, 750.0f);
	for (int i = 0; i < 20; i++)
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
	floor->SetSkin("pavement.jpg");

	powerUpMesh = myEngine->LoadMesh("megagatt.x");
	placementPowerUp = powerUpMesh->CreateModel(0.0f, -30.0f, 730.0f);
	placementPowerUp->Scale(10.0f);

	playerShipMesh = myEngine->LoadMesh("gunShip.x");
	playerShip = playerShipMesh->CreateModel(0.0f, -30.0f, 785.0f);

	flameMesh = myEngine->LoadMesh("quad.x");
	flame = flameMesh->CreateModel(0.0f, 0.0f, 5.9f);
	flame->AttachToParent(playerShip);

	playerCamera->SetLocalPosition(0.0f, 49.0f, 771.0f);
	playerCamera->RotateLocalX(90.0f);
	playerCamera->RotateLocalZ(180.0f);

	skyBoxMesh = myEngine->LoadMesh("Skybox 01.x");
	skyBox = skyBoxMesh->CreateModel(0.0f, -1050.0f, 0.0f);

	towerMesh = myEngine->LoadMesh("skyscraper04.x");
	tower = towerMesh->CreateModel(-80.0f, -130.0f, -840.0f);

	tower->Scale(0.5f);
	//fixedCamBlock->AttachToParent(playerShip);
	eCameraPos cameraPos;
	cameraPos = topDown;
	bool moveCamTop = false;
	bool moveCamBehind = false;


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
			placementPowerUp->MoveLocalY(-0.2f);
			powerUpTimer -= frameTime;
			if (powerUpTimer <= 0.0f)
			{
				currentPowerUpState = None;
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
					playerShip->MoveLocalX(-50.0f * frameTime);
				}
				if (myEngine->KeyHeld(MoveLeft))
				{
					playerShip->MoveLocalX(50.0f * frameTime);
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
					playerShip->MoveLocalZ(-50.0f * frameTime);
				}
				if (myEngine->KeyHeld(MoveDown))
				{
					playerShip->MoveLocalZ(50.0f * frameTime);
				}
				if (myEngine->KeyHeld(MoveRight))
				{
					playerShip->MoveLocalX(-50.0f * frameTime);
				}
				if (myEngine->KeyHeld(MoveLeft))
				{
					playerShip->MoveLocalX(50.0f * frameTime);
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
		//flame->LookAt(playerCamera);
		//particleV = particleV + -particleG * frameTime;
		//flame->MoveZ(particleV * frameTime);
		//particleCount -= frameTime;
		//if (particleCount <= 0)
		//{
		//	particleV = 70.0f;
		//	particleCount = 2.8;
		//}



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
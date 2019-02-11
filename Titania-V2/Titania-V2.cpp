// Titania-V2.cpp: A program using the TL-Engine
#include <TL-Engine.h>	// TL-Engine include file and namespace
#include "Defs.h"
using namespace tle;

EKeyCode camSwitch = Key_1;
EKeyCode MoveUp = Key_Up;
EKeyCode MoveRight = Key_Right;
EKeyCode MoveDown = Key_Down;
EKeyCode MoveLeft = Key_Left;

void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine(kTLX);
	myEngine->StartWindowed();

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder("C:\\ProgramData\\TL-Engine\\Media");
	myEngine->AddMediaFolder("D:\\DKavanagh2\\Documents\\GitHub\\Titania-V2\\Assest\\Vehicles\\Sci-Fi Gunships\\Sci-Fi_Gunships_collection");
	myEngine->AddMediaFolder("D:\\DKavanagh2\\Documents\\GitHub\\Titania-V2\\Assest\\Model Packs\\Architecture\SciFi");

	/**** Set up your scene here ****/
	ICamera* playerCamera = myEngine->CreateCamera(kManual);
	IModel* playerShip;
	IMesh* playerShipMesh;
	IModel* floor;
	IMesh* floorMesh;
	IModel* topDownCamBlock;
	IMesh* camBlockMesh;

	float countDown = 4;

	/* QUICK NOTE, Because of the camera being flipped the pluses and minus are swaped. (going left is pos)(going right is negative) */
	camBlockMesh = myEngine->LoadMesh("cube.x");
	topDownCamBlock = camBlockMesh->CreateModel(0.0f, -35.0f, -50.0f);
	topDownCamBlock->Scale(0.01f);
	floorMesh = myEngine->LoadMesh("floor.x");
	floor = floorMesh->CreateModel(0.0f, -130.0f, 0.0f);
	playerShipMesh = myEngine->LoadMesh("gunShip.x");
	playerShip = playerShipMesh->CreateModel(0.0f, -30.0f, -15.0f);
	playerCamera->SetLocalPosition(0.0f, 50.0f, -40.0f);
	playerCamera->RotateLocalX(90.0f);
	playerCamera->RotateLocalZ(180.0f);

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

	


		/* Camera Switching */
		switch (cameraPos)
		{
		case behind:
		{
			if (myEngine->KeyHeld(MoveRight))
			{
				playerShip->MoveLocalX(-50.0f * frameTime);
				playerCamera->MoveX(-50.0f * frameTime);
			}
			if (myEngine->KeyHeld(MoveLeft))
			{
				playerShip->MoveLocalX(50.0f * frameTime);
				playerCamera->MoveX(50.0f * frameTime);
			}
			if (myEngine->KeyHit(camSwitch))
			{
				moveCamBehind = true;
			}
			if (moveCamBehind == true)
			{
				playerCamera->LookAt(topDownCamBlock);
				countDown -= frameTime;
				playerCamera->MoveLocalY(21.0 * frameTime);
				playerCamera->MoveLocalZ(-8.0 * frameTime);
				if (countDown <= 0)
				{
					moveCamBehind = false;
					countDown = 4;
					topDownCamBlock->DetachFromParent();
					cameraPos = topDown;
				}
			}
			break;
		}
		case topDown:
		{
			playerCamera->LookAt(topDownCamBlock);
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
			if (myEngine->KeyHit(camSwitch))
			{
				moveCamTop = true;
			}
			if (moveCamTop == true)
			{
				countDown -= frameTime;
				playerCamera->MoveLocalY(-21.0 * frameTime);
				playerCamera->MoveLocalZ(8.0 * frameTime);
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
		/******************************/

		/**** Update your scene each frame here ****/

	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}

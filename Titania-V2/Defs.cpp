#include "Defs.h"
#include <TL-Engine.h>	// TL-Engine include file and namespace
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
using namespace tle;

//COLLISION DETECTION

int keyEnter(I3DEngine* myEngine)
{
	if (myEngine->KeyHit(Key_0)) return '0';
	else if (myEngine->KeyHit(Key_1)) return '1';
	else if (myEngine->KeyHit(Key_2)) return '2';
	else if (myEngine->KeyHit(Key_3)) return '3';
	else if (myEngine->KeyHit(Key_4)) return '4';
	else if (myEngine->KeyHit(Key_5)) return '5';
	else if (myEngine->KeyHit(Key_6)) return '6';
	else if (myEngine->KeyHit(Key_7)) return '7';
	else if (myEngine->KeyHit(Key_8)) return '8';
	else if (myEngine->KeyHit(Key_9)) return '9';
	else if (myEngine->KeyHit(Key_Q)) return 'Q';
	else if (myEngine->KeyHit(Key_W)) return 'W';
	else if (myEngine->KeyHit(Key_E)) return 'E';
	else if (myEngine->KeyHit(Key_R)) return 'R';
	else if (myEngine->KeyHit(Key_T)) return 'T';
	else if (myEngine->KeyHit(Key_Y)) return 'Y';
	else if (myEngine->KeyHit(Key_U)) return 'U';
	else if (myEngine->KeyHit(Key_I)) return 'I';
	else if (myEngine->KeyHit(Key_O)) return 'O';
	else if (myEngine->KeyHit(Key_P)) return 'P';
	else if (myEngine->KeyHit(Key_A)) return 'A';
	else if (myEngine->KeyHit(Key_S)) return 'S';
	else if (myEngine->KeyHit(Key_D)) return 'D';
	else if (myEngine->KeyHit(Key_F)) return 'F';
	else if (myEngine->KeyHit(Key_G)) return 'G';
	else if (myEngine->KeyHit(Key_H)) return 'H';
	else if (myEngine->KeyHit(Key_J)) return 'J';
	else if (myEngine->KeyHit(Key_K)) return 'K';
	else if (myEngine->KeyHit(Key_L)) return 'L';
	else if (myEngine->KeyHit(Key_Z)) return 'Z';
	else if (myEngine->KeyHit(Key_X)) return 'X';
	else if (myEngine->KeyHit(Key_C)) return 'C';
	else if (myEngine->KeyHit(Key_V)) return 'V';
	else if (myEngine->KeyHit(Key_B)) return 'B';
	else if (myEngine->KeyHit(Key_N)) return 'N';
	else if (myEngine->KeyHit(Key_M)) return 'M';
}

bool sphere2sphere( IModel*& Ship, IModel*& Object, float shipRad, float objectRad) //Calculates distance between two spheres and if they have collided
{
 	int s1xPos = Ship->GetLocalX();	
	int s1yPos = Ship->GetLocalY();
	int s1zPos = Ship->GetLocalZ();

   	int s2xPos = Object->GetLocalX();
	int s2yPos = Object->GetLocalY();
	int s2zPos = Object->GetLocalZ();

	float distX = s2xPos - s1xPos;
	float distZ = s2zPos - s1zPos;
	float distY = s2yPos - s1yPos;
	float distance = sqrt(distX * distX + distZ * distZ + distY * distY);

	return (distance < (shipRad + objectRad));
}

// Return a random number in the range between rangeMin and rangeMax inclusive
// range_min <= random number <= range_max
float random(int rangeMin, int rangeMax)
{
	float result = (float)rand() / (float)(RAND_MAX + 1);
	result *= (float)(rangeMax - rangeMin);
	result += rangeMin;

	return result;
}


CBulletData::CBulletData()
{
}

CBulletData::~CBulletData()
{
}

//CTripleBullet::CTripleBullet()
//{
//}
//
//CTripleBullet::~CTripleBullet()
//{
//}
//
//CNormalBullet::CNormalBullet()
//{
//}
//
//CNormalBullet::~CNormalBullet()
//{
//}
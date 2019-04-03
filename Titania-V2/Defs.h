#pragma once
#include <TL-Engine.h>	// TL-Engine include file and namespace
#include <SFML/Audio.hpp>
#include <deque>
#include  <memory>
using namespace tle;



enum eCameraPos { behind, topDown };
enum PowerUpState { None, Speed, Shield, Bullet };
bool sphere2sphere(IModel*& Ship, IModel*& Object, float shipRad, float objectRad); //collision function for any sphere on sphere collisions
float random(int rangeMin, int rangeMax);


const float PLAYERSHIPRADIUS = 3.0f;
const float PLACEMENTPOWERUPRADIUS = 2.0f;
const float ENEMYSHIPRADIUS = 6.0f;
const float BULLETRADIUS = 1.0f;

class CBulletData
{
public:
	CBulletData();
	~CBulletData();
	IModel* model;
	float xVel, yVel, zVel;
	float life = 3.0;
	float mRadius;
	float mHealth;
	string mOwner;
	float mSpeed;
	bool mImmune = false;
};

//class CTripleBullet : public CBulletData
//{
//public:
//	CTripleBullet();
//	~CTripleBullet();
//	float fireRate = 20.0f;
//private:
//
//};
//
//class CNormalBullet : public CBulletData
//{
//public:
//	CNormalBullet();
//	~CNormalBullet();
//	float fireRate = 20.0f;
//private:
//
//};



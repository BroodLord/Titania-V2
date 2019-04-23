#pragma once
#include <TL-Engine.h>	// TL-Engine include file and namespace
#include <SFML/Audio.hpp>
#include <deque>
#include  <memory>
#include <fstream>

using namespace tle;

class LeaderBoardClass
{
public:
	void setter(string n, int s, int t)
	{
		name = n;
		score = s;
		time = t;
	}
	void LeaderBoardRead(std::vector<LeaderBoardClass*> &leaderboard)
	{
		ifstream infile("LeaderBoard.txt");
		while (infile.is_open())
		{
			LeaderBoardClass* ptr = new LeaderBoardClass();
			string name = "";
			int score = 0;
			int timer = 0;
			infile >> name;
			infile >> score;
			infile >> timer;
			ptr->setter(name, score, timer);
			leaderboard.push_back(ptr);

			if (infile.end)
			{
				infile.close();
			}
		}
	}

	void LeaderBoardWrite(std::vector<LeaderBoardClass*> &leaderboard)
	{
		ofstream infile("LeaderBoard.txt");
		int counter = 0;
		LeaderBoardClass* ptr;
		LeaderBoardClass* ptr2;
		sort(leaderboard.begin(), leaderboard.end());
		for (auto i = leaderboard.begin(); i != leaderboard.end();)
		{
			counter++;
			string n = (*i)->name;
			int s = (*i)->score;
			int t = (*i)->time;
			infile << n;
			infile << s;
			infile << t;
			if (counter == 10)
			{
				counter = 0;
				break;
			}
		}
	}

protected:
	string name;
	int score;
	int time;
};



enum eCameraPos { behind, topDown };
enum PowerUpState { None, Speed, Shield, Bullet };
bool sphere2sphere(IModel*& Ship, IModel*& Object, float shipRad, float objectRad); //collision function for any sphere on sphere collisions
float random(int rangeMin, int rangeMax);
int keyEnter(I3DEngine* myEngine);


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
	float mDistance = 10.0f;
	float angle = 0.0f;
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



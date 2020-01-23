#pragma once
#include <TL-Engine.h>	// TL-Engine include file and namespace
//#include <SFML/Audio.hpp>
#include <deque>
#include  <memory>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
using namespace tle;



class LeaderBoardClass
{
public:
	string name;
	int score;
	int time;

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
			static int count = 0;
			LeaderBoardClass* ptr = new LeaderBoardClass();
			string name;
			int score = 0;
			int timer = 0;
			infile >> name;
			name.erase(remove_if(name.begin(), name.end(), isspace), name.end());
			infile >> score;
			infile >> timer;
			ptr->setter(name, score, timer);
			leaderboard.push_back(ptr);
			count++;

			if (count == 10)
			{
				count = 0;
				infile.close();
			}
		}
	}

	bool comp(LeaderBoardClass* v1, LeaderBoardClass* v2)
	{
		return v1->score < v2->score;
	}


	void LeaderBoardWrite(std::vector<LeaderBoardClass*> &leaderboard)
	{
		ofstream infile("LeaderBoard.txt");
		int counter = 0;
		LeaderBoardClass* ptr = new LeaderBoardClass;
		LeaderBoardClass* ptr2 = new LeaderBoardClass;
		
		//std::sort(leaderboard.begin(), leaderboard.end(), comp);

		std::sort(leaderboard.begin(),
			leaderboard.end(),
			[](const LeaderBoardClass* lhs, const LeaderBoardClass* rhs)
		{
			return lhs->score > rhs->score;
		});

		for (auto i = leaderboard.begin(); i != leaderboard.end(); ++i)
		{
			counter++;
			string n = (*i)->name;
			int s = (*i)->score;
			int t = (*i)->time;
			char schar = s - '0';
			char tchar = t - '0';

			infile << n.c_str() << " " << s << " " << t << " " << endl;
			if (counter == 10)
			{
				counter = 0;
				leaderboard.clear();
				ptr->LeaderBoardRead(leaderboard);
				break;
			}
		}
	}

	
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



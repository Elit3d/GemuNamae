#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	Player();
	~Player();
	Player(std::string filename);

	int getHealth();
	void setHealth(int h);
	void takeDmg(int dmg);

	int getScore();
	void setScore(int s);
	void addScore(int s);
private:
	int health, maxHealth;
	int score = 0;
};


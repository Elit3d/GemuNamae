#include "Player.h"


Player::Player()
{
	health = 10;
	maxHealth = 10;
}


Player::~Player()
{
}

int Player::getHealth()
{
	return health;
}

void Player::setHealth(int h)
{
	health = h;
}

void Player::takeDmg(int dmg)
{
	health -= dmg;
}

int Player::getScore()
{
	return score;
}

void Player::setScore(int s)
{
	score = s;
}

void Player::addScore(int s)
{
	score += s;
}
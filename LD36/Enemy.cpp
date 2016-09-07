#include "Enemy.h"
#include <iostream>

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

Enemy::Enemy(std::string filename)
{
	counter = 0;
	randProjectileTime = rand() % 5 + 1;
	bulletLifetime = 0;
	lifeTime = 100;
	texture.loadFromFile(filename);
	sprite.setTexture(texture);

	dagger_texture.loadFromFile("img/dagger.png");
	dagger_sprite.setTexture(dagger_texture);
}

sf::Vector2f Enemy::getPos()
{
	return sprite.getPosition();
}

void Enemy::set_pos(int x, int y)
{
	sprite.setPosition(x, y);
}

int Enemy::getHeight()
{
	return sprite.getGlobalBounds().height;
}

void Enemy::moveEnemy()
{
	counter++;

	if (counter >= randCounter)
	{
		enemyDir = rand() % 2;
		randCounter = rand() % 100 + 50;
		counter = 0;
	}

	switch (enemyDir)
	{
	case 0:
		if (sprite.getPosition().x > 0)
			sprite.move(-0.5f, 0.0f);
		break;
	case 1:
		if (sprite.getPosition().x < 320 - sprite.getGlobalBounds().width)
			sprite.move(0.5f, 0.0f);
		break;
	}
}

sf::Sprite Enemy::getDaggerSprite()
{
	return dagger_sprite;
}

void Enemy::Attack(sf::Sprite player)
{
	//bulletLifetime++;
	//if (bulletLifetime >= 500)
	//{
	//	destroy = true;
	//	bulletLifetime = 0;
	//}

	//sf::Time elapsed1 = projectileClock.getElapsedTime();

	//Shoot bullets at certain speed
	//if (elapsed1.asSeconds() >= randProjectileTime)
	//{
	//	randProjectileTime = rand() % 5 + 1;
	//	projectileClock.restart(); // Restart clock
	//	if (player.getPosition().x < sprite.getPosition().x)
	//	{
	//		//dagger_sprite.setRotation(0);
	//		//dagger_sprite.setPosition(sprite.getPosition().x - sprite.getGlobalBounds().width, sprite.getPosition().y + 10);
	//		shotDir = 0;
	//		//dagger_vector.push_back(dagger_sprite);
	//	}
	//	else if (player.getPosition().x > sprite.getPosition().x)
	//	{
	//		//dagger_sprite.setRotation(180);
	//		//dagger_sprite.setPosition(sprite.getPosition().x + sprite.getGlobalBounds().width, sprite.getPosition().y + 14);
	//		shotDir = 1;
	//		//dagger_vector.push_back(dagger_sprite);
	//	}
	//}

	//for (dagger_iter = dagger_vector.begin(); dagger_iter != dagger_vector.end(); dagger_iter++)
	//{
	//	if (destroy == true)
	//	{
	//		dagger_vector.erase(dagger_iter);
	//		destroy = false;
	//		break;
	//	}
	//}
}

bool Enemy::FireProjectile()
{
	sf::Time elapsed1 = projectileClock.getElapsedTime();

	if (elapsed1.asSeconds() >= randProjectileTime)
	{
		randProjectileTime = rand() % 5 + 1;
		projectileClock.restart(); // Restart clock

		return true;
	}
	return false;
}

sf::Sprite Enemy::getSprite()
{
	return sprite;
}

//void Enemy::Draw(sf::RenderWindow &window)
//{
//	window.draw(sprite);
//
//	for (dagger_iter = dagger_vector.begin(); dagger_iter != dagger_vector.end(); dagger_iter++)
//	{
//		if (shotDir == 0)
//		{
//			(dagger_iter)->move(-1.0f, 0.0f);
//			window.draw((*dagger_iter));
//		}
//		else if (shotDir == 1)
//		{
//			(dagger_iter)->move(1.0f, 0.0f);
//			window.draw((*dagger_iter));
//		}
//	}
//}
#pragma once

#include "Entity.h"
#include "Projectile.h"

class Enemy : 
	public Entity
{
public:
	Enemy();
	~Enemy();
	Enemy(std::string filename);

	sf::Vector2f getPos();
	void set_pos(int x, int y);

	int getHeight();

	void moveEnemy();
	void Attack(sf::Sprite player);

	sf::Sprite getSprite();
	sf::Sprite getDaggerSprite();

	std::vector<sf::Sprite> dagger_vector;
	std::vector<sf::Sprite>::iterator dagger_iter;

	bool FireProjectile();

	//void Update(Player &player);
	void Draw(sf::RenderWindow &window);
private:
	//sf::Sprite sprite;
	//sf::Texture texture;

	sf::Texture dagger_texture;
	sf::Sprite dagger_sprite;

	sf::Clock projectileClock;
	int randProjectileTime = rand() % 5 + 1;

	int enemyDir;
	int shotDir;
	int counter;
	int randCounter = rand() % 100 + 50;
	int bulletLifetime, lifeTime;
	bool destroy = false;
};


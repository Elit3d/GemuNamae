#include "Projectile.h"


Projectile::Projectile()
{
	bulletLifeTime = 0;
	lifeTime = rand() % 500 + 250;
	
	texture.loadFromFile("img/dagger.png");
	sprite.setTexture(texture);
	sprite.setRotation(180);

	rect.setSize(sf::Vector2f(10, 10));
	rect.setPosition(0, 0);
	rect.setFillColor(sf::Color::Green);
}


Projectile::~Projectile()
{
}

Projectile::Projectile(std::string filename)
{
	//texture.loadFromFile(filename);
	//sprite.setTexture(texture);
	//sprite.setPosition(0, 0);

	rect.setSize(sf::Vector2f(10, 10));
	rect.setPosition(0, 0);
	rect.setFillColor(sf::Color::Green);

	bulletLifeTime = 0;
	lifeTime = rand() % 200 + 100;
}

bool Projectile::Destroy()
{
	bulletLifeTime++;
	if (bulletLifeTime >= 200)
	{
		bulletLifeTime = 0;
		return true;
	}
	return false;
}

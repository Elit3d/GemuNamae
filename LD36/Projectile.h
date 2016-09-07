#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_
#include "Entity.h"

class Projectile : public Entity
{
public:
	Projectile();
	~Projectile();
	Projectile(std::string filename);

	bool Destroy();
private:
	int bulletLifeTime, lifeTime;
};
#endif

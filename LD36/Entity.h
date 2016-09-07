#ifndef _ENTITY_H_
#define _ENTITY_H_
#include <SFML\Graphics.hpp>

class Entity
{
public:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::RectangleShape rect;
};
#endif
#pragma once
#include <SFML\Graphics.hpp>

class Tile
{
public:
	Tile();
	~Tile();
	Tile(std::string filename);

	bool Place(sf::Vector2f pos);
	void Draw(sf::RenderWindow &window);
private:
	sf::Vector2f m_pos;
	sf::Texture tileTexture;
	sf::Sprite tile;
};


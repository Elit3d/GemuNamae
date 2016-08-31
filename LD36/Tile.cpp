#include "Tile.h"


Tile::Tile()
{
}

Tile::~Tile()
{
}

Tile::Tile(std::string filename)
{
	tileTexture.loadFromFile(filename);
	tile.setTexture(tileTexture);
	tile.setPosition(0, 0);
}

bool Tile::Place(sf::Vector2f pos)
{
	m_pos = pos;
	tile.setPosition(m_pos);
	return true;
}

void Tile::Draw(sf::RenderWindow &window)
{
	window.draw(tile);
}
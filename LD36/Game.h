#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

#include "Tile.h"
#include "Enemy.h"
#include "Player.h"

const int SOLID_WIDTH = 10;
const int SOLID_HEIGHT = 100;

const int BLANK_WIDTH = 3;
const int BLANK_HEIGHT = 3;

enum GameState
{
	SPLASH,
	MENU,
	GAME,
	PAUSE,
	LOAD,
	RESTART,
	GAMEOVER
};

class Game
{
public:
	Game();
	~Game();

	void Setup();
	void Update();
	void Draw(sf::RenderWindow &window);

	bool SpawnSolidBlock();
	bool SpawnEnemyOnBlock();
	bool TileCollision(sf::Sprite &obj1);
	void SetupEnemy();
	void RestartGame();
	void NextLevel();
private:
	Enemy *e1;
	Player player;
	GameState state;

	std::vector<Enemy*> enemyVector;
	std::vector<Enemy*>::iterator enemyiter;

	sf::Texture block_texture;
	sf::Sprite block_sprite[SOLID_WIDTH][SOLID_HEIGHT];

	sf::Texture block2_texture;
	sf::Sprite block2_sprite[BLANK_WIDTH][BLANK_HEIGHT];

	sf::Texture player_texture;
	sf::Sprite player_sprite;
	
	sf::Texture whip_texture;
	sf::Sprite whip_sprite;

	std::vector<sf::Sprite> block_vector;
	std::vector<sf::Sprite>::iterator block_iter;

	float spawncounter;
	float testrand;
	bool maxSpawned = false;
	bool drawWhip = false;
	bool isAbovePlatform = false;

	sf::View view;
	sf::Vector2f vel;

	sf::Font font;
	sf::Text health;
	sf::Text score;
	sf::Text game_over;
	sf::Text restart;
	sf::Text startgame;
	sf::Text gameName;
	sf::Text createdby;
};


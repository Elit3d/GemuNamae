#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

#include "Tile.h"
#include "Enemy.h"
#include "Player.h"
#include "Projectile.h"

const int SOLID_WIDTH = 10;
const int SOLID_HEIGHT = 100;

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

	void SetupBlocks();
	bool SpawnSolidBlock();
	bool SpawnEnemyOnBlock();
	void SetupEnemy();
	void RestartGame();
	void NextLevel();
	int generateRand(int min, int max);
	void DestroyObjects();
	void HeartContainers();

	bool topWallCollide(sf::Sprite &obj1);
	bool leftWallCollide(sf::Sprite &obj1);
	bool rightWallCollide(sf::Sprite &obj1);
private:
	Enemy *e1;
	Player player;
	GameState state;
	Projectile proj;

	std::vector<Projectile> projVector;
	std::vector<Projectile>::iterator projiter;

	std::vector<Enemy*> enemyVector;
	std::vector<Enemy*>::iterator enemyiter;

	sf::Texture block_texture;
	sf::Sprite block_sprite[SOLID_WIDTH][SOLID_HEIGHT];

	sf::Texture player_texture;
	sf::Sprite player_sprite;
	
	sf::Texture whip_texture;
	sf::Sprite whip_sprite;

	sf::Texture bg_texture;
	sf::Sprite bg_sprite;

	sf::Texture heart_texture;
	sf::Sprite heart_sprite;

	std::vector<sf::Sprite> block_vector;
	std::vector<sf::Sprite>::iterator block_iter;

	float spawncounter;
	int randNumber;
	bool drawWhip = false;

	sf::View view;
	sf::View uiView;
	sf::Vector2f vel;

	sf::Font font;
	sf::Text health;
	sf::Text score;
	sf::Text game_over;
	sf::Text restart;
	sf::Text startgame;
	sf::Text gameName;
	sf::Text createdby;

	bool leftCollide, rightCollide, topCollide, bottomCollide;
	int blockLeft, blockRight, blockUp, blockDown;
	int oldPosY, oldPosX;
};


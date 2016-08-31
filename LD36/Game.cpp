#include "Game.h"
#include <sstream>

Game::Game()
{
	testrand = 2;
	spawncounter = 0;
	state = MENU;
}


Game::~Game()
{
}

void Game::Setup()
{
	font.loadFromFile("font/arial.ttf");

	player_texture.loadFromFile("img/player.png");
	player_sprite.setTexture(player_texture);
	player_sprite.setPosition(50, 0);

	whip_texture.loadFromFile("img/whip.png");
	whip_sprite.setTexture(whip_texture);

	block_texture.loadFromFile("img/block.png");
	block2_texture.loadFromFile("img/block_not_solid.png");

	for (int x = 0; x < SOLID_WIDTH; x++)
	{
		for (int y = 0; y < SOLID_HEIGHT; y++)
		{
			block_sprite[x][y].setTexture(block_texture);

			if (SpawnSolidBlock() == true)
			{
				block_sprite[x][y].setPosition(x * 32, 32 + (y * 64));
				block_vector.push_back(block_sprite[x][y]);

				if (SpawnEnemyOnBlock() == true)
				{
					e1 = new Enemy("img/enemy1.png");
					e1->set_pos(x * 32, block_sprite[x][y].getPosition().y - e1->getHeight());
					enemyVector.push_back(e1);
				}
			}
		}
	}

	health.setFont(font);
	health.setCharacterSize(18);

	score.setFont(font);
	score.setCharacterSize(18);

	game_over.setFont(font);
	game_over.setCharacterSize(30);
	game_over.setString("Game Over");

	restart.setFont(font);
	restart.setCharacterSize(18);
	restart.setString("Press [R] to restart the game!");

	gameName.setFont(font);
	gameName.setCharacterSize(40);
	gameName.setString("Gemu Namae");
	gameName.setPosition(30, 0);

	startgame.setFont(font);
	startgame.setCharacterSize(18);
	startgame.setString("Press [P] to start the game!");
	startgame.setPosition(startgame.getGlobalBounds().width - 320 / 2, 500 / 2);

	createdby.setFont(font);
	createdby.setCharacterSize(18);
	createdby.setString("Kyle Thomas - @Elit3dGaming");
	createdby.setPosition(40, 470);
}

void Game::SetupEnemy()
{
	e1 = new Enemy("img/enemy1.png");
}

bool Game::SpawnSolidBlock()
{
	int blockNum = rand() % 2;
	if (blockNum == 0)
	{
		return true;
	}
	return false;
}

bool Game::SpawnEnemyOnBlock()
{
	int enemyNum = rand() % 5;
	if (enemyNum == 0)
	{
		return true;
	}
	return false;
}

bool Game::TileCollision(sf::Sprite &obj1)
{
	for (int i = 0; i < block_vector.size(); i++)
	{
		if (obj1.getGlobalBounds().intersects(block_vector[i].getGlobalBounds()))
		{
			return true;
		}
	}


	return false;
}

void Game::NextLevel()
{
	spawncounter++;
	if (spawncounter >= 100)
	{
		spawncounter = 0;

		for (int x = 0; x < SOLID_WIDTH; x++)
		{
			for (int y = 0; y < SOLID_HEIGHT; y++)
			{
				block_sprite[x][y].setTexture(block_texture);

				if (SpawnSolidBlock() == true)
				{
					block_sprite[x][y].setPosition(x * 32, 32 + (y * 64));
					block_vector.push_back(block_sprite[x][y]);

					if (SpawnEnemyOnBlock() == true)
					{
						e1 = new Enemy("img/enemy1.png");
						e1->set_pos(x * 32, block_sprite[x][y].getPosition().y - e1->getHeight());
						enemyVector.push_back(e1);
					}
				}
			}
		}

		state = GAME;
	}
	else
	{
		for (enemyiter = enemyVector.begin(); enemyiter != enemyVector.end(); enemyiter++)
		{
			enemyVector.erase(enemyiter);
			break;
		}

		for (int i = 0; i < block_vector.size(); i++)
		{
			block_vector.clear();
		}
	}

	player.setHealth(10);
	player_sprite.setPosition(50, 0);
}

void Game::RestartGame()
{
	NextLevel();
	player.setScore(0);
}


void Game::Update()
{
	std::ostringstream ss; //string buffer to convert numbers to string
	ss << "Health: " << player.getHealth();// put float into string buffer

	std::ostringstream ss1; //string buffer to convert numbers to string
	ss1 << "Score: " << player.getScore();// put float into string buffer

	switch (state)
	{
	case SPLASH:
		break;
	case MENU:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			state = GAME;
		}
		break;
	case GAME:
		view.setCenter(player_sprite.getPosition().x, player_sprite.getPosition().y);
		view.setSize(320, 500);

		health.setPosition(player_sprite.getPosition().x - 150, player_sprite.getPosition().y - 245);
		health.setString(ss.str());

		score.setPosition(player_sprite.getPosition().x + 50, player_sprite.getPosition().y - 245);
		score.setString(ss1.str());

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			whip_sprite.setPosition(player_sprite.getPosition().x + player_sprite.getGlobalBounds().width, player_sprite.getPosition().y + 10);
			drawWhip = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			whip_sprite.setPosition(player_sprite.getPosition().x - whip_sprite.getGlobalBounds().width, player_sprite.getPosition().y + 10);
			drawWhip = true;
		}
		else
		{
			drawWhip = false;
		}

		if (TileCollision(player_sprite))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player_sprite.getPosition().x <= 320 - player_sprite.getGlobalBounds().width)
			{
				player_sprite.move(sf::Vector2f(1.0f, 0.0f));
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player_sprite.getPosition().x >= 0)
			{
				player_sprite.move(sf::Vector2f(-1.0f, 0.0f));
			}
		}
		else
		{
			player_sprite.move(sf::Vector2f(0, 3.0f));
		}

		for (enemyiter = enemyVector.begin(); enemyiter != enemyVector.end(); enemyiter++)
		{
			(*enemyiter)->Attack(player_sprite);
			(*enemyiter)->moveEnemy();
		}

		for (enemyiter = enemyVector.begin(); enemyiter != enemyVector.end(); enemyiter++)
		{
			if (whip_sprite.getGlobalBounds().intersects((*enemyiter)->getSprite().getGlobalBounds()))
			{
				player.addScore(10);
				enemyVector.erase(enemyiter);
				break;
			}
			for ((*enemyiter)->dagger_iter = (*enemyiter)->dagger_vector.begin(); (*enemyiter)->dagger_iter != (*enemyiter)->dagger_vector.end(); (*enemyiter)->dagger_iter++)
			{
				if (whip_sprite.getGlobalBounds().intersects((*enemyiter)->dagger_iter->getGlobalBounds()))
				{
					player.addScore(1);
					(*enemyiter)->dagger_vector.erase((*enemyiter)->dagger_iter);
					break;
				}
				if ((*enemyiter)->dagger_iter->getGlobalBounds().intersects(player_sprite.getGlobalBounds()))
				{
					player.takeDmg(1);
					(*enemyiter)->dagger_vector.erase((*enemyiter)->dagger_iter);
					//std::cout << player.getHealth() << std::endl;
					break;
				}
			}
		}

		if (player_sprite.getPosition().y >= 6300)
		{
			state = LOAD;
		}

		if (player.getHealth() <= 0)
		{
			state = GAMEOVER;
		}
		break;
	case PAUSE:
		break;
	case LOAD:
		NextLevel();
		break;
	case RESTART:
		RestartGame();
		break;
	case GAMEOVER:
		game_over.setPosition(player_sprite.getPosition().x - player_sprite.getGlobalBounds().width - 50, player_sprite.getPosition().y - 30);

		restart.setPosition(player_sprite.getPosition().x - player_sprite.getGlobalBounds().width - 100, player_sprite.getPosition().y + 100);

		score.setPosition(player_sprite.getPosition().x - player_sprite.getGlobalBounds().width - 10, player_sprite.getPosition().y);
		score.setString(ss1.str());

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			state = RESTART;
		}
		break;
	}
}

void Game::Draw(sf::RenderWindow &window)
{
	switch (state)
	{
	case SPLASH:
		break;
	case MENU:
		window.draw(startgame);
		window.draw(gameName);
		window.draw(createdby);
		break;
	case GAME:
		for (int i = 0; i < block_vector.size(); i++)
			window.draw(block_vector[i]);

		window.draw(player_sprite);
		window.setView(view);

		if (drawWhip == true)
			window.draw(whip_sprite);

		for (enemyiter = enemyVector.begin(); enemyiter != enemyVector.end(); enemyiter++)
		{
			(*enemyiter)->Draw(window);
		}

		window.draw(health);
		window.draw(score);
		break;
	case PAUSE:
		break;
	case LOAD:
		break;
	case RESTART:
		break;
	case GAMEOVER:
		window.draw(game_over);
		window.draw(score);
		window.draw(restart);
		break;
	}
}
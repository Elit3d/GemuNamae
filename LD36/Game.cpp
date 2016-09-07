#include "Game.h"
#include <sstream>

Game::Game()
{
	spawncounter = 0;
	state = MENU;
}


Game::~Game()
{
	e1 = NULL;
	delete e1;
}

int Game::generateRand(int min, int max)
{
	randNumber = rand() % max + min;
	return randNumber;
}

void Game::Setup()
{
	topCollide = false;

	font.loadFromFile("font/arial.ttf");

	player_texture.loadFromFile("img/player.png");
	player_sprite.setTexture(player_texture);
	player_sprite.setPosition(50, -100);

	whip_texture.loadFromFile("img/whip.png");
	whip_sprite.setTexture(whip_texture);

	block_texture.loadFromFile("img/block.png");

	SetupBlocks();

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

	bg_texture.loadFromFile("img/bg.png");
	bg_sprite.setTexture(bg_texture);
	bg_sprite.setPosition(0, 0);

	uiView.setViewport(sf::FloatRect(0, 0, 1, 1));
	//uiView.zoom();
}

void Game::SetupBlocks()
{
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
}

void Game::SetupEnemy()
{
	e1 = new Enemy("img/enemy1.png");
}

bool Game::SpawnSolidBlock()
{
	if (generateRand(0, 2) == 0)
	{
		return true;
	}
	return false;
}

bool Game::SpawnEnemyOnBlock()
{
	if (generateRand(0, 10) == 0)
	{
		return true;
	}
	return false;
}

bool Game::topWallCollide(sf::Sprite &obj1)
{
	for (int i = 0; i < block_vector.size(); i++)
	{
		if (obj1.getGlobalBounds().intersects(block_vector[i].getGlobalBounds()))
		{
			if (obj1.getPosition().y + obj1.getGlobalBounds().height < block_vector[i].getPosition().y + block_vector[i].getGlobalBounds().height)
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

		SetupBlocks();

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
	player_sprite.setScale(4, 4);
}

void Game::RestartGame()
{
	NextLevel();
	player.setScore(0);
}

bool Game::leftWallCollide(sf::Sprite &obj1)
{
	for (int i = 0; i < block_vector.size(); i++)
	{
		if (obj1.getGlobalBounds().intersects(block_vector[i].getGlobalBounds()))
		{
			if (obj1.getPosition().y >= block_vector[i].getPosition().y - 20)
			{
				if (obj1.getPosition().x + obj1.getGlobalBounds().width < block_vector[i].getPosition().x + block_vector[i].getGlobalBounds().width)
					return true;
			}
		}
	}
	return false;
}

bool Game::rightWallCollide(sf::Sprite &obj1)
{
	for (int i = 0; i < block_vector.size(); i++)
	{
		if (obj1.getGlobalBounds().intersects(block_vector[i].getGlobalBounds()))
		{
			if (obj1.getPosition().y >= block_vector[i].getPosition().y - 20)
			{
				if (obj1.getPosition().x + obj1.getGlobalBounds().width > block_vector[i].getPosition().x + block_vector[i].getGlobalBounds().width)
					return true;
			}
		}
	}
	return false;
}

void Game::HeartContainers()
{
	switch (player.getHealth())
	{
	case 0:
		heart_texture.loadFromFile("img/heart_containers/heart_0.png");
		break;
	case 1:
		heart_texture.loadFromFile("img/heart_containers/heart_1.png");
		break;
	case 2:
		heart_texture.loadFromFile("img/heart_containers/heart_2.png");
		break;
	case 3:
		heart_texture.loadFromFile("img/heart_containers/heart_3.png");
		break;
	case 4:
		heart_texture.loadFromFile("img/heart_containers/heart_4.png");
		break;
	case 5:
		heart_texture.loadFromFile("img/heart_containers/heart_5.png");
		break;
	case 6:
		heart_texture.loadFromFile("img/heart_containers/heart_6.png");
		break;
	case 7:
		heart_texture.loadFromFile("img/heart_containers/heart_7.png");
		break;
	case 8:
		heart_texture.loadFromFile("img/heart_containers/heart_8.png");
		break;
	case 9:
		heart_texture.loadFromFile("img/heart_containers/heart_9.png");
		break;
	case 10:
		heart_texture.loadFromFile("img/heart_containers/heart_10.png");
		break;
	}

	heart_sprite.setTexture(heart_texture);
	heart_sprite.setPosition(0,0);
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
			player.takeDmg(1);

		HeartContainers(); //chose the texture to display

		oldPosY = player_sprite.getPosition().y;
		oldPosX = player_sprite.getPosition().x;

		//top tile collision
		if (topWallCollide(player_sprite))
		{
			player_sprite.setPosition(oldPosX, oldPosY);
		}
		else
		{
			player_sprite.move(0, 2.0f);
		}

		//left tile collision
		if (leftWallCollide(player_sprite))
		{
			player_sprite.move(-1.0f, 0);
		}
		else
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				player_sprite.move(1.0f, 0);
		}

		//right tile collision
		if (rightWallCollide(player_sprite))
		{
			player_sprite.move(1.0f, 0);
		}
		else
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				player_sprite.move(-1.0f, 0);
		}

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


		for (enemyiter = enemyVector.begin(); enemyiter != enemyVector.end(); enemyiter++)
		{
			//(*enemyiter)->Attack(player_sprite);
			if ((*enemyiter)->FireProjectile() == true)
			{
				proj.rect.setPosition((*enemyiter)->getPos().x, (*enemyiter)->getPos().y + (*enemyiter)->getSprite().getGlobalBounds().width / 2);
				projVector.push_back(proj);
			}

			(*enemyiter)->moveEnemy();
		}

		if (player_sprite.getPosition().y >= 6300)
		{
			state = LOAD;
		}

		if (player.getHealth() <= 0)
		{
			state = GAMEOVER;
		}

		DestroyObjects(); //destroy all the objects

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

void Game::DestroyObjects()
{
	for (projiter = projVector.begin(); projiter != projVector.end(); projiter++)
	{
		//kill projectile
		if ((projiter)->Destroy() == true)
		{
			projVector.erase(projiter);
			break;
		}
	}

	for (enemyiter = enemyVector.begin(); enemyiter != enemyVector.end(); enemyiter++)
	{
		//whip collision with enemy
		if (whip_sprite.getGlobalBounds().intersects((*enemyiter)->getSprite().getGlobalBounds()))
		{
			player.addScore(10);
			enemyVector.erase(enemyiter);
			break;
		}

		for ((*enemyiter)->dagger_iter = (*enemyiter)->dagger_vector.begin(); (*enemyiter)->dagger_iter != (*enemyiter)->dagger_vector.end(); (*enemyiter)->dagger_iter++)
		{
			//whip collision with dagger
			if (whip_sprite.getGlobalBounds().intersects((*enemyiter)->dagger_iter->getGlobalBounds()))
			{
				player.addScore(1);
				(*enemyiter)->dagger_vector.erase((*enemyiter)->dagger_iter);
				break;
			}

			//dagger collision with player
			if ((*enemyiter)->dagger_iter->getGlobalBounds().intersects(player_sprite.getGlobalBounds()))
			{
				player.takeDmg(1);
				(*enemyiter)->dagger_vector.erase((*enemyiter)->dagger_iter);
				break;
			}
		}
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
		window.setView(view);
		window.draw(bg_sprite);

		for (int i = 0; i < block_vector.size(); i++)
			window.draw(block_vector[i]);

		window.draw(player_sprite);

		if (drawWhip == true)
			window.draw(whip_sprite);

		for (projiter = projVector.begin(); projiter != projVector.end(); projiter++)
		{
			(projiter)->rect.move(1.0f, 0);
			window.draw((projiter)->rect);
		}

		for (enemyiter = enemyVector.begin(); enemyiter != enemyVector.end(); enemyiter++)
		{
			window.draw((*enemyiter)->sprite);
		}

		window.draw(health);
		window.draw(score);

		window.setView(uiView);
		window.draw(heart_sprite);
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
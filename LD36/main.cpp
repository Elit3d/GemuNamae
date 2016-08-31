#include <SFML\Graphics.hpp>

#include "Game.h"

int main()
{
	srand(time(NULL)); //randomize the map
	sf::RenderWindow window(sf::VideoMode(320, 500), "Gemu Namae");
	window.setFramerateLimit(120);
	window.setKeyRepeatEnabled(false);
	Game game;

	game.Setup();

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				window.close();
		}

		game.Update();

		window.clear();
		game.Draw(window);
		window.display();
	}

	return 0;
}
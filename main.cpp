#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstring>
#include "Gameset.h"
#include "Snakegame.h"
#include "Doodlejumpgame.h"
#include "Tetrisgame3.h"
#include "Menu.h"

using namespace std;

int main() {
	const int windowWidth = 600;
	const int windowHeight = 600;
	sf::Vector2i WindowSize(windowWidth, windowHeight);
	sf::RenderWindow window(sf::VideoMode(WindowSize.x, WindowSize.y), "Gamemenu");
	Menu menu((float)window.getSize().x, (float)window.getSize().y);
	menu.setbackground((float)WindowSize.x, (float)WindowSize.y);

	while (window.isOpen()) {
		sf::Event evt;
		if (window.pollEvent(evt)) {
			switch (evt.type) {
			case sf::Event::KeyReleased:
				switch (evt.key.code) {
				case sf::Keyboard::Up:
					menu.MoveUp();
					break;
				case sf::Keyboard::Down:
					menu.MoveDown();
					break;

				case sf::Keyboard::Return:
					if (menu.menunumbers == 0) {
						switch (menu.GetPressedItem())
						{
						case 0:
							cout << "Play Button has been Pressed" << endl;
							menu.menunumbers = 1;
						case sf::Keyboard::Return:
							break;
						case 1:
							cout << "Option Button has been Pressed" << endl;
							break;
						case 2:
							window.close();
							break;
						}
					}
					else if (menu.menunumbers == 1) {
						switch (menu.GetPressedItem2()) {
						case 0:
							cout << "Snake Game has Started" << endl;
							Snake();
							break;
						case 1:
							cout << "Doodle Jump Game has Started" << endl;
							DoodleJump();
							break;
						case 2:
							cout << "Tetris Game has Started" << endl;
							Tetris3();
							break;
						case 3:
							cout << "Return Button has been Pressed" << endl;
							menu.menunumbers = 0;
						}
					}
				}
				break;
			case sf::Event::Closed:
				window.close();
				return EXIT_SUCCESS;
				break;
			case sf::Keyboard::Escape:
				window.close();
				return EXIT_SUCCESS;
				break;
			}
		}
		window.clear();
		window.draw(menu.background);
		menu.draw(window);
		window.display();
	}
}
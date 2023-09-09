#ifndef MENU_H
#define MENU_H

#define MAX_MUMBER_OF_ITEMS 3
#define MAX_MUMBER_OF_ITEMS2 4
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

class Menu
{
	public:
		Menu(float Width, float Height);
		~Menu();
		sf::Texture backgroundTexture;
		sf::Sprite backgroundSprite;
		sf::RectangleShape background;
		void setbackground(float Width, float Height);
		void draw(sf::RenderWindow& Window);
		void MoveUp();
		void MoveDown();
		int GetPressedItem() {
			return selectedItemIndex;
		}
		int GetPressedItem2() {
			return selectedItemIndex2;
		}
		int menunumbers = 0;
	private:
		int selectedItemIndex;
		int selectedItemIndex2;
		sf::Font font;
		sf::Text menu[MAX_MUMBER_OF_ITEMS], gamemenu[MAX_MUMBER_OF_ITEMS2];
		sf::FloatRect menuBounds[MAX_MUMBER_OF_ITEMS], gamemenuBounds[MAX_MUMBER_OF_ITEMS2];
};

#endif // !MENU_H

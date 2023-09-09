#include "Menu.h"

Menu::Menu( float Width, float Height) {
	if (!font.loadFromFile("segoeui.ttf")) {
		cout<<"Can't load font file";
	}

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Play");

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Option");

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Exit");

	gamemenu[0].setFont(font);
	gamemenu[0].setFillColor(sf::Color::Red);
	gamemenu[0].setString("Snake");

	gamemenu[1].setFont(font);
	gamemenu[1].setFillColor(sf::Color::White);
	gamemenu[1].setString("Doodle Jump");

	gamemenu[2].setFont(font);
	gamemenu[2].setFillColor(sf::Color::White);
	gamemenu[2].setString("Tetris");

	gamemenu[3].setFont(font);
	gamemenu[3].setFillColor(sf::Color::White);
	gamemenu[3].setString("Return");

	for (int i = 0; i < MAX_MUMBER_OF_ITEMS; i++) {
		menu[i].setCharacterSize(35);
		menuBounds[i] = menu[i].getLocalBounds();
		menu[i].setStyle(sf::Text::Bold);
		menu[i].setOutlineColor(sf::Color::Blue);
		menu[i].setOutlineThickness(1);
	}

	for (int i = 0; i < MAX_MUMBER_OF_ITEMS2; i++) {
		gamemenu[i].setCharacterSize(35);
		gamemenuBounds[i] = gamemenu[i].getLocalBounds();
		gamemenu[i].setStyle(sf::Text::Bold);
		gamemenu[i].setOutlineColor(sf::Color::Blue);
		gamemenu[i].setOutlineThickness(1);
	}

	menu[0].setPosition(sf::Vector2f((Width - menuBounds[0].width) / 2.0f, Height / (MAX_MUMBER_OF_ITEMS + 1) * 1));
	menu[1].setPosition(sf::Vector2f((Width - menuBounds[1].width) / 2.0f, Height / (MAX_MUMBER_OF_ITEMS + 1) * 2));
	menu[2].setPosition(sf::Vector2f((Width - menuBounds[2].width) / 2.0f, Height / (MAX_MUMBER_OF_ITEMS + 1) * 3));
	gamemenu[0].setPosition(sf::Vector2f((Width - gamemenuBounds[0].width) / 2.0f, Height / (MAX_MUMBER_OF_ITEMS2 + 1) * 1));
	gamemenu[1].setPosition(sf::Vector2f((Width - gamemenuBounds[1].width) / 2.0f, Height / (MAX_MUMBER_OF_ITEMS2 + 1) * 2));
	gamemenu[2].setPosition(sf::Vector2f((Width - gamemenuBounds[2].width) / 2.0f, Height / (MAX_MUMBER_OF_ITEMS2 + 1) * 3));
	gamemenu[3].setPosition(sf::Vector2f((Width - gamemenuBounds[2].width) / 2.0f, Height / (MAX_MUMBER_OF_ITEMS2 + 1) * 4));

	selectedItemIndex = 0;
	selectedItemIndex2 = 0;
}

Menu::~Menu() {

}

void Menu::draw(sf::RenderWindow& window) {
	if (menunumbers == 0) {
		for (int i = 0; i < MAX_MUMBER_OF_ITEMS; i++) {
			window.draw(menu[i]);
		}
	}
	else if (menunumbers == 1) {
		for (int i = 0; i < MAX_MUMBER_OF_ITEMS2; i++) {
			window.draw(gamemenu[i]);
		}
	}
	/*for (int i = 0; i < MAX_MUMBER_OF_ITEMS; i++) {  if your maxmumberofitems are the same
		window.draw(menunumbers==0 ? menu[i] : gamemenu[i]); 
	}*/
}

void Menu::MoveUp() {
	if (menunumbers == 0) {
		if (selectedItemIndex >= 0) {
			menu[selectedItemIndex].setFillColor(sf::Color::White);
			selectedItemIndex--;
			if (selectedItemIndex == -1) {
				selectedItemIndex = 2;
			}
			menu[selectedItemIndex].setFillColor(sf::Color::Red);
		}
	}
	if (menunumbers == 1) {
		if (selectedItemIndex2 >= 0) {
			gamemenu[selectedItemIndex2].setFillColor(sf::Color::White);
			selectedItemIndex2--;
			if (selectedItemIndex2 == -1) {
				selectedItemIndex2 = 3;
			}
			gamemenu[selectedItemIndex2].setFillColor(sf::Color::Red);
		}
	}
}

void Menu::MoveDown() {
	if (menunumbers == 0) {
		if (selectedItemIndex + 1 <= MAX_MUMBER_OF_ITEMS) {
			menu[selectedItemIndex].setFillColor(sf::Color::White);
			selectedItemIndex++;
			if (selectedItemIndex == 3) {
				selectedItemIndex = 0;
			}
			menu[selectedItemIndex].setFillColor(sf::Color::Red);
		}
	}
	if (menunumbers == 1) {
		if (selectedItemIndex2 + 1 <= MAX_MUMBER_OF_ITEMS2) {
			gamemenu[selectedItemIndex2].setFillColor(sf::Color::White);
			selectedItemIndex2++;
			if (selectedItemIndex2 == 4) {
				selectedItemIndex2 = 0;
			}
			gamemenu[selectedItemIndex2].setFillColor(sf::Color::Red);
		}
	}

}

void Menu::setbackground(float Width, float Height) {
	background.setSize(sf::Vector2f(Width, Height));
	if (!(backgroundTexture.loadFromFile("background.png"))) {
		cout << "Can't load background image" << endl;
	}
	background.setTexture(&backgroundTexture);
}
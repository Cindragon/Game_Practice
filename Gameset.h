#ifndef GAMESET_H
#define GAMESET_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstring>
#include <ctime>
#include <random>
#include <fstream>
using namespace std;

class Gamedata {
	public:
		int score;
		Gamedata();
		~Gamedata();
		void setGamefont(sf::Font& font);
		void setDeadText(sf::Text& text, sf::Font& font);
		void setscoreText(sf::Text& text, sf::Font& font);
		void draw(sf::RenderWindow& window, sf::Text& scoreText, sf::Text& hscoreText, sf::Text& deadText, sf::Vector2f WindowSize, const int MAX_Text_Index);
		sf::Clock clock;
	private:
		sf::Text text;
		sf::Font font;

};

#endif // !GAMESET_H
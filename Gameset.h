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
		sf::Text scoreText, deadText, hscoreText, pauseText, nextText, levelText;
		void setGamefont(sf::Font& font);
		void setDeadText(sf::Text& text, sf::Font& font);
		void setscoreText(sf::Text& text, sf::Font& font);
		void setpauseText(sf::Text& text, sf::Font& font);
		void setlevelText(sf::Text& text, sf::Font& font);
		void draw(sf::RenderWindow& window, sf::Text& deadText, sf::Text& scoreText, sf::Text& hscoreText, sf::Vector2f WindowSize, const int MAX_Text_Index);
		sf::Clock clock;
		bool IsPaused, isDead;
	private:
		sf::Text text;
		sf::Font font;
};

#endif // !GAMESET_H
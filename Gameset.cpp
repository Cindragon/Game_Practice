#include "Gameset.h"
using namespace std;

Gamedata::Gamedata() {

}

Gamedata::~Gamedata() {

}

void Gamedata::setGamefont(sf::Font& font) {
	if (!font.loadFromFile("segoeui.ttf")) {
		cout << "Can't read Font file" << endl;
	}
}

void Gamedata::setscoreText(sf::Text& text, sf::Font& font) {
	text.setFont(font);
	text.setCharacterSize(25);
	text.setFillColor(sf::Color::Blue);
	text.setStyle(sf::Text::Bold);
	text.setOutlineColor(sf::Color::White);
	text.setOutlineThickness(1);
	text.setOrigin(0, 0);
}

void Gamedata::setDeadText(sf::Text& text, sf::Font& font) {
	text.setFont(font);
	text.setCharacterSize(25);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::Red);
	text.setString("Game Over!");
	text.setOutlineColor(sf::Color::White);
	text.setOutlineThickness(1);
}

void Gamedata::draw(sf::RenderWindow& window, sf::Text& deadText, sf::Text& scoreText, sf::Text& hscoreText, sf::Vector2f WindowSize, const int MAX_Text_Index) {
	sf::FloatRect deadTextbound = deadText.getLocalBounds();
	sf::FloatRect scoreTextbound = scoreText.getLocalBounds();
	sf::FloatRect hscoreTextbound = hscoreText.getLocalBounds();
	scoreText.setOrigin(0, 0);
	deadText.setPosition(sf::Vector2f((WindowSize.x - deadTextbound.width) / 2.0f, (WindowSize.y - deadTextbound.height) / (MAX_Text_Index + 1) * 1));
	scoreText.setPosition(sf::Vector2f((WindowSize.x - scoreTextbound.width) / 2.0f, (WindowSize.y - deadTextbound.height) / (MAX_Text_Index + 1) * 2));
	hscoreText.setPosition((WindowSize.x - hscoreTextbound.width) / 2.0f, (WindowSize.y - deadTextbound.height) / (MAX_Text_Index + 1) * 3);
	window.draw(deadText);
	window.draw(scoreText);
	window.draw(hscoreText);
}
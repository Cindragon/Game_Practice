#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include "Gameset.h"

int Snake();
class Snakegame :public Gamedata {
	public:
		Snakegame() {
			score = 0;
			ifstream inputFile("Snakehscore.txt");
			if (inputFile.is_open()) {
				// Read numbers from the file
				inputFile >> hscore;
				inputFile.close();
			}
		};
		~Snakegame();
		sf::SoundBuffer eatBuffer,dieBuffer;
		sf::Sound eatSound, dieSound;
		sf::Font Sfont;
		int foodnum = 0, dir = 0;
		int hscore;
		int Size;
		sf::Texture foodTexture, blockTexture, bodyTexture;
		sf::Sprite foodSprite, blockSprite, bodySprite;
		void setenv() {
			blockTexture.loadFromFile("Snakegame/white.png");
			bodyTexture.loadFromFile("Snakegame/red.png");
			foodTexture.loadFromFile("Snakegame/green.png");
			foodSprite = sf::Sprite(foodTexture);
			blockSprite = sf::Sprite(blockTexture);
			bodySprite = sf::Sprite(bodyTexture);
		}
		vector<sf::Vector2f> food;
		void setSFX() {
			eatBuffer.loadFromFile("Snakegame/Coin.wav");
			dieBuffer.loadFromFile("Snakegame/Mariodie.wav");
			dieSound.setBuffer(dieBuffer);
			eatSound.setBuffer(eatBuffer);
		}
	private:

};
#endif // !SNAKEGAME_H
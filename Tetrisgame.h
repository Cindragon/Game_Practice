#pragma once
#include "Gameset.h"
int Tetris();



class TetrisGame : public Gamedata {
	public:

		TetrisGame() {
			srand((unsigned)time(NULL));;
			colorNum = 1 + rand() % 7;
		}
		//~TetrisGame() {
		//};
		sf::Text scoreText, deadText, hscoreText;
		sf::Font font;
		sf::SoundBuffer buffer;
		sf::Sound linesound, backgroundmusic;
		sf::Texture backgroundTexture, yellowTexture, blueTexture, greenTexture,
			light_blueTexture, orangeTexture, purpleTexture, redTexture;
		sf::Sprite backgroundSprite, yellowSprite, blueSprite, greenSprite,
			light_blueSprite, orangeSprite, purpleSprite, redSprite, currentSprite;

		void setblocks() {
			yellowTexture.loadFromFile("Tetrisgame/yellow.png");
			yellowSprite = sf::Sprite(yellowTexture);
			blueTexture.loadFromFile("Tetrisgame/blue.png");
			blueSprite = sf::Sprite(blueTexture);
			greenTexture.loadFromFile("Tetrisgame/green.png");
			greenSprite = sf::Sprite(greenTexture);
			light_blueTexture.loadFromFile("Tetrisgame/light_blue.png");
			light_blueSprite = sf::Sprite(light_blueTexture);
			orangeTexture.loadFromFile("Tetrisgame/orange.png");
			orangeSprite = sf::Sprite(orangeTexture);
			purpleTexture.loadFromFile("Tetrisgame/purple.png");
			purpleSprite = sf::Sprite(purpleTexture);
			redTexture.loadFromFile("Tetrisgame/red.png"); 
			redSprite = sf::Sprite(redTexture);
		}

		void setbackgroud() {
			backgroundTexture.loadFromFile("Tetrisgame/backgroundblack.png");
			backgroundSprite = sf::Sprite(backgroundTexture);
		}

		void setbackground(int groundWidth, int blockWidth, int windowHeight) {
			backgroundTexture.setRepeated(true);
			backgroundSprite = sf::Sprite(backgroundTexture, sf::IntRect(0, 0, groundWidth * blockWidth, windowHeight));
		}

		sf::Sprite setcurrentsprite(int colorNum) {
			switch (colorNum) {
				case 1:
					currentSprite = redSprite;
					break;
				case 2:
					currentSprite = yellowSprite;
					break;
				case 3:
					currentSprite = blueSprite;
					break;
				case 4:
					currentSprite = light_blueSprite;
					break;
				case 5:
					currentSprite = orangeSprite;
					break;
				case 6:
					currentSprite = greenSprite;
					break;
				case 7:
					currentSprite = purpleSprite;
					break;
			}
			return currentSprite;
		}
		int figure[7][4]{
			{2, 5, 8, 11}, //I*
			{4, 5, 7, 8}, //O*
			{5, 8, 7, 10}, //S*
			{5, 8, 7, 11}, //T
			{4, 7, 8, 11}, //Z*
			{4, 7, 10, 11}, //L
			{5, 8, 11, 10}, //J
		};
		int colorNum = 0;
		void checkelined(int groundWidth, int fieldHeight, int field[10][20], int& line) {
			int posH = fieldHeight - 1;
			for (int i = fieldHeight-1; i > 0; i--) {
				int count = 0;
				for (int j = 0; j < groundWidth; j++) {
					if (field[j][i])
						count++;
					field[j][posH] = field[j][i];
				}
				if (count < groundWidth)
					posH--;
			}
		}

		sf::Clock Tclock;

	private:
};

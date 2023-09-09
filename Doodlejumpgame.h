#ifndef DOODLEJUMPGAME_H
#define DOODLEJUMGAME_H


#include "Gameset.h"
#include <math.h>
using namespace std;
int DoodleJump();
class Doodlejumpgame : public Gamedata {
	public:
		sf::Texture doodletexture, platformtexture, backgroundtexture;
		sf::Sprite doodlesprite, platformsprite, backgroundsprite;
		sf::Font font;
		sf::SoundBuffer jumpBuffer, fallBuffer;
		sf::Sound jumpSound, fallSound;
		sf::Text scoreText, deadText, hscoreText;
		int score = 0, hscore;
		int Windowwidth = 400;
		int Windowheight = 533;

		Doodlejumpgame() {
			ifstream inputFile("Doodlejumphscore.txt");
			if (inputFile.is_open()) {
				// Read numbers from the file
				inputFile >> hscore;
				inputFile.close();
			}
			doodletexture.loadFromFile("Doodlejumpgame/doodle.png");
			backgroundtexture.loadFromFile("Doodlejumpgame/background.png");
			platformtexture.loadFromFile("Doodlejumpgame/platform.png");
			doodlesprite = sf::Sprite(doodletexture);
			backgroundsprite = sf::Sprite(backgroundtexture);
			platformsprite = sf::Sprite(platformtexture);
			jumpBuffer.loadFromFile("Doodlejumpgame/jump.wav");
			jumpSound.setBuffer(jumpBuffer);
			fallBuffer.loadFromFile("Doodlejumpgame/falling.wav");
			fallSound.setBuffer(fallBuffer);
			fallSound.setVolume(20);
		};
		~Doodlejumpgame();

		sf::Vector2i plat[10] = {};
		void setplat(int w, int h) {
			std::uniform_int_distribution<unsigned> px(0, 400 - w);
			std::uniform_int_distribution<unsigned> py(90, 530);
			std::default_random_engine e((unsigned)time(NULL));
			for (int i = 0; i < 10; i++) {
				plat[i].x = px(e);
				plat[i].y = py(e);
				//每兩個平台要有間隔 最大跟最小間隔 rand()%160 +40 (40~199)
				for (int j = 0; j < i; j++) {
					if (plat[i].y == plat[j].y){					 
						std::default_random_engine e((unsigned)time(NULL));
						plat[i].y = py(e);
					}
				}
			}
		}

		void move(int& x) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				x += 3;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				x -= 3;
		}

		void jump(int& playerX, int& playerY, float &dy, sf::Vector2i plat[10]) {
			for (int i = 0; i < 10; i++) {
				if ((playerX + 50 > plat[i].x) && (playerX + 20 < plat[i].x + 68)
					&& (playerY + 70 > plat[i].y) && (playerY + 70 < plat[i].y + 14)
					&& (dy > 0)) {
					dy = -10.f;
					jumpSound.play();
				}
			}
		}

	private:

};

#endif // !DOODLEJUMPGAME_H
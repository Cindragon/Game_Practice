#ifndef DOODLEJUMPGAME_H
#define DOODLEJUMPGAME_H

#include "Gameset.h"
using namespace std;
int DoodleJump();
class Doodlejumpgame : public Gamedata {
	public:
		sf::Texture doodletexture, platformtexture, backgroundtexture;
		sf::Sprite doodlesprite, platformsprite, backgroundsprite;
		sf::Font font;
		sf::SoundBuffer jumpBuffer, fallBuffer;
		sf::Sound jumpSound, fallSound;
		int hscore;
		int Windowwidth = 400;
		int Windowheight = 533;

		Doodlejumpgame() {
			score = 0;
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
				for (int j = 0; j < i; j++) {
					if (plat[i].y == plat[j].y) {
						plat[i].y = py(e);
					}
				}
			}
		}

		void move(int& x, int& speed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				x += speed;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				x -= speed;
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
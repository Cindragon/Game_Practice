#include "Tetrisgame.h"
#include <iostream>
using namespace std;

const int fieldWidth = 14;
const int groundWidth = 10;
const int fieldHeight = 20;
int field[groundWidth][fieldHeight] = {};

struct Point {
	int x, y;
} a[4], b[4], p;

bool check()
{
	for (int i = 0; i < 4; i++)
		if (a[i].x < 0 || a[i].x >= groundWidth || a[i].y >= fieldHeight) return 0;
		else if (field[a[i].x][a[i].y]) return 0;

	return 1;
};

//TetrisGame:: ~TetrisGame() {
//
//}


int Tetris() {
	TetrisGame T;
	Gamedata TG;
	T.setblocks();
	const int blockWidth = T.yellowTexture.getSize().x;
	const int blockHeight = T.yellowTexture.getSize().y;
	sf::Vector2i windowSize(fieldWidth * blockWidth, fieldHeight * blockHeight);

	T.setbackgroud();
	T.setbackground(groundWidth, blockWidth, windowSize.y);

	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));

	TG.setGamefont(T.font);
	TG.setscoreText(T.scoreText, T.font);
	TG.setDeadText(T.deadText, T.font);

	int dx = 0;

	bool rotate = false;
	float timer = 0.f, delay = 0.3f;

	sf::Sprite currentSprite;

	enum class Type {
		None, I, O, S, T, Z, L, J,
	};

	int type[7];
	for (int i = 0; i < 7; i++) {
		type[i] = i;
	}

	Type currentType = Type(rand() % 7 + 1);
	map<Type, sf::Sprite> sprites{
		{ Type::I, T.yellowSprite},
		{ Type::O, T.light_blueSprite },
		{ Type::S, T.orangeSprite },
		{ Type::T, T.blueSprite },
		{ Type::Z, T.redSprite },
		{ Type::L, T.greenSprite },
		{ Type::J, T.purpleSprite },
	};

	//int colorNum = 1 + rand() % 7;
	int n = rand() % 7;
	for (int i = 0; i < 4; i++) {
		a[i].x = T.figure[n][i] % 3;
		a[i].y = T.figure[n][i] / 3;
	}

	int line = 0;

	sf::RenderWindow Twindow(sf::VideoMode(windowSize.x, windowSize.y), "Tetris Game");
	while (Twindow.isOpen()) {

		T.currentSprite = T.setcurrentsprite(T.colorNum);
		float timepass = T.clock.getElapsedTime().asSeconds();
		T.clock.restart();
		timer += timepass;
		//T.check(T.a, fieldWidth, fieldHeight, field, check);
		sf::Event Tevt;
		while (Twindow.pollEvent(Tevt)) {
			if (Tevt.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				Twindow.close();
				return EXIT_SUCCESS;
			}
			if (Tevt.type == sf::Event::KeyPressed) {
				switch (Tevt.key.code) {
					case (sf::Keyboard::Up):
						rotate = true;
						break;
					case (sf::Keyboard::Right):
						dx=1;
						break;
					case (sf::Keyboard::Left):
						dx=-1;
						break;
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			delay = 0.05f;
		////Move////
		//T.blockMove(a, b, dx);

		for (int i = 0; i < 4; i++) {
			b[i] = a[i];
			a[i].x += dx;
		}

		if (!check()) {
			for (int i = 0; i < 4; i++)
				a[i] = b[i];
		}
		//T.blockMovecheck(T.a, T.b, check);

		////Rotate////
		if (rotate) {
			//T.Rotate(p, a, b);
			p = a[1]; //center of Rotation
			for (int i = 0; i < 4; i++) {
				int x = a[i].y - p.y;
				int y = a[i].x - p.x;
				a[i].x = p.x - x;
				a[i].y = p.y + y;
			}
			if (!check()) {
				for (int i = 0; i < 4; i++) {
					a[i] = b[i];
				}
			}
		}

		////Tick////
		if (timer > delay) {
			//srand(time(0));
			for (int i = 0; i < 4; i++) {
				b[i] = a[i];
				a[i].y += 1;
			}
			if (!check()) {
				for (int i = 0; i < 4; i++) {
					field[b[i].x][b[i].y] = T.colorNum;
				}
				T.colorNum = 1 + rand() % 7;
				int n = rand()%7;
				for (int i = 0; i < 4; i++) {
					a[i].x = T.figure[n][i] % 3;
					a[i].y = T.figure[n][i] / 3;
				}
			}
			timer = 0;
		};

		T.checkelined(groundWidth, fieldHeight, field, line);

		dx = 0;
		rotate = false;
		delay = 0.3f;
		Twindow.clear(sf::Color::White);
		Twindow.draw(T.backgroundSprite);

		for (int i = 0; i < groundWidth; i++) {
			for (int j = 0; j < fieldHeight; j++) {
				T.currentSprite = T.setcurrentsprite(field[i][j]);
				sf::Sprite& s = T.currentSprite;
				if (field[i][j] == false)
					continue; 
				if (field[i][j] == 1) {
					s.setPosition((float)i * blockWidth, (float)j * blockHeight);
					Twindow.draw(s);
				}
				if (field[i][j] == 2) {
					//sf::Sprite& s = T.yellowSprite;
					s.setPosition((float)i * blockWidth, (float)j * blockHeight);
					Twindow.draw(s);
				}
				if (field[i][j] == 3) {
					//sf::Sprite& s = T.blueSprite;
					s.setPosition((float)i * blockWidth, (float)j * blockHeight);
					Twindow.draw(s);
				}
				if (field[i][j] == 4) {
					//sf::Sprite& s = T.light_blueSprite;
					s.setPosition((float)i * blockWidth, (float)j * blockHeight);
					Twindow.draw(s);
				}
				if (field[i][j] == 5) {
					//sf::Sprite& s = T.orangeSprite;
					s.setPosition((float)i * blockWidth, (float)j * blockHeight);
					Twindow.draw(s);
				}
				if (field[i][j] == 6) {
					//sf::Sprite& s = T.greenSprite;
					s.setPosition((float)i * blockWidth, (float)j * blockHeight);
					Twindow.draw(s);
				}
				if (field[i][j] == 7) {
					//sf::Sprite& s = T.purpleSprite;
					s.setPosition((float)i * blockWidth, (float)j * blockHeight);
					Twindow.draw(s);
				}
			}
		}
		for (int i = 0; i < 4; i++) {
			T.currentSprite = T.setcurrentsprite(T.colorNum);
			T.currentSprite.setPosition((float)(a[i].x)* blockWidth, (float)(a[i].y)* blockHeight);
			Twindow.draw(T.currentSprite);
		}
		//Twindow.draw(T.deadText);
		Twindow.display();
	}
}

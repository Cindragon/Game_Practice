#include "Snakegame.h"
using namespace std;

Snakegame::~Snakegame() {

}

Snakegame S;
sf::Vector2i FieldSize(30, 20);
int Size = 16;
sf::Vector2f WindowSize((float)Size* FieldSize.x, (float)Size* FieldSize.y);
int foodnum = 0;
int bodylength = 4, dir;
bool isdead = false, eaten = false;


struct Snake {
	int x, y;
} s[100];

void setfoodpos() {
	srand((unsigned)time(NULL));
	for (int i = 0; i < 3; i++) {
		S.food.push_back(sf::Vector2f((float)(rand() % FieldSize.x), (float)(rand() % FieldSize.y)));
	}
}
void Move() {
	for (int i = bodylength; i >0; i--) {
		s[i].x = s[i - 1].x;
		s[i].y = s[i - 1].y;
	}

	if (dir == 0) s[0].y+=1;
	if (dir == 1) s[0].x+=1;
	if (dir == 2) s[0].y-=1;
	if (dir == 3) s[0].x-=1;

	for (int i = 0; i < 3; i++) {
		if (s[0].x == S.food[i].x && s[0].y == S.food[i].y) {
			eaten = true;
			S.dieSound.setVolume(20);
			S.eatSound.play();
			bodylength++;
			foodnum++;
			S.score = foodnum * 10;

			if (S.score > S.hscore) {
				S.hscore = S.score;
				ofstream outputFile("Snakehscore.txt");
				// Write modified numbers to the file
				outputFile << S.hscore;
				outputFile.close();
			}

			while (true) {
				S.food[i].x = float(rand() % FieldSize.x);
				S.food[i].y = float(rand() % FieldSize.y);
				bool check = false;
				for (int j = 0; j < bodylength; j++) {
					if (S.food[i].x == s[j].x &&
						S.food[i].y == s[j].y) {
						check = true;
						break;
					}
				}
				if (!check) break;
			}
		}
		eaten = false;
	}

	if (s[0].x >= FieldSize.x || s[0].x<0 ||
		s[0].y>=FieldSize.y || s[0].y <0) {
		isdead = true;
		S.dieSound.setVolume(30);
		S.dieSound.play();
	}

	for (int i = 1; i < bodylength; i++) {
		if (s[0].x == s[i].x && s[0].y == s[i].y) {
			isdead = true;
			S.dieSound.setVolume(30);
			S.dieSound.play();

		}
	}
}

int Snake() {
	memset(s, 0, sizeof(s));

	for (int i = 0; i < bodylength; i++) {
		s[i].x = 2;
		s[i].y = 5 - i;
	}

	S = Snakegame();
	bodylength = 4;
	foodnum = 0;
	isdead = false;
	srand((unsigned)time(NULL));
	S.setenv();
	S.setSFX();
	sf::RenderWindow Swindow(sf::VideoMode((unsigned int)WindowSize.x, (unsigned int)WindowSize.y),"Snake Game");

	const int MAX_Text_Index = 3;
	setfoodpos();
	S.setGamefont(S.Sfont);
	S.setscoreText(S.scoreText, S.Sfont);
	S.setscoreText(S.hscoreText, S.Sfont);
	S.setDeadText(S.deadText, S.Sfont);

	while (Swindow.isOpen()) {
		sf::Event Sevt;
		if (Swindow.pollEvent(Sevt)) {
			if (Sevt.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				Swindow.close();
				return EXIT_SUCCESS;
			}
			if (Sevt.type == sf::Event::KeyPressed) {
				switch (Sevt.key.code) {
					case(sf::Keyboard::Down):
						if(dir!=2)
							dir = 0;
						break;
					case(sf::Keyboard::Right):
						if(dir!=3)
							dir = 1;
						break;
					case(sf::Keyboard::Up):
						if(dir!=0)
							dir = 2;
						break;
					case(sf::Keyboard::Left):
						if(dir!=1)
							dir = 3;
						break;
				}
			}
		}
		if (S.clock.getElapsedTime().asSeconds() >= 0.1f&&!isdead) {
			Move();
			S.clock.restart();
		}
		
		Swindow.clear();

		for (int i = 0; i < FieldSize.x; i++) {
			for (int j = 0; j < FieldSize.y; j++) {
				S.blockSprite.setPosition(float(i * Size), float(j * Size));
				Swindow.draw(S.blockSprite);
			}
		}

		for (int i = 0; i < bodylength; i++) {
			S.bodySprite.setPosition((float)s[i].x*Size, (float)s[i].y*Size);
			Swindow.draw(S.bodySprite);
		}

		for (int i = 0; i < 3; i++) {
			S.foodSprite.setPosition(S.food[i].x * Size, S.food[i].y * Size);
			Swindow.draw(S.foodSprite);
		}

		S.scoreText.setString("Score: " + to_string(S.score));
		S.hscoreText.setString("Hightest Score: " + to_string(S.hscore));
		sf::FloatRect scoreTextBounds = S.scoreText.getLocalBounds();
		S.scoreText.setOrigin((scoreTextBounds.width) + 5, 0.f);
		S.scoreText.setPosition(WindowSize.x, 0);
		Swindow.draw(S.scoreText);

		if (isdead) {
			S.draw(Swindow, S.deadText, S.scoreText, S.hscoreText, WindowSize, MAX_Text_Index);
		}
		Swindow.display();
	}
}
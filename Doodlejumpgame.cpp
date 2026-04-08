# include "Doodlejumpgame.h"
using namespace std;

Doodlejumpgame::~Doodlejumpgame() {
};

int DoodleJump() {
	const int MAX_Text_Index = 3;
	srand((unsigned)time(NULL));
	Doodlejumpgame D;
	sf::Vector2f WindowSize((float)D.Windowwidth, (float)D.Windowheight);
	sf::RenderWindow Dwindow(sf::VideoMode((unsigned int)WindowSize.x, (unsigned int)WindowSize.y), "Doodle Game");
	Dwindow.setFramerateLimit(60);

	D.setGamefont(D.font);

	int pWidth = D.platformtexture.getSize().x;
	int pHeight = D.platformtexture.getSize().y;
	D.setplat(pWidth, pHeight);

	D.setscoreText(D.scoreText, D.font);
	D.setscoreText(D.hscoreText, D.font);
	D.setDeadText(D.deadText, D.font);
	D.setlevelText(D.levelText, D.font);
	sf::FloatRect deadTextbound = D.deadText.getLocalBounds();

	int playerX = 100, playerY = 100, h = 200, level = 1, speed = 3;
	float dy = 0.f;
	bool isDead = false;
	D.IsPaused=false;

	while (Dwindow.isOpen()) {
		sf::Event Devt;
		if (Dwindow.pollEvent(Devt)) {
			if (Devt.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				Dwindow.close();
				return EXIT_SUCCESS;
			}
		}
		D.move(playerX, speed);

		dy += 0.2f;
		playerY += dy;
		if (playerY < h) {
			for (int i = 0; i < 10; i++) {
				playerY = h;
				D.plat[i].y = (unsigned)(D.plat[i].y - dy);
				if (D.plat[i].y > 553) {
					D.plat[i].y = 0;
					D.plat[i].x = rand() % (int (WindowSize.x) - pWidth);
				}
			}
		}

		if (playerY == h && dy < (-1.62)) {
			D.score++;
			if (D.score % 300 == 0) {
				level++;
				speed = (int)(speed * 1.5);
				cout << speed << endl;
			}
			if (D.score > D.hscore) {
				D.hscore = D.score;
				ofstream outputFile("Doodlejumphscore.txt");
				// Write modified numbers to the file
				outputFile << D.hscore;
				outputFile.close();
			}
		}

		D.jump(playerX, playerY, dy, D.plat);
		Dwindow.clear();
		Dwindow.draw(D.backgroundsprite);
		Dwindow.draw(D.doodlesprite);

		D.doodlesprite.setPosition(float(playerX), float(playerY));
		for (int i = 0; i < 10; i++) {
			D.platformsprite.setPosition(float(D.plat[i].x), float(D.plat[i].y));
			Dwindow.draw(D.platformsprite);
		}

		if (playerX > WindowSize.x)
			playerX = 0;
		if (playerX < 0)
			playerX = (int)(WindowSize.x - D.doodletexture.getSize().x);

		D.scoreText.setString("Score: " + to_string(int(D.score) / 10));
		D.hscoreText.setString("Highest Score: " + to_string(int(D.hscore) / 10));
		sf::FloatRect scoreTextBound = D.scoreText.getLocalBounds();
		D.scoreText.setOrigin((scoreTextBound.width) + 5, 0.f);
		D.scoreText.setPosition(WindowSize.x, 0);
		Dwindow.draw(D.scoreText);
		D.levelText.setString("Level: " + to_string(level));
		D.levelText.setPosition(2, 0);
		Dwindow.draw(D.levelText);
		if (D.doodlesprite.getPosition().y > 500 && !isDead) {
			isDead = true;
			D.fallSound.play();
		}
		if (isDead) {
			D.draw(Dwindow, D.deadText, D.scoreText, D.hscoreText, WindowSize, MAX_Text_Index);
		}

		Dwindow.display();
	}
}
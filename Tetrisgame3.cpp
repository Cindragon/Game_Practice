#include "Tetrisgame3.h"
using namespace std;

TetrisGame3::~TetrisGame3() {

}

int Tetris3() {
	TetrisGame3 T3;

	T3.setblocks();
	T3.setbackgroud();
	T3.IsPaused = false;
	const int MAX_Text_Index = 3;
	int currentIndex = 0, nextIndex =0;

	const int blockWidth = T3.yellowTexture.getSize().x;
	const int blockHeight = T3.yellowTexture.getSize().y;
	const int windowWidth = fieldWidth * blockWidth;
	const int windowHeight = fieldHeight * blockHeight;

	sf::Vector2f fieldSize(groundWidth * blockWidth, fieldHeight * blockHeight);
	sf::Vector2f WindowSize(windowWidth, windowHeight);
	T3.setbackgroundsize(groundWidth, blockWidth, windowHeight);
	sf::RectangleShape backgroundZone;
	backgroundZone.setSize(sf::Vector2f(WindowSize.x, WindowSize.y));
	if (!(T3.backgroundZoneTexture.loadFromFile("Tetrisgame/backgroundzone.png"))) {
		cout << "Can't load background image" << endl;
	}
	backgroundZone.setTexture(&T3.backgroundZoneTexture);

	const sf::Vector2i origin(groundWidth / 2, 0);
	const sf::Vector2i savedorigin(12, 5);
	sf::Vector2i pos(origin);
	sf::Vector2i savedpos(savedorigin);
	bool isDead = false;
	bool isLined = false;
	//bool isChange = false;
	int level = 1;
	T3.setGamefont(T3.font);
	T3.setscoreText(T3.scoreText, T3.font);
	T3.setscoreText(T3.hscoreText, T3.font);
	T3.setDeadText(T3.deadText, T3.font);
	T3.setscoreText(T3.nextText, T3.font);
	T3.nextText.setCharacterSize(32);
	T3.setpauseText(T3.pauseText, T3.font);
	T3.setlevelText(T3.levelText, T3.font);
	T3.setsoundandbuffer();

	sf::RenderWindow Twindow(sf::VideoMode(WindowSize.x, WindowSize.y), "Tetrisgame");
	float delay = 0.3f;

	while (Twindow.isOpen()) {
		T3.setcurrentTetris(currentIndex, T3.currentType, T3.savedType);
		enum class Action {
			Hold,
			MoveDown,
			MoveRight,
			MoveLeft,
			Rotate,
			Pause,
			Change,
		};

		Action action = Action::Hold;
		sf::Event Tevt;

		if (Twindow.pollEvent(Tevt)) {
			if (Tevt.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
				Twindow.close();
				return EXIT_SUCCESS;
			}
			if (Tevt.type == sf::Event::KeyPressed) {
				switch (Tevt.key.code) {
				case sf::Keyboard::Left:
					action = Action::MoveLeft;
					break;
				case sf::Keyboard::Right:
					action = Action::MoveRight;
					break;
				case sf::Keyboard::Down:
					action = Action::MoveDown;
					break;
				case sf::Keyboard::Up:
					action = Action::Rotate;
					break;
				case sf::Keyboard::Space:
					action = Action::Pause;
					T3.IsPaused = !T3.IsPaused;
					cout << "Paused!" << endl;
					break;
				//case sf::Keyboard::Space:
				//	action = Action::Change;
				//	break;
				}
			}
		}
		if (isDead)
			continue;
		if (T3.clock.getElapsedTime().asSeconds() >= delay&&!T3.IsPaused&&!isDead) {
			action = Action::MoveDown;
			T3.clock.restart();
		};

		sf::Vector2i nextPos(pos);
		int nextIndex = currentIndex;
		if (action == Action::Rotate) {
			nextIndex = (nextIndex + 1) % T3.shapes[T3.currentType].size();
		}

		vector<sf::Vector2i> nextShape = T3.shapes[T3.currentType][nextIndex];
		switch (action) {
		case Action::Hold:
			break;
		case Action::MoveDown:
			delay = 0.05f;
			nextPos.y++;
			break;
		case Action::MoveLeft:
			nextPos.x--;
			break;
		case Action::MoveRight:
			nextPos.x++;
			break;
		case Action::Pause:
			break;
		//case Action::Change:
		//	isChange = true;
		}

		delay = 0.3f;
		int countEmpty = 0;

		Twindow.clear();
		Twindow.draw(backgroundZone);
		Twindow.draw(T3.backgroundSprite);
		if (T3.IsPaused) {
			sf::FloatRect pauseTextbound = T3.pauseText.getLocalBounds();
			T3.pauseText.setOrigin(0, 0);
			T3.pauseText.setPosition(sf::Vector2f((WindowSize.x - pauseTextbound.width) / 2.0f, (WindowSize.y - pauseTextbound.height) / 2.0f));
			Twindow.draw(T3.pauseText);
		}
		for (const sf::Vector2i d : nextShape) {
			sf::Vector2i np = nextPos + d;
			if (np.x >= 0 && np.x < groundWidth &&
				np.y >= 0 && np.y < fieldHeight &&
				(np.y < 0 || T3.field[np.x][np.y] == Type::None)) {
				countEmpty++;
			}
		}

		if (countEmpty == 4) {
			pos = nextPos;
			currentIndex = nextIndex;
			T3.currentShape = nextShape;
		}
		else {
			if (action == Action::MoveDown) {
				for (const sf::Vector2i& d : T3.currentShape) {
					sf::Vector2i np = pos + d;
					if (np.y >= 0) {
						T3.field[np.x][np.y] = T3.currentType;
					}
					else{
						action = Action::Hold;
						isDead = true;
					}
				}
				for (int y = 0; y < fieldHeight; y++) {
					bool isFull = true;
					for (int x = 0; x < groundWidth; x++) {
						if (T3.field[x][y] == Type::None) {
							isFull = false;
						}
					}
					if (isFull) {
						T3.line++;
						if (T3.line % 3 == 0) {
							level++;
							delay *= 0.9;
							cout << delay<<endl;
						}
						T3.score = T3.line * 100;
						if (T3.score > T3.hscore) {
							T3.hscore = T3.score;
							ofstream outputFile("Tetrishscore.txt");
							// Write modified numbers to the file
							outputFile << T3.hscore;
							outputFile.close();
						}
						isLined = true;
						if (isLined) {
							T3.linedmusic.play();
							isLined = false;
						}
						for (int ty = y; ty > 0; ty--) {
							for (int x = 0; x < groundWidth; x++) {
								T3.field[x][ty] = T3.field[x][ty - 1];
							}
						}
						for (int x = 0; x < groundWidth; x++) {
							T3.field[x][0] = Type::None;
						}
					}
				}
				pos = origin;
				T3.currentType = T3.savedType;  //
				srand((unsigned)time(NULL));
				T3.savedType = Type(rand() % 7 + 1);  //
				currentIndex = 0;
			}
		}

		// Draw placed blocks
		for (int x = 0; x < groundWidth; x++) {
			for (int y = 0; y < fieldHeight; y++) {
				if (T3.field[x][y] == Type::None)
					continue;
				sf::Sprite& s = T3.sprites[T3.field[x][y]];
				s.setPosition(float(x * blockWidth), float(y * blockHeight));
				Twindow.draw(s);
			}
		}

		// Draw current falling piece
		for (const sf::Vector2i& d : T3.currentShape) {
			sf::Vector2i np = pos + d;
			T3.currentSprite.setPosition(
				float(np.x * blockWidth),
				float(np.y * blockHeight));
			Twindow.draw(T3.currentSprite);
		}

		for (const sf::Vector2i& d : T3.savedShape) {
			sf::Vector2i np = savedpos + d;
			T3.savedSprite.setPosition(
				float(np.x * blockWidth),
				float(np.y * blockHeight));
			Twindow.draw(T3.savedSprite);

		}

		Twindow.draw(T3.scoreText);
		T3.scoreText.setString("Score: " + to_string(T3.score));
		T3.hscoreText.setString("Highest Score: " + to_string(T3.hscore));
		T3.nextText.setString("NEXT");
		sf::FloatRect scoreTextBound = T3.scoreText.getLocalBounds();
		T3.scoreText.setOrigin((scoreTextBound.width) + 5, 0.f);
		T3.scoreText.setPosition((float)WindowSize.x, 0);
		T3.nextText.setPosition(fieldSize.x + blockWidth*1.5, T3.scoreText.getPosition().y + blockHeight*2);
		Twindow.draw(T3.nextText);
		T3.levelText.setString("Level: " + to_string(level));
		T3.levelText.setPosition(2, 0);
		Twindow.draw(T3.levelText);
		//if (isChange) {
		//	T3.tempType = T3.currentType;
		//	T3.currentType = T3.savedType;
		//	T3.savedType = T3.tempType;
		//	isChange = false;
		//}

		if (isDead) {
			T3.backgroundmusic.stop();
			T3.draw(Twindow, T3.deadText, T3.scoreText, T3.hscoreText, fieldSize, MAX_Text_Index);
		}

		Twindow.display();
	}
}

/*Photo by <a href="https://unsplash.com/@zane404?utm_source=unsplash&utm_medium=referral&utm_content=creditCopyText">Zane Lee</a> 
on <a href="https://unsplash.com/photos/IHj0xtWtLKE?utm_source=unsplash&utm_medium=referral&utm_content=creditCopyText">Unsplash</a> */ 

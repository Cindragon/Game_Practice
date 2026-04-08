#pragma once
#ifndef TETRISGAME3_H
#define TETRISGAME3_H

#include "Gameset.h"
const int fieldWidth = 15;
const int fieldHeight = 20;
const int groundWidth = 10;

enum class Type {
	None,
	O,
	I,
	L,
	J,
	T,
	Z,
	S
};

int Tetris3();
class TetrisGame3 : public Gamedata {
	public:
		Type currentType = Type::None;
		Type savedType = Type::None;
		Type tempType = Type::None;
		TetrisGame3() {
			srand((unsigned)time(NULL));
			currentType = Type(rand()%7+1);
			srand((unsigned)time(NULL));
			savedType = Type(rand() % 7 + 1);
			ifstream inputFile("Tetrishscore.txt");
			if (inputFile.is_open()) {
				// Read numbers from the file
				inputFile >> hscore;
				inputFile.close();
			}
		};
		~TetrisGame3();
		int score = 0, hscore, line=0;
		sf::Font font;
		sf::SoundBuffer lined;
		sf::Sound linedmusic;
		sf::Music backgroundmusic;
		sf::Texture backgroundTexture, yellowTexture, blueTexture, greenTexture,
			light_blueTexture, orangeTexture, purpleTexture, redTexture, backgroundZoneTexture;

		sf::Sprite backgroundSprite, yellowSprite, blueSprite, greenSprite,
			light_blueSprite, orangeSprite, purpleSprite, redSprite, currentSprite, savedSprite;

		vector<sf::Vector2i> currentShape, nextShape, savedShape;

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

			sprites[Type::O] = yellowSprite;
			sprites[Type::I] = light_blueSprite;
			sprites[Type::L] = orangeSprite;
			sprites[Type::J] = blueSprite;
			sprites[Type::T] = redSprite;
			sprites[Type::Z] = greenSprite;
			sprites[Type::S] = purpleSprite;
		}
		Type field[groundWidth][fieldHeight] = {};

		map <Type, vector<vector<sf::Vector2i>>> shapes = {
{
	Type::O,
	{
				//Oガㅸ락:		OO	(0,-1) (1,-1)
				//				OO	(0, 0) (1, 0) (0,0)	О�_헕
					{
						sf::Vector2i(0, 0),
						sf::Vector2i(1, 0),
						sf::Vector2i(0, -1),
						sf::Vector2i(1, -1),
					}
				},
			},
			{
				Type::I,
				{

				//Iガ:			O (0, -1)	(0, 0)О�_헕 	shape_Is[0]
				//				O (0, 0)
				//				O (0, 1)
				//				O (0, 2)
					{
						sf::Vector2i(0, -1),
						sf::Vector2i(0, 0),
						sf::Vector2i(0, 1),
						sf::Vector2i(0, 2),
					},
					//Iガㅸ락:		OOOO	(-2, 0)(-1, 0)(0, 0)(1, 0)  shape_Is[1]
					{
	
						sf::Vector2i(-2, 0),
						sf::Vector2i(-1, 0),
						sf::Vector2i(0, 0),
						sf::Vector2i(1, 0),
					}
				}
			},
			{
				Type::L,
				{
				//Lガ:		O  (0, -1)
				//			O  (0, 0)
				//			OO (0, 1) (1, 1)
					{
						sf::Vector2i(0, -1),
						sf::Vector2i(0, 0),
						sf::Vector2i(0, 1),
						sf::Vector2i(1, 1),
					},
					//Lガ:		OOO (-1, 0) (0, 0) (1, 0)
					//			O	(-1, 1)
					{
						sf::Vector2i(-1, 0),
						sf::Vector2i(0, 0),
						sf::Vector2i(1, 0),
						sf::Vector2i(-1, 1),
					},
					//Lガ:		OO (-1, -1)(0, -1)
					//			 O (0, 0)
					//			 O (0, 1)
					{
						sf::Vector2i(-1, -1),
						sf::Vector2i(0, -1),
						sf::Vector2i(0, 0),
						sf::Vector2i(0, 1),
					},
					//Lガ:		  O (1, -1)
					//			OOO (-1, 0)(0, 0) (1, 0)
					{
						sf::Vector2i(1, -1),
						sf::Vector2i(-1, 0),
						sf::Vector2i(0, 0),
						sf::Vector2i(1, 0),
					},
				},
			},
			{
				Type::J,
				{
				//		O (0, -1)
				//		O (0, 0)
				//	   OO (-1, 1) (0, 1)
					{
						sf::Vector2i(0, -1),
						sf::Vector2i(0, 0),
						sf::Vector2i(-1, 1),
						sf::Vector2i(0, 1),
					},
					//		O	(-1, -1)
					//		OOO (-1, 0)(0, 0)(1, 0)
					{
						sf::Vector2i(-1, -1),
						sf::Vector2i(-1, 0),
						sf::Vector2i(0, 0),
						sf::Vector2i(1, 0),
					},
					//		 OO (0, -1)(1, -1)
					//		 O  (0, 0)
					//		 O  (0, 1)
					{
						sf::Vector2i(0, -1),
						sf::Vector2i(1, -1),
						sf::Vector2i(0, 0),
						sf::Vector2i(0, 1),
					},
					//		 OOO  (-1,0)(0, 0)(1, 0)
					//		   O  (1, 1)
					{
						sf::Vector2i(-1, 0),
						sf::Vector2i(0, 0),
						sf::Vector2i(1, 0),
						sf::Vector2i(1, 1),
					},
				},
			},
			{
				Type::T,
				{
				//		OOO(-1, 0)(0, 0)(1,0)
				//		 O (0, 1)
				{
					sf::Vector2i(-1,0),
					sf::Vector2i(0, 0),
					sf::Vector2i(1, 0),
					sf::Vector2i(0, 1),
				},
				//		 O (0, -1)
				//		OO (-1,0)(0, 0)
				//		 O (0, 1)
				{
					sf::Vector2i(0,-1),
					sf::Vector2i(-1, 0),
					sf::Vector2i(0, 0),
					sf::Vector2i(0, 1),
				},
				//		 O  (0, -1)
				//		OOO (-1,0) (0, 0) (1, 0)
				{
					sf::Vector2i(0,-1),
					sf::Vector2i(-1, 0),
					sf::Vector2i(0, 0),
					sf::Vector2i(1, 0),
				},
				//		 O  (0, -1)
				//		 OO (0, 0) (1, 0)
				//		 O	(0, 1)
				{
					sf::Vector2i(0,-1),
					sf::Vector2i(0, 0),
					sf::Vector2i(1, 0),
					sf::Vector2i(0, 1),
				},
			},
		},
			{
				Type::Z,
				{
				//		OO  (-1, 0)(0, 0)
				//		 OO (0, 1) (1,1)
				{
					sf::Vector2i(-1, 0),
					sf::Vector2i(0, 0),
					sf::Vector2i(0, 1),
					sf::Vector2i(1,1),
				},
				//		O (0,-1)
				//	   OO (-1,0)(0,0)
				//	   O  (-1,1)
				{
					sf::Vector2i(0, -1),
					sf::Vector2i(-1, 0),
					sf::Vector2i(0, 0),
					sf::Vector2i(-1,1),
				},
			},
		},
		{
			Type::S,
			{
				//		OO	(0, 0)(1,0)
				//	   OO	(-1,1)(0,1)
				{
					sf::Vector2i(0, 0),
					sf::Vector2i(1, 0),
					sf::Vector2i(-1, 1),
					sf::Vector2i(0, 1),
				},
				//		O  (0, -1)
				//		OO (0, 0) (1,0)
				//		 O (1, 1)
				{
					sf::Vector2i(0, -1),
					sf::Vector2i(0, 0),
					sf::Vector2i(1, 0),
					sf::Vector2i(1, 1),
				},
			},
		}
		};

		map<Type, sf::Sprite> sprites;

		void setcurrentTetris(int currentIndex, Type currentType,Type savedType){
			currentShape = shapes[currentType][currentIndex];
			currentSprite = sprites[currentType];
			savedShape = shapes[savedType][0];
			savedSprite = sprites[savedType];
		}

		void setbackgroud() {
			backgroundTexture.loadFromFile("Tetrisgame/backgroundblack.png");
			backgroundSprite = sf::Sprite(backgroundTexture);
		}

		void setbackgroundsize(int groundWidth, int blockWidth, int windowHeight) {
			backgroundTexture.setRepeated(true);
			backgroundSprite = sf::Sprite(backgroundTexture, sf::IntRect(0, 0, groundWidth * blockWidth, windowHeight));
		}
		void setsoundandbuffer() {
			lined.loadFromFile("Tetrisgame/line.wav");
			linedmusic.setBuffer(lined);
			backgroundmusic.openFromFile("Tetrisgame/Tetris Theme.ogg");
			backgroundmusic.setLoop(true);
			backgroundmusic.setVolume(25);
			backgroundmusic.play();
		 }
	private:

};
#endif // !TETRISGAME3_H

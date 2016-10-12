#include <iostream>
#include <time.h>
#include <curses.h>
#include "kbhit.h"
using namespace std;

enum eDir {STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6};

class cBall
{
private:
	int x, y;
	int originalX, originalY;
	eDir direction;
public:
	cBall(int posX, int posY)
	{
		originalX = posX;
		originalY = posY;
		x = posX;
		y = posY;
		direction = STOP;
	}
	void Reset()
	{
		x = originalX;
		y = originalY;
		direction = STOP;
	}
	void changeDirection(eDir d)
	{
		direction = d;
	}
	void randomDirection()
	{
		direction = (eDir)((rand() % 6) + 1);
	}
	void Move()
	{
		switch (direction)
		{
			case STOP:
				break;
			case LEFT:
				x--;
				break;
			case RIGHT:
				x++;
				break;
			case UPLEFT:
				x--;
				y--;
				break;
			case DOWNLEFT:
				x--;
				y++;
				break;
			case UPRIGHT:
				x++;
				y--;
				break;
			case DOWNRIGHT:
				x++;
				y++;
				break;
			default:
				break;
		}
	}
	friend ostream & operator<< (ostream & o, cBall c)
	{
		o << "Ball [" << c.x << "," << c.y << "][" << c.direction << "]";
		return o;
	}
	inline int getX() { return x; }
	inline int getY() { return y; }
	inline eDir getDirection() { return direction; }
};

class cPaddle
{
private:
	int x, y;
	int originalX, originalY;
public:
	cPaddle()
	{
		x = y = 0;
	}
	cPaddle(int posX, int posY) : cPaddle()
	{
		originalX = posX;
		originalY = posY;
		x = posX;
		y = posY;
	}
	inline void Reset() {
		x = originalX;
		y = originalY;
	}
	inline int getX() { return x; }
	inline int getY() { return y; }
	inline void moveUp() { y--; }
	inline void moveDown() { y++; }
	friend ostream & operator<< (ostream & o, cPaddle c) 
	{
		o << "Paddle [" << c.x << "," << c.y << "]";
		return o;
	}
};

class cGameManager
{
private:
	int width, height;
	int score1, score2;
	char up1, down1, up2, down2;
	bool quit;
	cBall *ball;
	cPaddle *player1;
	cPaddle *player2;
public:
	cGameManager(int w, int h)
	{
		srand(time(NULL));
		quit = false;
		up1 = 'w';
		down1 = 's';
		up2 = 'i';
		down2 = 'k';
		score1 = score2 = 0;
		width = w;
		height = h;
		ball = new cBall(width / 2, height / 2);
		player1 = new cPaddle(1, height / 2 - 3);
		player2 = new cPaddle(width - 2, height / 2 - 3);
	}
	~cGameManager()
	{
		delete ball;
		delete player1;
		delete player2;
	}
	void ScoreUp(cPaddle * player)
	{
		if (player == player1) {
			score1++;
		} else if (player == player2) {
			score2++;
		}

		ball->Reset();
		player1->Reset();
		player2->Reset();
	}
	void Draw() {
		system("clear");
		// top row
		for (int i=0; i < (width + 2); i++) {
			cout << "▁";
		}
		cout << endl;
		for (int i=0; i < height; i++) {
			for (int j=0; j < width; j++) {
				int ballx = ball->getX();
				int bally = ball->getY();
				int player1x = player1->getX();
				int player1y = player1->getY();
				int player2x = player2->getX();
				int player2y = player2->getY();
				// left side
				if (j == 0) {
					cout << "▏";
				}
				if (ballx == j && bally == i) {
					cout << "❁"; // ball
				} else if (player1x == j && (player1y <= i && player1y >= i-3)) {
					cout << "▓"; // player 1
				} else if (player2x == j && (player2y <= i && player2y >= i-3)) {
					cout << "▓"; // player 2
				} else {
					cout << " "; 
				}
				// right side
				if (j == (width - 1)) {
					cout << "▕";
				}
			}
			cout << endl;
		}
		// bottom row
		for (int i=0; i < (width + 2); i++) {
			cout << "▔";
		}
		cout << endl;
	}
	void Input() {
		ball->Move();

		int ballx = ball->getX();
		int bally = ball->getY();
		int player1x = player1->getX();
		int player1y = player1->getY();
		int player2x = player2->getX();
		int player2y = player2->getY();
		int pLength = 4;
		char current;

		if () {
			
			if (current == up1) {
				if (player1y > 0) {
					player1->moveUp();
				}
			} 
			else if (current == up2) {
				if (player2y > 0) {
					player2->moveUp();
				}
			} 
			else if (current == down1) {
				if (player1y + pLength < height) {
					player1->moveDown();
				}
			} 
			else if (current == down2) {
				if (player2y + pLength < height) {
					player2->moveDown();
				}
			} 
			else if (current == down1) {
				if (player1y + pLength < height) {
					player1->moveDown();
				}
			}

			if (ball->getDirection() == STOP) {
				 ball->randomDirection();
			}

			if (current == 'q') {
				quit = true;
			}
		}
	}
	void Logic() {
		int ballx = ball->getX();
		int bally = ball->getY();
		int player1x = player1->getX();
		int player1y = player1->getY();
		int player2x = player2->getX();
		int player2y = player2->getY();
		int pLength = 4;

		// left paddle
		for (int i = 0; i < 4; i++) {
			if (ballx == player1x + 1) {
				if (bally == player1y + i) {
					ball->changeDirection((eDir)((rand() % 3) + 4));
				}
			}
		}
		// right paddle
		for (int i = 0; i < 4; i++) {
			if (ballx == player2x - 1) {
				if (bally == player2y + i) {
					ball->changeDirection((eDir)((rand() % 3) + 1));
				}
			}
		}

		// bottom wall
		if (bally == height - 1) {
			ball->changeDirection(ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);
		}
		// top wall
		if (bally == 0) {
			ball->changeDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
		}

		// right wall
		if (ballx == width - 1) {
			ScoreUp(player1);
		}
		// left wall
		if (ballx == 0) {
			ScoreUp(player2);
		}
	}
	void Run() {
		while (!quit) {
			Draw();
			Input();
			Logic();
		}
	}
};

int main() 
{
	cGameManager c(40, 20);
	c.Run();
	return 0;
}
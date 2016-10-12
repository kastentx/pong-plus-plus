#include <iostream>
#include <time.h>
#include <curses.h>
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
};

int main() 
{
	cGameManager c(40, 20);
	c.Draw();
	return 0;
}
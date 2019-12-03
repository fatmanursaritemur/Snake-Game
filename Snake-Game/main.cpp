#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>

using namespace std;

bool gameOver;
const int width = 20, height = 20;
int snakeX, snakeY, fruitX, fruitY, score;
int tailX[25], tailY[25];
int nTail;
enum direction{ STOP = 0,LEFT,RIGHT,UP,DOWN };
direction dir;

void Settings() {
	bool gameOver = false;
	dir = STOP;
	snakeX = width / 2;
	snakeY = height / 2; // which means player is going to start at the position which is the position at the middle of map
	fruitX = rand() % width;
	fruitY = rand() % height;  
	score = 0;
}
void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
			

		}
	}
}

void Logic()
{
	int preX = tailX[0];
	int preY = tailY[0];
	int pre2X, pre2Y;
	tailX[0] = snakeX;
	tailY[0]=snakeY;
	for (int i = 1; i < nTail; i++)
	{
		pre2X = tailX[i];
		pre2Y = tailY[i];
		tailX[i] = preX;
		tailY[i] = preY;
		preX = pre2X;
		preY = pre2Y;
	}

	switch (dir)
	{
	case LEFT:
		snakeX--;
		break;
	case RIGHT:
		snakeX++;
		break;
	case UP:
	    snakeY--;
		break;
	case DOWN:
		snakeY++;
		break;
	default:
		break;
	}
	if (snakeX >= width)
		snakeX = 0;
	else if (snakeX < 0)
		snakeX = width - 1;
	if (snakeY >= height)
		snakeY = 0;
	else if (snakeY < 0)
		snakeY = height - 1;

	for (int i = 0; i < nTail; i++)
		if (tailX[i] == snakeX && tailY[i] == snakeY)
			gameOver = true;
	
	if (snakeX == fruitX && snakeY == fruitY)
	{
		score++;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}
void Visual()
{
	system("cls");
	for (int i = 0; i < width+2; i++) {
		cout << "#";
	}
	cout << endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
			cout << "#";
			if (i == snakeY && j == snakeX)
				cout << "O";
			else if (i == fruitY && j == fruitX)
				cout << "*";
			else {
				bool printTail = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						cout << "O";
						printTail = true;
					}
				}
				if(!printTail)
				cout << " ";
			}
			if (j == width - 1)
				cout << "#";
			
		}
		cout << endl;
	}
	for (int i = 0; i < width+2; i++) {
		cout << "#";
	}
	cout << endl;
	cout << "Score: " << score << endl;
}

int main()
{
	Settings();
	while (!gameOver)
	{
		Visual();
		Input();
		Logic();		
		Sleep(15); // for game speed
	}
	return 0;
 }
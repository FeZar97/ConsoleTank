// 10 ConsoleTank.cpp
#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

int consoleWidth, consoleHeight;

void gotoxy(int x, int y)
{
    HANDLE h = GetStdHandle(-12);
	if(x < 0) {
		x += consoleWidth;
	}
	if(x >= consoleWidth) {
		x -= consoleWidth;
	}
	if(y < 0) {
		y += consoleHeight;
	}
	if(y >= consoleHeight) {
		y -= consoleHeight;
	}
    COORD c = { x, y };
    SetConsoleCursorPosition(h, c);
};

void getConsoleParams() {
	static HANDLE hWndConsole = GetStdHandle(-12);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo);
	consoleWidth = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
    consoleHeight = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hWndConsole, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hWndConsole, &structCursorInfo);

};
struct Tank {
	int centerX;
	int centerY;
	char direction;
	
	void setInitialParams(int _centerX, int _centerY, char _direction) {
		centerX = _centerX;
		centerY = _centerY;
		direction = _direction;
	};

	void moveTank(char newDirection) {
		
		if(newDirection != direction) {
			direction = newDirection;
		} else {
			switch(direction) {
				case 'A':
					centerX--;
					break;
				case 'W':
					centerY--;
					break;
				case 'D':
					centerX++;
					break;
				case 'S':
					centerY++;
					break;
			}
		}

		if(centerX < 0) {
			centerX += consoleWidth;
		}
		if(centerX >= consoleWidth) {
			centerX -= consoleWidth;
		}
		if(centerY < 0) {
			centerY += consoleHeight;
		}
		if(centerY >= consoleHeight) {
			centerY -= consoleHeight;
		}
		
		system("cls");

		// отрисовка
		switch(direction) {
			case 'A':
				/*
			     01234
				0  ---
				1--|0|  center (3,1)
				2  ---
				*/
				// гусеница
				gotoxy(centerX - 1, centerY - 1); cout << '-';
				gotoxy(centerX,     centerY - 1); cout << '-';
				gotoxy(centerX + 1, centerY - 1); cout << '-';
				
				// пушка
				gotoxy(centerX - 3, centerY);     cout << '-';
				gotoxy(centerX - 2, centerY);     cout << '-';
				
				// тело
				gotoxy(centerX - 1, centerY);		cout << '|';
				gotoxy(centerX,		centerY);		cout << '0';
				gotoxy(centerX + 1,	centerY);		cout << '|';
				
				// гусеница
				gotoxy(centerX - 1, centerY + 1);	cout << '-';
				gotoxy(centerX,     centerY + 1);	cout << '-';
				gotoxy(centerX + 1, centerY + 1);	cout << '-';

				break;

			case 'W':
				/*
			     01234
				0  |
				1  |    center (2,2)
				2|-0-|
				*/
				// тело + гусеницы
				gotoxy(centerX - 2, centerY);		cout << '|';
				gotoxy(centerX - 1, centerY);		cout << '-';
				gotoxy(centerX,		centerY);		cout << '0';
				gotoxy(centerX + 1, centerY);		cout << '-';
				gotoxy(centerX + 2, centerY);		cout << '|';
				
				// пушка
				gotoxy(centerX,		centerY - 1);	cout << '|';
				gotoxy(centerX,		centerY - 2);	cout << '|';

				break;

			case 'D':
				/*
			     01234
				0---
				1|0|--  center (1,1)
				2---
				*/
				// гусеница
				gotoxy(centerX - 1, centerY - 1);	cout << '-';
				gotoxy(centerX,     centerY - 1);	cout << '-';
				gotoxy(centerX + 1, centerY - 1);	cout << '-';

				// тело
				gotoxy(centerX - 1, centerY);		cout << '|';
				gotoxy(centerX,		centerY);		cout << '0';
				gotoxy(centerX + 1,	centerY);		cout << '|';

				// пушка
				gotoxy(centerX + 2, centerY);		cout << '-';
				gotoxy(centerX + 3, centerY);		cout << '-';
				
				// гусеница
				gotoxy(centerX - 1, centerY + 1);	cout << '-';
				gotoxy(centerX,     centerY + 1);	cout << '-';
				gotoxy(centerX + 1, centerY + 1);	cout << '-';

				break;

			case 'S':
				/*
			     01234
				0|-0-|
				1  |   center (2,0)
				2  |
				*/
				// тело + гусеницы
				gotoxy(centerX - 2, centerY);		cout << '|';
				gotoxy(centerX - 1, centerY);		cout << '-';
				gotoxy(centerX,		centerY);		cout << '0';
				gotoxy(centerX + 1, centerY);		cout << '-';
				gotoxy(centerX + 2, centerY);		cout << '|';
				
				// пушка
				gotoxy(centerX,		centerY + 1);	cout << '|';
				gotoxy(centerX,		centerY + 2);	cout << '|';

				break;
		}
		ShowCursor(FALSE);
	};

};


int main()
{
	Tank tank;
	getConsoleParams();

	tank.setInitialParams(consoleWidth/2, consoleHeight/2, 'S');
	tank.moveTank('W');

	char sym;

	while(true) {

		getConsoleParams();

		sym = getch();
		switch(int(sym)) {

			case 27: 
				exit(0);

			case 87:
			case 119:
			case -26:
			case -106:
				tank.moveTank('W');
				break;

			case 83:
			case 115:
			case -21:
			case -101:
				tank.moveTank('S');
				break;

			case 65:
			case 97:
			case -28:
			case -108:
				tank.moveTank('A');
				break;

			case 68:
			case 100:
			case -94:
			case -126:
				tank.moveTank('D');
				break;
		}
	}

	return 0;
}


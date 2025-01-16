#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

int board[3][3]; //поле для крестиков ноликов

int game;

int WinBlue = 0;
int WinRed = 0;

int ChoiseLen = 0;
int ChoiseColomn = 0;

void set_console_color(int textColor, int backgroundColor) { //изменение цвета исходя из поданных аргументов
	cout << "\033[48;5;" << backgroundColor << ";38;5;" << textColor << "m"; //слева цвет фона, справа текста
}

void reset_console_color() {
	cout << "\033[0m";
}

int CheckWinner(int move) {
	int Count = 0;
	int winner = 0;
	//вначале проверим по строкам на обеду
	for (int y = 0; y < 3; y++) {
		Count = 0;
		for (int x = 0; x < 3; x++) {
			if (board[y][x] == move % 2) {
				Count++;
			}
		}
		if (Count == 3) {
			winner = 1;
			return winner;
		}
	}

	//проверяем по столбцам
	for (int x = 0; x < 3; x++) {
		Count = 0;
		for (int y = 0; y < 3; y++) {
			if (board[y][x] == move % 2) {
				Count++;
			}
		}
		if (Count == 3) {
			winner = 1;
			return winner;
		}
	}
	int k = 0;

	int y = 0;
	int x = 0;

	int y1 = 0;
	int x1 = 2;

	int Count1 = 0;
	Count = 0;

	while (k < 3) {
		if (board[y][x] == move % 2) {
			Count++;
		}
		if (board[y1][x1] == move % 2) {
			Count1++;
		}
		if (Count == 3 || Count1 == 3) {
			winner = 1;
			return winner;
		}
		k++;
		y++;
		x++;
		y1++;
		x1--;
	}
}

int CheckEnd() {
	int N = 0;
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			if (board[y][x] == 3) {
				N++;
			}
		}
	}
	return N;
}

void PrintMenu() {
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			if (y == ChoiseLen && x == ChoiseColomn) {
				cout << "*";
			}
			else {
				cout << " ";
			}
			if (board[y][x] == 3) {
				cout << "  |";
				continue;
			}
			if (board[y][x] == 1) {//крестик
				cout << "X |";
				continue;
			}
			if (board[y][x] == 0) {//нолик
				cout << "0 |";
			}
		}
		cout << endl;
	}
	set_console_color(196, 0);
	cout << "    " << WinRed;
	reset_console_color();
	cout << "/";
	set_console_color(123, 0);
	cout << WinBlue << endl;
	reset_console_color();
}

void Menu() {
	cout << "Введите сколько игр будет" << endl;
	cin >> game;
	if (game <= 0) {
		cout << "Ошибка" << endl;
		int key = _getch();
	}

	for (int i = 0; i < game; i++) {
		ChoiseLen = 0;
		ChoiseColomn = 0;
		int move = 1 + i;
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				board[y][x] = 3; //пустая клетка
			}
		}

		while (true) {
			system("cls");
			PrintMenu();

			int k = CheckEnd();
			if (k == 0) {
				cout << "Ничья" << endl;
				system("pause");
				break;
			}

			int key = _getch();
			if (key == 72) {
				ChoiseLen--;
				if (ChoiseLen < 0) {
					ChoiseLen = 2;
				}
			}
			if (key == 80) {
				ChoiseLen++;
				if (ChoiseLen > 2) {
					ChoiseLen = 0;
				}
			}

			if (key == 75) {//left
				ChoiseColomn--;
				if (ChoiseColomn < 0) {
					ChoiseColomn = 2;
				}
			}
			if (key == 77) {//Right
				ChoiseColomn++;
				if (ChoiseColomn > 2) {
					ChoiseColomn = 0;
				}
			}

			if (key == 13) {

				if (board[ChoiseLen][ChoiseColomn] == 3) {
					board[ChoiseLen][ChoiseColomn] = move % 2;
					int win = CheckWinner(move);
					if (win == 1) {
						if (move % 2 != 0) {
							WinRed++;
							system("cls");
							PrintMenu();
							cout << "Крестик выйграл" << endl;
							system("pause");
							break;
						}
						else {
							WinBlue++;
							system("cls");
							PrintMenu();
							cout << "Нолик выйграл" << endl;
							system("pause");
							break;
						}
					}
				}
				else {
					cout << "error" << endl;
					system("pause");
				}

			}
			move++;
		}
	}
	if (WinRed > WinBlue) {
		cout << "Дуэль выйграл крестик" << endl;
	}
	if (WinRed == WinBlue) {
		cout << "Ничья" << endl;
	}
	if (WinRed < WinBlue) {
		cout << "Дуэль выйграл нолик" << endl;
	}
}

int main(){
	setlocale(LC_ALL, "rus");
	Menu();
}
#include <iostream>
#include <conio.h> //для управленя змейкой
#include <thread>
#include <vector>
using namespace std;

bool game_over;
const int width = 20;//ширина
const int heigh = 20;//высота
int x, y,fruitX,fruitY,score;//координаты змейки, координаты фруктов, счёт
vector<int> tail_x, tail_y;
int ntail;//количество добавленных к хвосту звеньев
enum eDirection { STOP ,LEFT,RIGHT,UP,DOWN };
eDirection dir;

void Setup() {
	game_over = false;
	dir = STOP;
	fruitX = rand() % width;//рандомное значение в пределах ширины
	fruitY = rand() % heigh;//рандомное значение в пределах высоты
	x = y = 1;
	ntail = 0;
	for (int i{};i < 20;i++) {
		tail_x.push_back(0);
		tail_y.push_back(0);
	}
}

void Draw() {
	system("cls");//очищаем консоль, всё что в ней было до этого убирается
	for (int i{};i <= width+1;++i) {
		cout << "#";
	}
	cout << endl;
	for (int i{};i < heigh;i++) {
		for (int j{};j < width+2;j++) {//+1 чтобы поле было ровно 20 на 20
			if (j == 0 || j == width+1  ) {
				cout << "#";
			}
			else if (i == y && j == x) {
				cout << "o";
			}
			else if (i == fruitY && j == fruitX) {//такое делаем, чтобы можно было написать обычный else потом
				cout << "%";
			}
			else {
				bool prt = false;
				for (int k = 0;k < ntail;++k) {
					if (j == tail_x[k] && i == tail_y[k]) {
						cout << "o";
						prt = true;
					}
				}
				if (prt == false) {
					cout << " ";
				}
				
			}
		}
		cout << endl;
	}
	for (int i{};i <= width+1;++i) {
		cout << "#";
	}
}

void Input() {
	if (_kbhit()) {//возвращает true если нажали на кнопку
		switch (_getch()) { //считывает кнопку, которую нажали, точнее не нажали а ввели, потому что можно просто приравнять переменную char к getch
		case 'a':
			dir = LEFT;
			break;
		case 'w':
			dir = UP;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			game_over = true;
			break;
		}
	}
}

void Logic() {
	int prevX = tail_x[0];//первый элемент полсе головки по х
	int prevY = tail_y[0];//первый элемент полсе головки по у
	int prev2X, prev2Y;
	tail_x[0] = x;
	tail_y[0] = y;
	for (int i = 1;i < ntail;i++) {
		prev2X = tail_x[i];
		prev2Y = tail_y[i];
		tail_x[i] = prevX;
		tail_y[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	case RIGHT:
		x++;
		break;
	}
	if (x > width || y > heigh || x < 0 || y< 0) { game_over = true; }
	
	for (int i{};i < ntail;i++) {
		if (x == tail_x[i] && y == tail_y[i]) {
			game_over = true;
		}
	}

	if (x == fruitX && y == fruitY) {
		score++;
		fruitX = rand() % width;
		fruitY = rand() % heigh;
		ntail++;

	}
}

int main() {
	//srand(time(NULL));
	//Setup();
	//while (!game_over) {//пока игра не завершена
	//	Draw();
	//	Input();
	//	Logic();
	//	this_thread::sleep_for(0.1s);
	//}
	//if (game_over) {
	//	system("cls");
	//	cout << "GAME OVER NIGGA"<<score;
	//}
}
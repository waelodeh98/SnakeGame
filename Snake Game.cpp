#include <iostream>
#include <ctime>
#include <conio.h>
#include<windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
using namespace std;

void Main_Menu_Levels();

void ClearScreen() {
	COORD pos = { 0, 0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void Shift_To_Right(int arr[], int Size) {

	for (short i = Size - 2; i >= 0; i--)
		arr[i + 1] = arr[i];

}

struct st_Map {
	int Width = 0;
	int Length = 0;

	int Fruit_X = 0;
	int Fruit_Y = 0;
};

struct st_Snake {
	int Head_X = 0;
	int Head_Y = 0;
	int Tail_N = 0;
	int Tail_X[50];
	int Tail_Y[50];
	int Direction = 0;
};

struct st_Player {
	int Score = 0;
	bool Lose = false;
};

enum en_Direction { Top = 1, Down = 2, Right = 3, Left = 4 };

int Random_Number(int From, int To) {
	int Random_Number = 0;
	Random_Number = rand() % (To - From + 1) + From;
	return Random_Number;
}

st_Map Map_1;
st_Snake Snake_1;
st_Player Player_1;

void Generate_Fruit() {
	Map_1.Fruit_X = Random_Number(1, Map_1.Width - 2);
	Map_1.Fruit_Y = Random_Number(1, Map_1.Length - 2);
}

void Set_Up() {

	Map_1.Width = 40;
	Map_1.Length = 20;
	Generate_Fruit();

	Snake_1.Head_X = (Map_1.Width / 2);
	Snake_1.Head_Y = (Map_1.Length / 2);
	Snake_1.Tail_N = 0;

	Player_1.Score = 0;
	Player_1.Lose = false;

	Snake_1.Direction = 0;

}

void Draw() {
	//system("cls");
	ClearScreen();
	cout << "\n       \033[31m======\033[0m \033[95mSNAKE GAME\033[0m \033[31m======\033[0m\n";
	for (int i = 0; i < Map_1.Length; i++) {

		for (int j = 0; j < Map_1.Width; j++) {
			cout << "\033[43m";
			cout << "";
			if (i == 0 || i == Map_1.Length - 1)
				cout << "\033[33m*\033[0m";
			else if (j == 0 || j == Map_1.Width - 1)
				cout << "\033[33m*\033[0m";
			else if (i == Snake_1.Head_Y && j == Snake_1.Head_X)
				cout << "\033[35mO\033[0m";
			else if (i == Map_1.Fruit_Y && j == Map_1.Fruit_X)
				cout << "\033[34m$\033[0m";
			else {
				bool Is_Printed = false;
				for (int z = 0; z < Snake_1.Tail_N; z++) {

					if (Snake_1.Tail_X[z] == j && Snake_1.Tail_Y[z] == i) {
						cout << "\033[35mo\033[0m";
						Is_Printed = true;
						break;
					}

				}

				if (!Is_Printed)
					cout << " ";

			}

		}
		cout << endl;

	}
	cout << "\033[36mPlayer Score : \033[0m" << "\033[32m" << Player_1.Score << "\033[0m" << endl;
}

void Input() {
	if (_kbhit()) {

		char Letter = _getch();

		switch (Letter) {
		case 'w': Snake_1.Direction = en_Direction::Top;
			break;
		case 's': Snake_1.Direction = en_Direction::Down;
			break;
		case 'd': Snake_1.Direction = en_Direction::Right;
			break;
		case 'a': Snake_1.Direction = en_Direction::Left;
			break;
		case 'x': exit(0);
			break;
		}
	}
}

void Move() {

	if (Snake_1.Direction == 0) return;

	for (int i = 1; i < Snake_1.Tail_N; i++) {
		if (Snake_1.Head_X == Snake_1.Tail_X[i] && Snake_1.Head_Y == Snake_1.Tail_Y[i]) {
			Player_1.Lose = true;
			break;
		}
	}


	Shift_To_Right(Snake_1.Tail_X, 50);
	Shift_To_Right(Snake_1.Tail_Y, 50);

	Snake_1.Tail_X[0] = Snake_1.Head_X;
	Snake_1.Tail_Y[0] = Snake_1.Head_Y;

	switch (Snake_1.Direction) {
	case en_Direction::Top: Snake_1.Head_Y--;
		break;
	case en_Direction::Down: Snake_1.Head_Y++;
		break;
	case en_Direction::Right: Snake_1.Head_X++;
		break;
	case en_Direction::Left: Snake_1.Head_X--;
		break;
	}

	if (Snake_1.Head_Y >= Map_1.Length || Snake_1.Head_Y <= 0 || Snake_1.Head_X >= Map_1.Width || Snake_1.Head_X <= 0) {
		PlaySound(TEXT("lose.wav"), NULL, SND_FILENAME | SND_ASYNC);
		Player_1.Lose = true;
	}
	if (Snake_1.Head_X == Map_1.Fruit_X && Snake_1.Head_Y == Map_1.Fruit_Y) {
		PlaySound(TEXT("eat.wav"), NULL, SND_FILENAME | SND_ASYNC);
		Generate_Fruit();

		Player_1.Score += 1;
		Snake_1.Tail_N++;
	}

}

enum en_Main_Choice { Easy = 1, Medium = 2, Hard = 3, Very_Hard = 4 };

short Read_Main_Choice() {
	short Choice = 0;
	do {
		cout << "\n\t\033[32mPlease Choice The Level : \033[0m \033[35m";
		cin >> Choice;
	} while (Choice > 4 || Choice < 1);
	cout << "\033[0m";
	return Choice;
}

void Start_Game(short Speed) {

	char Play_Again = 'Y';

	while (Play_Again == 'Y') {
		Set_Up();

		while (!Player_1.Lose) {
			Draw();
			Input();
			Move();
			Sleep(Speed);
		}

		cout << "\n\n\033[31mDo You Want To Play Again \033[0m(\033[92mY\033[0m/\033[91mN\033[0m) \033[93m?\033[0m \033[34m";
		cin >> Play_Again;
		Play_Again = toupper(Play_Again);
	}

}

void Go_Back_To_Main_Menu_Levels() {
	cout << "\n\033[32mPress Any Key To Go Back To Main Menu Levels...\033[0m";
	system("pause>0");
	Main_Menu_Levels();
}

void Perform_Main_Menu_Levels(en_Main_Choice Main_Choice) {
	switch (Main_Choice) {
	case  en_Main_Choice::Easy:
		system("cls");
		Start_Game(150);
		Go_Back_To_Main_Menu_Levels();
		break;
	case  en_Main_Choice::Medium:
		system("cls");
		Start_Game(100);
		Go_Back_To_Main_Menu_Levels();
		break;
	case  en_Main_Choice::Hard:
		system("cls");
		Start_Game(50);
		Go_Back_To_Main_Menu_Levels();
		break;
	case  en_Main_Choice::Very_Hard:
		system("cls");
		Start_Game(30);
		Go_Back_To_Main_Menu_Levels();
		break;
	}
}

void Main_Menu_Levels() {
	system("cls");
	cout << "\n\t\033[31m+++++++++++++++++++++++++\033[0m";
	cout << "\n\t\033[33m1)\033[0m \033[34mEasy  \033[0m";
	cout << "\n\t\033[33m2)\033[0m \033[34mMedium\033[0m";
	cout << "\n\t\033[33m3)\033[0m \033[34mHard  \033[0m";
	cout << "\n\t\033[33m4)\033[0m \033[34mVery Hard  \033[0m";
	cout << "\n\t\033[31m+++++++++++++++++++++++++\033[0m";
	Perform_Main_Menu_Levels((en_Main_Choice)Read_Main_Choice());
}

int main() {
	srand(unsigned(time(NULL)));

	Main_Menu_Levels();

	system("pause>0");
	return 0;
}
#include "game.h"

void menu()
{
	printf("*************************\n");
	printf("**********1.play*********\n");
	printf("**********0.exit*********\n");
	printf("*************************\n");
}

void game()
{
	//mine数组是用来存放布置好的雷的信息
	char mine[ROWS][COLS] = { 0 };
	//show数组是用来存放排出的雷的
	char show[ROWS][COLS] = { 0 };

	init_board(mine, ROWS, COLS, '0');
	init_board(show, ROWS, COLS, '*');

	//布雷
	set_mine(mine, ROW, COL);
//	show_board(mine, ROW, COL);
	show_board(show, ROW, COL);

	find_mine(mine, show, ROW, COL);
}

int main()
{
	int input = 0;
	srand((unsigned int)time(NULL));
	do
	{
		menu();
		printf("Please input:>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("Exit game\n");
			break;
		default:
			printf("Wrong choice, please rechoose\n");
			break;
		}
	} while (input);
	return 0;
}
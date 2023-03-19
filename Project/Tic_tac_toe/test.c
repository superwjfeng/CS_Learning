// To test the logic of game

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
	char ret = 0;
	//Storage data
	char board[ROW][COL] = { 0 };
	//Initialize
	init_board(board, ROW, COL);
	//Display board
	display_board(board, ROW, COL);

	while (1)
	{
		//Player move
		player_move(board, ROW, COL);
		display_board(board, ROW, COL);
		ret = is_win(board, ROW, COL);
		if (ret != 'C')
		{
			break;
		}
		//Computer move
		computer_move(board, ROW, COL);
		display_board(board, ROW, COL);
		ret = is_win(board, ROW, COL);
		if (ret != 'C')
		{
			break;
		}
	}
	if (ret == '*')
	{
		printf("You won!\n");
	}
	else if (ret == '#')
	{
		printf("Computer won!\n");
	}
	else
	{
		printf("Draw!\n");
	}

	//display_board(board, ROW, COL);
}

void test()
{
	int input = 0;
	srand((unsigned int)time(NULL));
	do
	{
		menu();
		printf("Please choose:>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			printf("Entering game\n");
			game();
			break;
		case 0:
			printf("Exiting game\n");
			break;
		default:
			printf("Wrong input, please rechoose!\n");
			break;
		}
	} while (input);
}

int main()
{
	test();
	return 0;
}
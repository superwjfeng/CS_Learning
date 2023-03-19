#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>


/*
int test()
{
	int a = 2;
	if (a)
		return 1;
	return 0;
}
*/


int main()
{
	//int age = 0;
	//scanf("%d", &age);
/*
	if (age >= 18)
		printf("Adult\n");
	else
		printf("Underage\n");
		*/
	/*
	if (age < 18)
	{
		printf("Underage\n");
		printf("Study!");
	}
	else if (age >= 18 && age < 30)
		printf("Best year\n");
	else if (age >= 30 && age < 60)
		printf("Middleage\n");
	else
		printf("Senior citizen\n");
	*/

	/*
	int ret = test();
	printf("ret = %d\n", ret);
	*/
	//int n = 0;

	//scanf("%d", &n);
	//if (n % 2 == 1)
	//	printf("Odd number\n");

	//for (n = 0; n <= 100; n += 1)
	//	if (n % 2 == 1)
	//		printf("n=%d;", n);

	//while (n <= 100)
	//{
	//	if (n % 2 == 1)
	//		printf("n = %d;", n);
	//	n++;
	//}

	//int i = 1;
	//while (i <= 100)
	//{
	//	printf("i=%d;", i);
	//	i+=2;
	//}

	//int day = 0;
	//scanf("%d", &day);

	//switch (day)
	//{
	//case 1:
	//	printf("Monday\n");
	//	break;
	//case 2:
	//	printf("Tuesday\n");
	//	break;
	//case 3:
	//	printf("Wednesday\n");
	//	break;
	//case 4:
	//	printf("Thursday\n");
	//	break;
	//case 5:
	//	printf("Friday\n");
	//	break;
	//case 6:
	//	printf("Saturday\n");
	//	break;
	//case 7:
	//	printf("Sunday\n");
	//	break;
	//default: //No case is satisfied
	//	printf("Wrong input!");
	//	break; // No sequence requirment, but tradition is to put default and break at the end
	//}
	//int i = 1;
	//while (i <= 10)
	//{
	//	if (5 == i)
	//		break;
	//	printf("%d\n", i);
	//	i++;
	//}

	//int ch = getchar(); //'a'=97
	//putchar(ch);

	//int ch = 0;
	//while ((ch = getchar()) != EOF)
	//{
	//	putchar(ch);
	//}

	char password[20] = { 0 };
	printf("Input password:>");
	scanf("%s", password);

	//// Method 1 
	////getchar();

	//// Method 2
	//int tmp = 0;
	//while ((tmp = getchar()) != '\n')
	//{
	//	;
	//}

	printf("Confirm(Y/N):>");
	int ch = getchar();
	if ('Y' == ch)
		printf("Confirm successfully");
	else
		printf("Cancceled");

	//int i = 0;
	//int j = 0;
	//for (; i < 10; i++)
	//{
	//	for (; j < 10; j++)
	//	{
	//		printf("j=%d\n", j);
	//	}

	//}

	
	return 0;
}
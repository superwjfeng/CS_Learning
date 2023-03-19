#include <stdio.h>

#define MAX 10 // #define constant

//enum constant: Sex, RGB, weekend...
enum Sex
{
	MALE,
	FEMALE,
	SECRET
};

enum Color
{
	RED,
	GREEN,
	BLUE
};

int Add(int x, int y)
{
	int z = x + y;
	return z;
}

int main()
{
	1; // Literal constant

	const num2 = 2; // Const variable
	// num2 = 3; WRONG! It is not correct to reassign consst

	/*
	const int n = 10;
	int arr[n] = { 0 };
	'const int' is still a variable, which is with const property
	*/

	int arr[MAX] = { 0 };
	printf("%d\n", MAX);

	//enum Sex s = FEMALE;
	printf("%d\n", MALE); //0
	printf("%d\n", FEMALE); //1
	printf("%d\n", SECRET); //2

	enum Color color = BLUE;
	color = RED;
	// BLUE = 6; WRONG! The eunm constant itsself cannot be reassigned 

	char arr1[] = "abc"; // Array
	// "abc" = 'a', 'b', 'c', '\0' -- \0 is the ending signal of string 
	// The ending symbol of string is '\0', it will not be accounted as content.
	char arr2[] = { 'a','b','c'};
	printf("%s\n", arr1);
	printf("%s\n", arr2);
	printf("%d\n", strlen(arr1));
	printf("%d\n", strlen(arr2));

	printf("C:\test\32\test\n");// Escape character \t insert a tab
	printf("C:\\test\\32\\test\n");
	printf("(are you ok??)\n");
	printf("\"\n");
	printf("%d\n", strlen("c:\test\32\test.c")); // "\t" is a whole escape character
	//total 13 char, \32 is two hex number
	printf("\x61");

	int input = 0;
	printf("Which number u gonna choose?(1/0)>: ");
	scanf_s("%d", &input);

	if (input == 1)
		printf("Great!");
	else
		printf("Not so great!");
	
	int line = 0;
	while (line < 20000)
	{
		printf("Coding Line: %d\n", line);
		line++;
	}
	printf("Offer!\n");

	int sum = Add(3, 5);
	printf("%d\n", sum); 

	int test_arr[10] = { 1,2,3,4,5,6,7,9,10 };
	int i = 0;
	while (i < 10)
	{
		printf("%d", test_arr[i]);
		i++;
	}

	// Shift operator << & >>
	int a = 1; // a is 4 Byte 00000000 00000000 00000000 00000001
	int b = a << 2; // Shift operator works on Binary, b becomes .... 00000100
	printf("%d\n", b);

	// True and false: in C, 0 represents false, every other values is ture
	int c = 0;
	printf("%d\n", c);
	printf("%d\n", !c);

	// sizeof calculates the how large each type of variable takes
	int d = 10;
	printf("%d\n", sizeof(d));
	printf("%d\n", sizeof(int));
	printf("%d\n", sizeof d);
	//printf("%d\n", sizeof int);
	int arr3[10] = { 0 };
	printf("%d\n", sizeof(arr3));

	int sz = 0;
	sz = sizeof(arr3) / sizeof(arr[0]);
	printf("%d\n", sz); // calculate the number of elements in an array
	return 0;
}
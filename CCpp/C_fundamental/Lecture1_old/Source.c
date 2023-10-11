/* .C Source file
* .h Header file
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h> // Standard input output

int num1 = 1; // Global variable: variables outside {} code block 
int num3 = 3;

int main() /* Main function is the entrace of program,
		   program must have one and only have one main function */ 
	/*'int' before the main function means
	the function returns a integer result*/
{
	printf("helloworld\n"); // printf is a library function, which is provided by C
	//Calling library funcitons -- #include<...>

	int num2 = 2; // Local variable
	int num3 = 4; 
	printf("%d\n", num3);/* Local and global variables can have same names with different
				  assigned values, but in this case local variables have higher privilage.
				  Recommendation: do not assgin same name to local and global variable,
				  it would be easier to generate errors*/

	char ch = 'A'; // Announcement 'char' opens memory for 'A'
	printf("%c\n", ch);
	
	short age = 20; /* apply 2 bits from memory to storage 'age'
					which is better compared with int age (4 bits) */
	printf("%d\n", age);

	printf("%d\n", sizeof(char)); //1 byte = 8 bit (0 or 1); 1 kb = 1024 byte
	printf("%d\n", sizeof(short)); //2 byte, which can represent 2^16 possibilities
	printf("%d\n", sizeof(int)); //4 byte
	printf("%d\n", sizeof(long)); //4 byte
	printf("%d\n", sizeof(long long)); //8 byte
	printf("%d\n", sizeof(float)); //4 byte
	printf("%d\n", sizeof(double)); //8 byte

	float weight = 95.6;
	
	//Calculate the sum of two input numbers
	int InputNum1 = 0;
	int InputNum2 = 0;
	int sum = 0;
	scanf("%d%d", &InputNum1, &InputNum2); // '&' is the address-of operator
	
	sum = InputNum1 + InputNum2;
	printf("sum = %d\n", sum);

	/*
	The scope of local variable is limited according to its position,
	on the contrary, the scope of global variable is not limited.
	{
		int num = 1
	}
	In this case, num is defined or its scope is inside {}, therefore
	num can not be used outside {}, but when the other way round, the num
	can be used without problems.

	*/

	extern global_test = 3; /* 'extern' will extend the scope of variable, so that 
							codes in other source files can also use the extended variables.*/
	return 0;
}
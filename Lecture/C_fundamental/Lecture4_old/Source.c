#include <stdio.h>

int main()
{
	int age_test = 10;
	if (18 <= age_test < 28) // first judge if 18 <= age, then judge if age <= 28
		printf("Adult\n");

	int age = 20;
	if (age >= 18 && age < 28)
		printf("Adult\n");
	else if (age <= 28 && age < 50)
		printf("Middle age\n");
	else if (age <= 50 && age < 90)
		printf("Senior citizen");
	else
		printf("Really old");

	int a = 0;
	int b = 2;
	if (a == 1)
		if (b == 2)
			printf("hehe\n");
		else
			printf("haha\n");

	if (a == 1)
		if (b == 2)
			printf("hehe\n");
		else
			(printf("haha\n"));
	//else和最靠近的没有匹配的if是自动匹配的，因此这么写代码是不规范的

	if (a == 1)
	{
		if (b == 2)
			printf("hehe\n");
	}
	else
		printf("haha\n");

	int num = 4;
	if (num = 5) //0 as falsh, non 0 as true
		printf("x\n");

	if (num == 4)
		printf("y\n");

	int i = 1;
	while (i < 100)
	{
		if (i % 2 == 1)
			printf("%d  ", i);
		i++;
	}

	int i2 = 1;
	while (i2 < 100)
	{
		printf("%d  ", i2);
		i2 += 2;
	}

	int day = 0;
	scanf_s("%d", &day);
	switch (day)
	{
	case 1:	
		printf("Monday\n");
		break;
	case 2:
		printf("Tuesday\n");
		break;
	case 3:	
		printf("Wednesday\n");
		break;
	case 4:
		printf("Thursday\n");
		break;
	case 5:	
		printf("Friday\n");
		break;
	case 6:
		printf("Saturday\n");
		break;	
	case 7:
		printf("Sunday\n");
		break;
	default:
		printf("Wrong input\n");
		break;
	}

	/* case 1-5 output the same, case 6-7 output the another case
	switch (day)
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		prinf("Workday\n");
		break;
	case 6:
	case 7:
		printf("Weekend\n");
		break;
	}
	*/

	int n = 1;
	int m = 2;
	switch(n)
	{
	case 1: m++; //如果没有遇到break, case按照进入位依次执行
	case 2: n++;
	case 3: // nest switch
		switch (n)
		{
		case 1:n++;
		case 2:
			m++;
			n++;
			break;
		}
	case 4:
		m++;
		break;
	default:
		break;
	}
	printf("m = %d, n = %d\n", m, n);


	int ii = 0;
	
	/* Infinite loop
	while (ii < 10)
	{
		if (ii == 5)
			continue;
		printf("%d\n", ii);
		ii++;
	}
	*/

	while (ii < 10)
	{
		ii++;
		if (ii == 5)
			continue; //continue 语句的作用是终止本次循环
		//也就是说跳过本次循环中continue语句之后剩余的代码，直接跳转到下一次循环的入口判断
		printf("%d\n", ii);
	}

	int ch = getchar();
	putchar(ch);
	printf("%c\n", ch); //putchar and printf with char are same, but apparently putchar is shorter

	return 0;
}

#include "contact.h"

/*
通讯录：
1. 保存1000个联系人的信息
2. 增加联系人
3. 删除联系人
4. 修改联系人
5. 查找联系人
6. 排序

一个人的信息包括：名字、性别、年龄、电话、住址
*/

void menu()
{
	printf("*************************\n");
	printf("****1.add    2.del*******\n");
	printf("****3.search 4.modify****\n");
	printf("****5.sort   6.print*****\n");
	printf("****7.reset  0.exit******\n");
	printf("*************************\n");
}

void test()
{
	int input = 0;
	//创建通讯录
	//PeoInfo data[1000]; //存放1000个人的信息
	Contact con; //Contact con = {0};?	

	//初始化通讯录
	InitContact(&con);

	int sz = 0; //记录通讯录中已经保存的信息个数
	do
	{
		menu();
		printf("Please choose:>");
		scanf("%d", &input);
		switch (input)
		{
		case ADD:
			AddContact(&con);
			break;
		case DEL:
			DelContact(&con);
			break;
		case SEARCH:
			SearchContact(&con);
			break;
		case MODIFY:
			ModifyContact(&con);
			break;
		case SORT:
			SortContactByName(&con);
			break;
		case PRINT:
			PrintContact(&con);
			break;
		case RESET:
			ResetContact(&con);
		case EXIT:
			DestroyContact(&con);
			//SaveContact(&con);
			printf("Exit.\n");
			break;
		default:
			printf("Invalid choice.\n");
			break;
		}
	} while (input);
}

int main()
{
	test();
	return 0;
}
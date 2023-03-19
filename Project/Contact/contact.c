//接口的实现
#include "contact.h"

////静态的版本
//void InitContact(Contact* pc)
//{
//	assert(pc);
//	pc->sz = 0;
//	memset(pc->data, 0, sizeof(pc->data)); //sizeof的是结构体地址，指向一个数组
//}

//动态的版本

void InitContact(Contact* pc)
{
	assert(pc);
	pc->sz = 0;
	pc->capacity = DEFAULT_SZ;
	pc->data = (PeoInfo*)malloc(pc->capacity * sizeof(PeoInfo));
	if (pc->data == NULL)
	{
		perror("InitContact::malloc");
		return;
	}
	memset(pc->data, 0, pc->capacity * sizeof(PeoInfo));
}

//动态增容
void CheckCapacity(Contact* pc)
{
	if (pc->sz == pc->capacity)
	{
		PeoInfo* tmp = (PeoInfo*)realloc(pc->data, (pc->capacity + 2) * sizeof(PeoInfo));
		if (tmp != NULL)
		{
			pc->data = tmp;
		}
		pc->capacity += 2;
	}
}

void AddContact(Contact* pc)
{
	////静态版本
	//assert(pc);
	//if (pc->sz == MAX)
	//{
	//	printf("Contact list is full, cannot add\n");
	//	return;
	//}

	//动态版本
	assert(pc);

	CheckCapacity(pc);

	printf("Please input name:>");
	scanf("%s", pc->data[pc->sz].name);
	printf("Please input age:>");
	scanf("%d", &(pc->data[pc->sz].age));
	printf("Please input sex:>");
	scanf("%s", pc->data[pc->sz].sex);
	printf("Please input telefone number:>");
	scanf("%s", pc->data[pc->sz].tele);
	printf("Please input address:>");
	scanf("%s", pc->data[pc->sz].addr);

	pc->sz++;
	printf("Successfull adding\n");
}


void PrintContact(const Contact* pc)
{
	assert(pc);
	int i = 0;
	printf("%-20s %-5s %-8s %-12s %-30s\n", "Name", "Age", "Sex", "Telefone", "Address");
	for (i = 0; i < pc->sz; i++)
	{
		//printf("%s %d %s %s %s\n", pc->data[i].name, pc->data[i].age, pc->data[i].sex, pc->data[i].tele, pc->data[i].addr); //无法对齐
		printf("%-20s %-5d %-8s %-12s %-30s\n", pc->data[i].name, pc->data[i].age, pc->data[i].sex, pc->data[i].tele, pc->data[i].addr);
	}
}


//找到返回下标，找不到返回-1
int FindByName(const Contact* pc, char* name)
{
	assert(pc);
	int i = 0;
	for (i = 0; i < pc->sz; i++)
	{
		if (0 == strcmp(pc->data[i].name, name))
		{
			return i;
		}
	}
	return -1;
}

void DelContact(Contact* pc)
{

	assert(pc);
	if (pc->sz == 0)
	{
		printf("Contact is empty, cannot be deleted\n");
		return;
	}

	//删除： 1.找到
	char name[NAME_MAX] = { 0 };
	printf("Please input the name of being deleted:>\n");
	scanf("%s", name);
	int pos = FindByName(pc, name);
	if (pos == -1)
	{
		printf("People to be deleted does not exist.\n");
		return;
	}

	//2. 删除 memmove?
	int j = 0;
	for (j = pos; j < pc->sz - 1; j++)
	{
		pc->data[j] = pc->data[j + 1];
	}
	pc->sz--;
	printf("Delete successfully");
}

void SearchContact(const Contact* pc)
{
	char name[NAME_MAX] = { 0 };
	printf("Please input the name you want to find:>\n");
	scanf("%s", name);
	int pos = FindByName(pc, name);
	if (pos == -1)
	{
		printf("The name you are looking for does not exist.\n");
		return;
	}

	printf("%-20s %-5s %-8s %-12s %-30s\n", "Name", "Age", "Sex", "Telefone", "Address");
	printf("%-20s %-5d %-8s %-12s %-30s\n", pc->data[pos].name, pc->data[pos].age, pc->data[pos].sex, pc->data[pos].tele, pc->data[pos].addr);
}

void SortContactByName(Contact* pc)
{
	int i = 0;
	for (i = 0; i < (pc->sz) - 1; i++)
	{
		int j = 0;
		for (j = 0; j < (pc->sz) - i - 1; j++)
		{
			if (strcmp(pc->data[j].name, pc->data[j + 1].name) > 0)
			{
				char tmp[NAME_MAX] = { 0 };
				strcpy(tmp, pc->data[j].name);
				strcpy(pc->data[j].name, pc->data[j + 1].name);
				strcpy(pc->data[j + 1].name, tmp);
			}
		}
	}
	printf("Sort successfully!\n");
}

void ModifyInfo()
{
	printf("*************************\n");
	printf("****1.Name     2.Sex*****\n");
	printf("****3.Age      4.Tele****\n");
	printf("****5.Address************\n");
	printf("*************************\n");
}

void ModifyContact(Contact* pc)
{
	char name[NAME_MAX] = { 0 };
	char modified_term[10] = { 0 };
	printf("Please input the name of contact that you want to modify:>\n");
	scanf("%s", name);
	int i = FindByName(pc, name);

	printf("Please input the label number of information you want to modify:>\n");
	ModifyInfo();
	int input = 0;
	scanf("%d", &input);
	printf("Please input the modified value:>\n");
	char value[ADDR_MAX] = {0};//ADDR_MAX是最长的
	scanf("%s", value);
	switch (input)
	{
	case NAME:
		strcpy(pc->data[i].name, value);
		break;
	case SEX:
		strcpy(pc->data[i].sex, value);
		break;
	case AGE:
		pc->data[i].age = (int)value; //??
		break;
	case TELE:
		strcpy(pc->data[i].tele, value);
		break;
	case ADDR:
		strcpy(pc->data[i].addr, value);
		break;
	}
	printf("Modify successfully!\n");
}

void ResetContact(Contact* pc)
{
	InitContact(pc);
	printf("Reset successfully!\n");
}

void DestroyContact(Contact* pc)
{
	free(pc->data);
	pc->data = NULL;
	pc->capacity = 0;
	pc->sz = 0;
}

void SaveContact(const Contact* pc)
{
	//打开文件
	FILE* pf = fopen("contact.dat", "wb");
	if (pf == NULL)
	{
		perror("SaveContact::fopen");
		return;
	}
	
	//写文件
	int i = 0;
	for (i = 0; i < pc->sz; i++)
	{
		fwrite(pc->data + i, sizeof(PeoInfo), 1, pf);
	}

	//关闭文件
	fclose(pf);
	pf = NULL;
}
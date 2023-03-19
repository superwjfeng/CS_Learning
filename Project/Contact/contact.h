#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
//接口声明

//类型的声明

enum Option
{
	EXIT, //0
	ADD,
	DEL,
	SEARCH,
	MODIFY,
	SORT,
	PRINT,
	RESET
};

enum ModifiedTerm
{
	NAME=1,
	SEX,
	AGE,
	TELE,
	ADDR
};

#define MAX 1000
#define NAME_MAX 20
#define SEX_MAX 5
#define TELE_MAX 12
#define ADDR_MAX 30
#define DEFAULT_SZ 3

typedef struct PeoInfo
{
	char name[NAME_MAX];
	char sex[SEX_MAX];
	int age;
	char tele[TELE_MAX];
	char addr[ADDR_MAX];
} PeoInfo;

////静态的版本
//typedef struct Contact
//{
//	PeoInfo data[1000];
//	int sz;
//}Contact;

//动态的版本
typedef struct Contact
{
	PeoInfo* data;
	int sz;
	int capacity; //记录当前通讯录的最大容量
}Contact;

//函数的声明

//初始化通讯录
void InitContact(Contact* pc);

//销毁通讯录
void DestroyContact(Contact* pc);

//增加联系人的信息
void AddContact(Contact* pc);

//打印通讯录中的信息
void PrintContact(const Contact* pc);

//删除指定联系人
void DelContact(Contact* pc);

//查找联系人
void SearchContact(const Contact* pc);

//排序所有联系人
void SortContactByName(Contact* pc);

//修改联系人信息
void ModifyContact(Contact* pc);

//清空所有联系人
void ResetContact(Contact* pc);




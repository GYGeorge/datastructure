#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
#include"STATUS.h"
#define LIST_INIT_SIZE 100    //线性表存储空间的初始分配量
#define LISEINCREMENT  10	  //线性表存储空间的分配增量
typedef int ElemType;
typedef struct {
	ElemType *elem;			  //存储空间基址
	int length;				  //当前长度
	int listsize;	        //当前分配的存储总量
}Sqlist;
Status InitList(Sqlist &L)//创建一个空表
{
	L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L.elem) exit(OVERFLOW);   //存储分配失败
	L.length = 0;				   //空表长度为0
	L.listsize = LIST_INIT_SIZE;   //初始存储容量
	return OK;
}//InitList
Status visit(int a)
{
	cout << a << " ";
	return OK;
}//visit
Status ListTraverse(Sqlist L, Status(*visit)(int a))
{
	int i;
	for (i = 0; i < L.length; i++)
	{
		visit(L.elem[i]);
	}
	cout<<endl;
	return OK;
}//ListTraverse
Status Get_BreakPoint(Sqlist L, ElemType &point)//求折点数量
{
	int count = 0;//计数器
	int i = 1;
	while (i < L.length - 1) {
		if ((L.elem[i] > L.elem[i + 1]) && (L.elem[i] > L.elem[i - 1]))//波峰
			count++;
		else if ((L.elem[i] < L.elem[i + 1]) && (L.elem[i] < L.elem[i - 1]))//波谷
			count++;
        i++;
	}
	point = count;
}//Get_BreakPoint
int main()
{
	int i;
	Sqlist L;
	InitList(L);
	ElemType num;
	cin >> num;
	L.length = num;
	for (i = 0; i < num; i++) {
		cin >> L.elem[i];
	}
	int BreakPoint;
	Get_BreakPoint(L, BreakPoint);
	cout << BreakPoint << endl;
}

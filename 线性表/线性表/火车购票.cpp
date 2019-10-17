#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
#include"STATUS.h"
#define LIST_INIT_SIZE 100    //线性表存储空间的初始分配量
typedef bool ElemType;
typedef struct {
	ElemType *elem;			  //存储空间基址
	int length;				  //当前长度
}Sqlist;
Status InitList_100(Sqlist &L)//创建一个空表
{
	int i = 0;
	L.elem = (ElemType *)malloc((LIST_INIT_SIZE+1) * sizeof(ElemType));
	if (!L.elem) exit(OVERFLOW);   //存储分配失败
	for (; i <= LIST_INIT_SIZE; i++) {
		L.elem[i] = 0;
	}//for
	L.length = LIST_INIT_SIZE+1;   //初始存储容量
	return OK;
}//InitList
Status DistributionTickets(Sqlist &L, int tics,int &po) 
{
	int i, j, cou;
	int n = tics;
	for (i = 1; i <= 100; i++)
	{
		if (L.elem[i] == 0) {
			for (j = i + 1, cou = 1; cou <= n; cou++, j++) {
				if (cou != n)
					if (j % 5 == 0 && (j + 1) % 5 == 1)
						break;
				if (L.elem[j] == 1) break;
				L.elem[j]

			}
		}
	}
}
int main()
{
	int n, i;
	std::cout << "购票人数：";
	std::cin >> n;
	int *cpot, *TicketNum;
	cpot = (int*)malloc(n * sizeof(int));
	TicketNum = (int*)malloc(n * sizeof(int));
	for (i = 0; i < n; i++) {
		std::cin >> TicketNum[i];
	}
	Sqlist Train;
	InitList_100(Train);

}
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
int ListLength(Sqlist L)//返回数据元素个数
{
	return L.length;
}//ListEmpty
Status ListInsert(Sqlist &L, int i, ElemType e)//在i前插入数据元素
{
	ElemType *newbase, *q, *p;
	if (i<1 || i>ListLength(L) + 1) return ERROR;
	if (L.length >= L.listsize) {
		newbase = (ElemType *)realloc(L.elem, (L.listsize + LISEINCREMENT) * sizeof(ElemType));
		if (!newbase) exit(OVERFLOW);
		L.elem = newbase;
		L.listsize += LISEINCREMENT;
	}
	q = &(L.elem[i - 1]);
	for (p = &(L.elem[L.length - 1]); p >= q; --p)
		*(p + 1) = *p;
	*q = e;
	L.length++;
	return OK;
}//ListInsert

Status ListDelete(Sqlist &L, int i, ElemType &e)//删除数据元素
{
	ElemType  *q, *p;
	if (i<1 || i>ListLength(L)) return ERROR;
	p = &(L.elem[i - 1]);
	e = *p;
	q = L.elem + L.length - 1;
	for (++p; p <= q; ++p)
		*(p - 1) = *p;
	--L.length;
	return OK;
}//ListDelete
void Insert_sort(Sqlist &L)//插入排序顺序表（删除相同元素）
{
	ElemType temp;
	int i, j;
	for (i = 0; i < L.length; i++) {
		for (j = 0; j < i; j++) {
			if (L.elem[j] > L.elem[i]) {//移动操作
				ListDelete(L, i + 1, temp);
				ListInsert(L, j + 1, temp);

			}
			else if (L.elem[j] == L.elem[i]) {//相同元素删除
				ListDelete(L, i + 1, temp);
				i--;
				if (L.elem[j] > L.elem[i]) {
                    ListDelete(L, i + 1, temp);
                    ListInsert(L, j + 1, temp);
                    break;
				}
			}
		}
	}
}//Insert_sort
Status visit(int a)
{
	cout << a << endl;
	return OK;
}//visit
Status ListTraverse(Sqlist L, Status(*visit)(int a))
{
	int i;
	for (i = 0; i < L.length; i++)
	{
		visit(L.elem[i]);
	}
	return OK;
}//ListTraverse

int main()
{
	Sqlist l;
	ElemType A[10] = { 9,10,7,3,2,4,6,9,1,0 };
	l.elem = A;
	l.length = 10;
	Insert_sort(l);
	ListTraverse(l, *visit);
	if (l.length % 2 == 1) {
		cout << l.elem[(l.length + 1) / 2] << endl;
	}
	else if (l.length % 2 == 2) {
		cout << "-1" << endl;
	}
}

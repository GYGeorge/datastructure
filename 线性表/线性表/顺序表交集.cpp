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
void Intersection(Sqlist &L,Sqlist A,Sqlist B)
{
	int k = 0;
	int i, j;
	InitList(L);
	for (i = 0; i < A.length; i++) {
		for (j = 0; j < B.length; j++) {
			if (A.elem[i] == B.elem[j]) {
				L.elem[k] = A.elem[i];
				L.length++;
				k++;
			}
		}
	}

}//Intersection
Status visit(int a)
{
    cout<<a<<endl;
    return OK;
}//visit
Status ListTraverse(Sqlist L,Status(*visit)(int a))
{
    int i;
    for(i = 0;i < L.length ;i++)
    {
        visit(L.elem[i]);
    }
    return OK;
}//ListTraverse
int main()
{
    Sqlist A,B,L;
    ElemType a[8]={0,2,5,9,89,99,100,158};
    ElemType b[5]={1,2,5,99,158};
    A.elem = a;B.elem = b;
    A.length = 8;
    B.length = 5;

    Intersection(L,A,B);
    ListTraverse(L,*visit);

}

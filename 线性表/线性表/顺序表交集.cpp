#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
#include"STATUS.h"
#define LIST_INIT_SIZE 100    //���Ա�洢�ռ�ĳ�ʼ������
#define LISEINCREMENT  10	  //���Ա�洢�ռ�ķ�������
typedef int ElemType;
typedef struct {
	ElemType *elem;			  //�洢�ռ��ַ
	int length;				  //��ǰ����
	int listsize;	        //��ǰ����Ĵ洢����
}Sqlist;
Status InitList(Sqlist &L)//����һ���ձ�
{
	L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L.elem) exit(OVERFLOW);   //�洢����ʧ��
	L.length = 0;				   //�ձ���Ϊ0
	L.listsize = LIST_INIT_SIZE;   //��ʼ�洢����
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

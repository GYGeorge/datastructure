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
Status Get_BreakPoint(Sqlist L, ElemType &point)//���۵�����
{
	int count = 0;//������
	int i = 1;
	while (i < L.length - 1) {
		if ((L.elem[i] > L.elem[i + 1]) && (L.elem[i] > L.elem[i - 1]))//����
			count++;
		else if ((L.elem[i] < L.elem[i + 1]) && (L.elem[i] < L.elem[i - 1]))//����
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

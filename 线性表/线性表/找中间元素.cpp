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
int ListLength(Sqlist L)//��������Ԫ�ظ���
{
	return L.length;
}//ListEmpty
Status ListInsert(Sqlist &L, int i, ElemType e)//��iǰ��������Ԫ��
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

Status ListDelete(Sqlist &L, int i, ElemType &e)//ɾ������Ԫ��
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
void Insert_sort(Sqlist &L)//��������˳���ɾ����ͬԪ�أ�
{
	ElemType temp;
	int i, j;
	for (i = 0; i < L.length; i++) {
		for (j = 0; j < i; j++) {
			if (L.elem[j] > L.elem[i]) {//�ƶ�����
				ListDelete(L, i + 1, temp);
				ListInsert(L, j + 1, temp);

			}
			else if (L.elem[j] == L.elem[i]) {//��ͬԪ��ɾ��
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

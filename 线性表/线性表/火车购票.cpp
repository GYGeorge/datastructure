#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
#include"STATUS.h"
#define LIST_INIT_SIZE 100    //���Ա�洢�ռ�ĳ�ʼ������
typedef bool ElemType;
typedef struct {
	ElemType *elem;			  //�洢�ռ��ַ
	int length;				  //��ǰ����
}Sqlist;
Status InitList_100(Sqlist &L)//����һ���ձ�
{
	int i = 0;
	L.elem = (ElemType *)malloc((LIST_INIT_SIZE+1) * sizeof(ElemType));
	if (!L.elem) exit(OVERFLOW);   //�洢����ʧ��
	for (; i <= LIST_INIT_SIZE; i++) {
		L.elem[i] = 0;
	}//for
	L.length = LIST_INIT_SIZE+1;   //��ʼ�洢����
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
	std::cout << "��Ʊ������";
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
//MergeSort.h
#ifndef MERGESORT_H
#include<iostream>
using namespace std;
typedef int ElemType;
void MERGE(ElemType *A, int &p, int &q, int &r)//�鲢
{
	int i, j, k;
	int n1 = q - p + 1;	//n1Ϊ����B�ĳ���
	int n2 = r - q;		//n2Ϊ����C�ĳ���
	int *B = new int[n1 + 2];
	int *C = new int[n2 + 2];
	for (i = p, j = 1; i <= q; i++, j++)		B[j] = A[i];//��A[p...q]������B[1...n1]��
	for (i = q + 1, j = 1; i <= r; i++, j++)	C[j] = A[i];//��A[q+1...r]������C[1...n2]��
	/*�����һ��Ԫ�ظ�ֵΪ����*/
	B[n1 + 1] = 9999;
	C[n2 + 1] = 9999;
	/************/
	i = 1; j = 1; k = p;//��ʼ��
	while (k <= r) {
		if (B[i] <= C[j]) {
			A[k] = B[i]; i++;
		}
		else {
			A[k] = C[j]; j++;
		}
		k++;
	}
	delete []B;
	delete []C;
}
void Merge_Sort(int *A, int p, int r)//�ֽ�
{
	int q;
	if (p >= r)
		return;
	else {
		q = (p + r) / 2;//q����ȡ��
		Merge_Sort(A, p, q);
		Merge_Sort(A, q + 1, r);
		MERGE(A, p, q, r);
	}
}//MERGE_SORT
#endif // !MERGESORT_H
#pragma once

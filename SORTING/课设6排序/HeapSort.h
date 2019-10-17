#ifndef HEAPSORT_H
#define HEAPSORT_H
#include<iostream>
#include<cstdlib>
#include<cstdio>
typedef int ElemType;
void HeapAdjust(ElemType *A, int s, int m)
{//A[s..m]�м�¼�Ĺؼ��ֳ���A[s]��ɶѵĽṹ
	int rc = A[s];//�ݴ�
	int j;
	for (j = 2 * s; j <= m; j = j * 2) {
		if (j < m&&A[j] < A[j + 1])//���������Ƚ�
			j++;
		if (rc >= A[j]) 
			break;
		A[s] = A[j];//��¼����
		s = j;
	}//for
	A[s] = rc;
}//HeapAdjust
void Heap_Sort(ElemType *A, int len)//������0�ŵ�Ԫδ��
{
	ElemType temp;
	int i;
	for (i = len / 2; i > 0; i--)//���󶥶�
		HeapAdjust(A, i, len);
	for (i = len; i > 1; i--) {
		swap(A[i], A[1]);//�����һ����¼����
		HeapAdjust(A, 1, i - 1);//���µ���Ϊ�󶥶�
	}//for
}//Heap_Sort
#endif //HEAPSORT_H
#pragma once

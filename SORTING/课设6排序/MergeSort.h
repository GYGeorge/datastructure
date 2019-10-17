//MergeSort.h
#ifndef MERGESORT_H
#include<iostream>
using namespace std;
typedef int ElemType;
void MERGE(ElemType *A, int &p, int &q, int &r)//归并
{
	int i, j, k;
	int n1 = q - p + 1;	//n1为数组B的长度
	int n2 = r - q;		//n2为数组C的长度
	int *B = new int[n1 + 2];
	int *C = new int[n2 + 2];
	for (i = p, j = 1; i <= q; i++, j++)		B[j] = A[i];//将A[p...q]拷贝到B[1...n1]中
	for (i = q + 1, j = 1; i <= r; i++, j++)	C[j] = A[i];//将A[q+1...r]拷贝到C[1...n2]中
	/*将最后一个元素赋值为无穷*/
	B[n1 + 1] = 9999;
	C[n2 + 1] = 9999;
	/************/
	i = 1; j = 1; k = p;//初始化
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
void Merge_Sort(int *A, int p, int r)//分解
{
	int q;
	if (p >= r)
		return;
	else {
		q = (p + r) / 2;//q向下取整
		Merge_Sort(A, p, q);
		Merge_Sort(A, q + 1, r);
		MERGE(A, p, q, r);
	}
}//MERGE_SORT
#endif // !MERGESORT_H
#pragma once

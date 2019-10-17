#ifndef HEAPSORT_H
#define HEAPSORT_H
#include<iostream>
#include<cstdlib>
#include<cstdio>
typedef int ElemType;
void HeapAdjust(ElemType *A, int s, int m)
{//A[s..m]中记录的关键字除了A[s]外成堆的结构
	int rc = A[s];//暂存
	int j;
	for (j = 2 * s; j <= m; j = j * 2) {
		if (j < m&&A[j] < A[j + 1])//左右子树比较
			j++;
		if (rc >= A[j]) 
			break;
		A[s] = A[j];//记录上移
		s = j;
	}//for
	A[s] = rc;
}//HeapAdjust
void Heap_Sort(ElemType *A, int len)//堆排序，0号单元未用
{
	ElemType temp;
	int i;
	for (i = len / 2; i > 0; i--)//建大顶堆
		HeapAdjust(A, i, len);
	for (i = len; i > 1; i--) {
		swap(A[i], A[1]);//和最后一个记录交换
		HeapAdjust(A, 1, i - 1);//重新调整为大顶堆
	}//for
}//Heap_Sort
#endif //HEAPSORT_H
#pragma once

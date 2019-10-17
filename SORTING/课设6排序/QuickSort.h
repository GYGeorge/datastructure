#ifndef QUICKSORT_H
#define QUICKSORT_H
#include<iostream>
using namespace std;
typedef int ElemType;
int PARITITION(ElemType *A, int p, int r)
{//以最右边数为主元划分数组，p为主元左，q为主元右，u位置待确定
	int q = p, u, temp;
	for (u = p; u <= r - 1; u++) {
		if (A[u] <= A[r]) {
			swap(A[q], A[u]);
			q++;
		}//if
	}//for
	swap(A[q], A[r]);
	return q;
}//PARITITION
void Quick_Sort(ElemType *A, int p, int r)
{
	int q;
	if (p >= r)	return;
	else {
		q = PARITITION(A, p, r);
		Quick_Sort(A, p, q - 1);
		Quick_Sort(A, q + 1, r);
	}
}//QUICK_SORT
#endif // !QUICKSORT_H
#pragma once



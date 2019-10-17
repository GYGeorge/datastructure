#ifndef SHELLSORT_H
#define SHELLSORT_H
#include<iostream>
#include<math.h>
#include<cstdlib>
#include<cstdio>
typedef int ElemType;
void SHELL_INSERT(ElemType *A,int len, int dk)
{//0ºÅµ¥ÔªÎ´ÓÃ
	int i, j;
	for (i = dk + 1; i <= len; i++) {
		if (A[i] < A[i - dk]) {
			A[0] = A[i];
			for (j = i - dk; (j > 0) && A[0] < A[j]; j -= dk) 
				A[j + dk] = A[j];
			A[j + dk] = A[0];
		}//if
	}//for
}//SHELL_INSERT
void Shell_Sort(ElemType *A, int len, int t)
{
	int k, dk;
	for (k = 0; k <= t; k++) {
		dk = (int)(pow(2, t - k + 1) - 1);
		SHELL_INSERT(A, len, dk);
	}
}//Shell_Sort
#endif // !SHELLSORT_H
#pragma once

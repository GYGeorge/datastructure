#ifndef BUBBLESORT_H
#define BUBBLESORT_H
#include<iostream>
#include<cstdlib>
#include<cstdio>
typedef int ElemType;
void Bubble_Sort(ElemType *A, int len)
{
	int i = len - 1;
	int j, lastExchange;
	ElemType temp;
	while (i > 0) {
		lastExchange = 0;
		for (j = 0; j < i; j++)
			if (A[j] > A[j + 1]) {
				temp = A[j];
				A[j] = A[j + 1];
				A[j + 1] = temp;
				lastExchange = j;
			}//if
		i = lastExchange;
	}//while
}//Bubble_Sort
#endif // BUBBLESORT_H
#pragma once

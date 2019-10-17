#ifndef SELECTSORT_H
#define SELECTSORT_H
#include<iostream>
#include<cstdlib>
#include<cstdio>
typedef int ElemType;
int SelectMinKey(ElemType *A,int len, int i)
{
	int j,t = i;
	for (j = i + 1; j < len; j++) {
		if (A[j] < A[t]) 
			t = j;
	}//for
	return t;
}//SelectMinKey
void Select_Sort(ElemType *A, int len)
{
	ElemType temp;
	int i, j;
	for (i = 0; i < len; i++) {
		j = SelectMinKey(A, len, i);
		if (i != j) {
			swap(A[i], A[j]);
		}//if
	}//for
}//Select_Sort
#endif // !SELECTSORT_H
#pragma once

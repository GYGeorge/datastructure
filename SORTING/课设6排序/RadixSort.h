#ifndef RADIXSORT_H
#define RADIXSORT_H

#include<iostream>
using namespace std;
void COUNTING_SORT(int *A, int n, int m)
{//A待排序数组，n为A中元素数，范围0~m-1 
	int *B = new int[n];
	int i, j, key, index;
	int *equal = new int[m];
	int *cpot = new int[m];
	int *next = new int[m];
	for (i = 0; i < m; i++) equal[i] = 0;
	for (j = 0; j < n; j++) equal[A[j]]++;
	cpot[0] = 0;
	for (i = 1; i < m; i++) cpot[i] = cpot[i - 1] + equal[i - 1];
	for (i = 0; i < n; i++) {
		key = A[i];
		index = cpot[key];
		B[index] = A[i];
		cpot[key]++;
	}//for
	for (i = 0; i < n; i++)
		A[i] = B[i];
	delete[]equal;
	delete[]cpot;
	delete[]next;
	delete[]B;
}//COUNTING_SORT
#endif // !RADIXSORT_H


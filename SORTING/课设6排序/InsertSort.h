#ifndef INSERTSORT_H
#define INSERTSORT_H
#include<iostream>
#include<cstdlib>
#include<cstdio>
typedef int ElemType;
void Insert_Sort(ElemType A[], int len)
{
	int i, j;
	int temp;
	for (i = 0; i < len; i++)
	{
		temp = A[i];
		j = i - 1;
		//与已排序的数逐一比较，大于temp时，该数移后
		while ((j >= 0) && (A[j] > temp))
		{
			A[j + 1] = A[j];
			j--;
		}
		//存在大于temp的数
		if (j != i - 1)
			A[j + 1] = temp;
	}
}//Insert_Sort
#endif // INSERTSORT_H
#pragma once

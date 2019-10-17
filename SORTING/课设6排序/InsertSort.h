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
		//�������������һ�Ƚϣ�����tempʱ�������ƺ�
		while ((j >= 0) && (A[j] > temp))
		{
			A[j + 1] = A[j];
			j--;
		}
		//���ڴ���temp����
		if (j != i - 1)
			A[j + 1] = temp;
	}
}//Insert_Sort
#endif // INSERTSORT_H
#pragma once

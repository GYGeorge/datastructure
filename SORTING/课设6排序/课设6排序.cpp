// 课设6排序.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//#include"pch.h"
#include<iostream>
#include<iomanip>
#include<time.h>
#include<cstdlib>
#include<cstdio>
#include<fstream>
#include"InsertSort.h"
#include"ShellSort.h"
#include"MergeSort.h"
#include"QuickSort.h"
#include"BubbleSort.h"
#include"HeapSort.h"
#include"SelectSort.h"
#include"RadixSort.h"
using namespace std;
#define NUMBER 20000
int compare1(const void *a, const void *b)
{
	return *(int*)a - *(int*)b;
}//compare
int compare2(const void *a, const void *b)
{
	return *(int*)b - *(int*)a;
}//compare
void WriteFile(char *filena, int *a)
{
	ofstream fo;
	fo.open(filena, ios::app);
	int i = 0;
	for (i = 0; i < NUMBER; i++)
		fo << a[i] << " ";
	fo << endl;
	fo.close();
}//WriteFile
void ArrayInsertSort(int asample[10][NUMBER])
{
	int a[10][NUMBER];
	int	m, n;
	for (m = 0; m < 10; m++)
		for (n = 0; n < NUMBER; n++)
			a[m][n] = asample[m][n];
	double coutime[10];
	double sta, end;
	int i;
	for (i = 0; i < 10; i++) {
		sta = clock();
		Insert_Sort(a[i], NUMBER);
		end = clock();
		coutime[i] = end - sta;
	}//for
	cout << "InsertSort: ";
	for (i = 0; i < 10; i++) {
		cout << setw(5) << coutime[i];
	}//for
	cout << endl;
	/*for (i = 0; i < NUMBER; i++) {
		cout << a[4][i] << " ";
	}
	cout << endl;*/
}//ArrayInsertSort
void ArraySelectSort(int asample[10][NUMBER])
{
	int a[10][NUMBER];
	int	m, n;
	for (m = 0; m < 10; m++)
		for (n = 0; n < NUMBER; n++)
			a[m][n] = asample[m][n];
	double coutime[10];
	double sta, end;
	int i;
	for (i = 0; i < 10; i++) {
		sta = clock();
		Select_Sort(a[i], NUMBER);
		end = clock();
		coutime[i] = end - sta;
	}//for
	cout << "SelectSort: ";
	for (i = 0; i < 10; i++) {
		cout << setw(5) << coutime[i];
	}//for
	cout << endl;
	/*for (i = 0; i < NUMBER; i++) {
		cout << a[4][i] << " ";
	}
	cout << endl;*/
}//ArrayInsertSort
void ArrayShellSort(int asample[10][NUMBER])
{
	int a[10][NUMBER+1];
	int	m, n;
	for (m = 0; m < 10; m++) {
		a[m][0] = 0;
		for (n = 0; n < NUMBER; n++)
			a[m][n + 1] = asample[m][n];
	}//for
	double coutime[10];
	double sta, end;
	int i;
	for (i = 0; i < 10; i++) {
		sta = clock();
		Shell_Sort(a[i], NUMBER, (int)log2(NUMBER+1));
		end = clock();
		coutime[i] = end - sta;
	}//for
	cout << "ShellSort: ";
	for (i = 0; i < 10; i++) {
		cout << setw(5) << coutime[i];
	}//for
	cout << endl;
	/*for (i = 1; i <= NUMBER; i++) {
		cout << a[4][i] << " ";
	}
	cout << endl;*/
}//ArrayInsertSort
void ArrayMergeSort(int asample[10][NUMBER])
{
	int a[10][NUMBER];
	int	m, n;
	for (m = 0; m < 10; m++)
		for (n = 0; n < NUMBER; n++)
			a[m][n] = asample[m][n];
	double coutime[10];
	double sta, end;
	int i;
	for (i = 0; i < 10; i++) {
		sta = clock();
		Merge_Sort(a[i], 0, NUMBER - 1);
		end = clock();
		coutime[i] = end - sta;
	}//for
	cout << "MergeSort: ";
	for (i = 0; i < 10; i++) {
		cout << setw(5) << coutime[i];
	}//for
	/*cout << endl;
	for (i = 0; i < NUMBER; i++) {
		cout << a[4][i] << " ";
	}*/
	cout << endl;
}//ArrayMergeSort
void ArrayQuickSort(int asample[10][NUMBER])
{
	int a[10][NUMBER];
	int	m, n;
	for (m = 0; m < 10; m++)
		for (n = 0; n < NUMBER; n++)
			a[m][n] = asample[m][n];
	double coutime[10];
	double sta, end;
	int i;
	for (i = 0; i < 10; i++) {
		sta = clock();
		Quick_Sort(a[i], 0, NUMBER - 1);
		end = clock();
		coutime[i] = end - sta;
	}//for
	cout << "QuickSort: ";
	for (i = 0; i < 10; i++) {
		cout << setw(5) << coutime[i];
	}//for
	cout << endl;
	/*for (i = 0; i < NUMBER; i++) {
		cout << a[4][i] << " ";
	}
	cout << endl;*/

}//ArrayMergeSort
void ArrayBubbleSort(int asample[10][NUMBER])
{
	int a[10][NUMBER];
	int	m, n;
	for (m = 0; m < 10; m++)
		for (n = 0; n < NUMBER; n++)
			a[m][n] = asample[m][n];
	double coutime[10];
	double sta, end;
	int i;
	for (i = 0; i < 10; i++) {
		sta = clock();
		Bubble_Sort(a[i], NUMBER);
		end = clock();
		coutime[i] = end - sta;
	}//for
	cout << "BubbleSort: ";
	for (i = 0; i < 10; i++) {
		cout << setw(5) << coutime[i];
	}//for
	cout << endl;
	/*for (i = 0; i < NUMBER; i++) {
		cout << a[4][i] << " ";
	}
	cout << endl;*/
}//ArrayBubbleSort
void ArrayHeapSort(int asample[10][NUMBER])
{
	int i;
	int a[10][NUMBER + 1];
	int	m, n;
	for (m = 0; m < 10; m++) {
		a[m][0] = 0;
		for (n = 0; n < NUMBER; n++)
			a[m][n + 1] = asample[m][n];
	}//for
	double coutime[10];
	double sta, end;
	for (i = 0; i < 10; i++) {
		sta = clock();
		Heap_Sort(a[i], NUMBER);
		end = clock();
		coutime[i] = end - sta;
	}//for
	cout << "HeapSort: ";
	for (i = 0; i < 10; i++) {
		cout << setw(5) << coutime[i];
	}//for
	cout << endl;
	/*for (i = 1; i <= NUMBER; i++) {
		cout << a[4][i] << " ";
	}
	cout << endl;*/
}//ArrayHeapSort
void ArrayRadixSort(int asample[10][NUMBER])
{
	int a[10][NUMBER];
	int	m, n;
	for (m = 0; m < 10; m++)
		for (n = 0; n < NUMBER; n++)
			a[m][n] = asample[m][n];
	double coutime[10];
	double sta, end;
	int i;
	for (i = 0; i < 10; i++) {
		sta = clock();
		COUNTING_SORT(a[i], NUMBER, NUMBER + 1);
		end = clock();
		coutime[i] = end - sta;
	}//for
	cout << "RadixSort: ";
	for (i = 0; i < 10; i++) {
		cout << setw(5) << coutime[i];
	}//for
	/*cout << endl;
	for (i = 0; i < NUMBER; i++) {
		cout << a[4][i] << " ";
	}
	cout << endl;*/
}//ArrayRadixSort
int main()
{

	int sample[10][NUMBER];
	srand(time(NULL));
	int i, j;
	for (i = 0; i < 10; i++)//产生10组随机数
		for (j = 0; j < NUMBER; j++)
			sample[i][j] = rand() % (NUMBER + 1);
	qsort(sample[0], NUMBER, sizeof(int), compare2);//第一个样本正序
	qsort(sample[1], NUMBER, sizeof(int), compare1);//第二个样本逆序
	char filename[] = "sample.txt";
	for (i = 0; i < 10; i++) {
		WriteFile(filename, sample[i]);
	}//for
	cout << "TimeUnit-ms" << endl;
	ArrayInsertSort(sample);
	ArrayBubbleSort(sample);
	ArrayShellSort(sample);
	ArrayMergeSort(sample);
	ArrayQuickSort(sample);
	ArrayHeapSort(sample);
	ArraySelectSort(sample);
	ArrayRadixSort(sample);
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

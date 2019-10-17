#ifndef RADIXSORT_H
#define RADIXSORT_H
#include<iostream>
#include<cstdlib>
#include<cstdio>
#define _MAX_NUM_OF_KEY		8
#define RADIX				10
#define MAX_SPACE           10000
typedef int KeysType;
typedef struct {
	KeysType	keys[_MAX_NUM_OF_KEY];
	int			next;
}SLCell, Cell[MAX_SPACE];
typedef struct {
	SLCell		r[MAX_SPACE];
	int			keynum;
	int			recnum;
}SLList;
typedef int ArrType[RADIX];
void Distribute(Cell &r, int i, ArrType &f, ArrType e)
{
	int j, p;
	for (j = 0; j < RADIX; j++) f[j] = 0;//³õÊ¼»¯
	for (p = r[0].next; p; p = r[p].next){
		j = ord(r[p].keys[i]);
		if (!f[j]) f[j] = p;
		else r[e[j]].next = p;
		e[j] = p;
	}
}
void Collect(Cell &r, int i, ArrType f, ArrType e)
{
	int j, t;
	for (j = 0; !f[j]; j = succ(j));
	r[0].next = f[j];
	t = e[j];
	while (j < RADIX) {
		for (j = succ(j); j < RADIX - 1 && !f[j]; j = succ(j));
		if (f[j]) {
			r[t].next = f[j];
			t = e[j];
		}
	}
	r[t].next = 0;
}
void Radix_Sort(SLList &L)
{
	int i = 0;
	for (i = 0; i < L.recnum; i++) L.r[i].next = i + 1;
	L.r[L.recnum].next = 0;
	ArrType f, e;
	for (i = 0; i < L.keynum; i++) {
		Distribute(L.r, i, f, e);
		Collect(L.r, i, f, e);
	}
}
#endif // RADIXSORT_H
#pragma once

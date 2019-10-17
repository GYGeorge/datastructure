#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstdio>
#include"find.h"
using namespace std;
int main()
{
	FILE *fptr;
	fptr=fopen("test.txt","r");
	BiTree T;
	InitBiTree(T);
	Read_File(fptr, T);
	
	fgetc(fptr);
	
	
	FindingKey(T,fptr);
	
}





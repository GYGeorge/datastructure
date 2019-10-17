#ifndef TREE_H
#define TREE_H
#include<iostream>
#include<fstream>
#include<cstdio>
#include<cstdlib>
#include<string.h>
#include"STATUS.h"
#define STRING_LENGTH 20
#define left 0
#define right 1
using namespace std;
typedef char* TElemType;
typedef struct BiTreeNode {
	TElemType			data;
	struct BiTreeNode  *lchild, *rsibling;
}BiTreeNode,*BiTree;
Status InitBiTree(BiTree &T)
{
	T = (BiTree)malloc(sizeof(BiTreeNode));
	if (!T)exit(OVERFLOW);
	T->data = (char*)malloc(STRING_LENGTH * sizeof(char));
	T->lchild = NULL;
	T->rsibling = NULL;
	return OK;
}//InitBiTree
int max(int i, int j) {
	if (i >= j)return i;
	else return j;
}//max
int BiTreeDepth_Child_Sibling(BiTree T)//孩子——兄弟树求树的深度
{
	if (T == NULL) return 0;
	int i, j, cou;
	i = BiTreeDepth_Child_Sibling(T->lchild);
	j = BiTreeDepth_Child_Sibling(T->rsibling);
	cou = max(i, j);
	if (cou == i) return ++cou;
	else if (cou == j) return cou;
}
Status PrintTree(BiTree T, bool tag)
{
	if (T == NULL) return OK;
	if (tag == left) {
		cout << "-";
		cout << T->data << endl;
		
		PrintTree(T->lchild, left);	
	}
	else {
		cout << T->data << endl;
		PrintTree(T->lchild, left);
		
	}PrintTree(T->rsibling, right);
	return OK;
}//PrintTree
Status Read_String(FILE *fptr, char *str)//读字符串类型
{
	char fch = (char)fgetc(fptr);
	if (fch == '{') { fseek(fptr, -1L, SEEK_CUR); return ERROR; }
	char temp = (char)fgetc(fptr);
	int i = 0;
	while (temp != '"') {
		if (temp == '\\') {
			temp = fgetc(fptr);
			str[i] = temp;
			i++;
		}//if
		else {
			str[i] = temp;
			i++;
		}
		temp = fgetc(fptr);
	}
	str[i] = '\0';
	return OK;
}//Read_String
void Read_File(FILE *fptr, BiTree &T)//读{}内的内容
{
	BiTree p = T, cur = NULL;
	char a=(char)fgetc(fptr); fgetc(fptr);//读{和\n
	char end = fgetc(fptr);
	while (end != '}') {
		if (end == '"') fseek(fptr, -1L, SEEK_CUR);//是"就退一个位置
		Read_String(fptr, p->data);
		char ch; 
		fscanf(fptr, "%c ", &ch);//读冒号和空格
		BiTree LNode; InitBiTree(LNode);
		if (Read_String(fptr, LNode->data) == ERROR) {
			cur = p;
			p->lchild = LNode; p = p->lchild;
			LNode = NULL; free(LNode);
			Read_File(fptr, p);
			fgetc(fptr); end = (char)fgetc(fptr); //读逗号和\n或者\n和}
			p = cur;
		}//if
		else {
			p->lchild = LNode;
			fgetc(fptr); end = (char)fgetc(fptr);//读逗号和\n或者\n和}	
		}//else
		if (end != '}') {
			BiTree RNode; InitBiTree(RNode);
			p->rsibling = RNode; p = RNode;
		}//if
	}//while
}//Read_File
Status CreatTree(BiTree &T, char *filena)
{
	InitBiTree(T);
	FILE *fptr;
	fptr = fopen(filena, "r");
    int line, check;
	fscanf(fptr, "%d %d", &line, &check);
	char temp;
	temp = fgetc(fptr);
	if (temp != '{') return ERROR;
	Read_File(fptr, T);
	return OK;
}//CreatTree
Status visit(TElemType e) {
	cout << e << endl;
	return OK;
}//visit
Status PreOrderTraverse(BiTree T, Status(*visit)(TElemType e))//先序遍历
{
	if (T == NULL) return OK;
	visit(T->data);
	PreOrderTraverse(T->lchild, visit);
	PreOrderTraverse(T->rsibling, visit);
	return OK;
}//PreOrderTraverse

#endif // !TREE_H

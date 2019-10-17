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
int BiTreeDepth_Child_Sibling(BiTree T)//���ӡ����ֵ������������
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
Status Read_String(FILE *fptr, char *str)//���ַ�������
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
void Read_File(FILE *fptr, BiTree &T)//��{}�ڵ�����
{
	BiTree p = T, cur = NULL;
	char a=(char)fgetc(fptr); fgetc(fptr);//��{��\n
	char end = fgetc(fptr);
	while (end != '}') {
		if (end == '"') fseek(fptr, -1L, SEEK_CUR);//��"����һ��λ��
		Read_String(fptr, p->data);
		char ch; 
		fscanf(fptr, "%c ", &ch);//��ð�źͿո�
		BiTree LNode; InitBiTree(LNode);
		if (Read_String(fptr, LNode->data) == ERROR) {
			cur = p;
			p->lchild = LNode; p = p->lchild;
			LNode = NULL; free(LNode);
			Read_File(fptr, p);
			fgetc(fptr); end = (char)fgetc(fptr); //�����ź�\n����\n��}
			p = cur;
		}//if
		else {
			p->lchild = LNode;
			fgetc(fptr); end = (char)fgetc(fptr);//�����ź�\n����\n��}	
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
Status PreOrderTraverse(BiTree T, Status(*visit)(TElemType e))//�������
{
	if (T == NULL) return OK;
	visit(T->data);
	PreOrderTraverse(T->lchild, visit);
	PreOrderTraverse(T->rsibling, visit);
	return OK;
}//PreOrderTraverse

#endif // !TREE_H

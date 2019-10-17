#ifndef FIND_H
#define FIND_H
#include"tree.h"
typedef char* ElemType;
typedef struct LNode {
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;
Status InitList_L(LinkList &L)//创建只有一个头结点空链表
{
	L = (LinkList)malloc(sizeof(LNode));
	if (!L) exit(OVERFLOW);
	L->data = (char*)malloc(STRING_LENGTH * sizeof(char));
	L->next = NULL;
	return OK;
}//InitList_L
Status DestroyList_L(LinkList &L)//销毁单链表
{
	LinkList p, q;
	p = L;
	while (p->next != NULL) {
		q = p;
		p = p->next;
		q->next = NULL;
		free(q);
	}
	free(p);
	return OK;
}//DestroyList_L
Status ClearList_L(LinkList &L)//重置单链表
{
	DestroyList_L(L);
	InitList_L(L);
	return OK;
}//ClearList_L
Status ListEmpty_L(LinkList &L)//检查链表是否为空
{
	if (L->next == NULL) return TRUE;
	else return FALSE;
}//ListEmpty_L
int ListLength_L(LinkList L)//返回链表长度
{
	int count = 1;
	LinkList p;
	if (L->next != NULL) {
		p = L->next;
	}
	else return 0;
	while (p->next != NULL) {
		p = p->next;
		count++;
	}
	return count;
}//ListLength_L
Status ListTraverse(LinkList L, Status(*visit)(ElemType a))//遍历并输出
{
	LinkList p = L;
	if (p == NULL) return ERROR;
	while (p != NULL) {
		visit(p->data);
		p = p->next;
	}
	return OK;
}//ListTraverse
Status CheckingKey(LinkList &L, FILE *fptr)//将文件中一行的内容读成查找关键字链表
{
	LinkList  p;
	p = L;
	int i = 0;
	char ch; ch = fgetc(fptr);
	while (1) {
		while (ch != '.'&&ch != '\n'&& !feof(fptr)) {
			p->data[i] = ch;
			i++;
			ch = fgetc(fptr);
		}//while
		p->data[i] = '\0';
		if (ch == '\n'||feof(fptr)) break;
		ch = fgetc(fptr);
		i = 0;
		LinkList node;
		InitList_L(node);
		p->next = node;
		p = node;
		node = NULL;
		free(node);
	}//while
	return OK;
}//CheckingKey
Status Find(BiTree T, LinkList L)
{
	BiTree pT = T;
	LinkList pL = L;
	while (pT) {
		if (strcmp(pT->data, pL->data) == 0) {
			pL = pL->next;
			pT = pT->lchild;
			if (pL == NULL) {
				if (pT->lchild == NULL && pT->rsibling == NULL) 
					cout << "STRING " << pT->data << endl;
				else cout << "OBJECT" << endl;
				return OK;
			}//if
			else {
				if (Find(pT, pL) == OK) return OK;
				else return ERROR;
			}
		}
		pT = pT->rsibling;
	}
	cout << "NOTEXIST" << endl;
	return ERROR;
}//find
Status FindingKey(BiTree T, FILE *fptr)
{
	while (!feof(fptr)) {
		LinkList L; 
		InitList_L(L);
		CheckingKey(L, fptr);
		Find(T, L);
		DestroyList_L(L);
	}//while
	return OK;
}
#endif // !FIND_H
#pragma once

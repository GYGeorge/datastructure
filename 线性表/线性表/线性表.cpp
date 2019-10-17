#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
#include"STATUS.h"
#define LIST_INIT_SIZE 100    //���Ա�洢�ռ�ĳ�ʼ������
#define LISEINCREMENT  10	  //���Ա�洢�ռ�ķ�������
typedef int ElemType;
typedef struct {
	ElemType *elem;			  //�洢�ռ��ַ
	int length;				  //��ǰ����
	int listsize;	        //��ǰ����Ĵ洢����
}Sqlist;
Status InitList(Sqlist &L)//����һ���ձ�
{
	L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L.elem) exit(OVERFLOW);   //�洢����ʧ��
	L.length = 0;				   //�ձ���Ϊ0
	L.listsize = LIST_INIT_SIZE;   //��ʼ�洢����
	return OK;
}//InitList
Status DestoryList(Sqlist &L)//�������Ա�
{
	free(L.elem);
	return OK;
}//DestoryList
Status ClearList(Sqlist &L)//����Ϊ�ձ�
{
	free(L.elem);
	L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	return OK;
}//ClearList
Status ListEmpty(Sqlist L)//����Ƿ�Ϊ��
{
	if (L.length = 0) return TRUE;
	else return FALSE;
}//ListEmpty
int ListLength(Sqlist L)//��������Ԫ�ظ���
{
	return L.length;
}//ListEmpty
Status GetElem(Sqlist L, int i, ElemType &e)//���ص�i��Ԫ�ص�ֵ
{
	if (i >= 1 || i <= ListLength(L)) {
		e = L.elem[i];
		return OK;
	}
	else exit(ERROR);
}//GetElem
Status compare(ElemType a,ElemType b){}
int LocateElem(Sqlist L,ElemType e,Status(*compare)(ElemType a,ElemType b))
{
    int i;
    for(i=0;i<L.length;i++){
        compare(L.elem[i],e);
    }
}//LocateElem
int BINARY_SEARCH(ElemType A[],int f ,int b,ElemType x) //���ֲ��Һ���
{
	int front = f, middle, back = b;
	while (front <= back) {
		middle = (front + back) / 2;
		if (A[middle] == x)
			break;
		else if (A[middle] != x) {
			if (A[middle] > x) {
				back = middle - 1;
			}
			else if (A[middle] < x) {
				front = middle + 1;
			}
		}
	}
	return middle;
}//BINARY_SEARCH
Status PriorElem(Sqlist L, ElemType cur_e, ElemType &pre_e)//��cur_e��ǰ��
{
	if (cur_e == L.elem[0]) return ERROR;
	int m;
	m = BINARY_SEARCH(L.elem, 0, L.length - 1, cur_e);
	pre_e = L.elem[m - 1];
	return OK;
}//PriorElem
Status NextElem(Sqlist L, ElemType cur_e, ElemType &next_e)//��cur_e�ĺ��
{
	if (cur_e == L.elem[L.length-1]) return ERROR;
	int m;
	m = BINARY_SEARCH(L.elem, 0, L.length - 1, cur_e);
	next_e= L.elem[m + 1];
	return OK;
}//NextElem
Status ListInsert(Sqlist &L, int i, ElemType e)//iǰ��������Ԫ��
{
	ElemType *newbase,*q,*p;
	if (i<1 || i>ListLength(L)+1) return ERROR;
	if (L.length >= L.listsize) {
		newbase = (ElemType *)realloc(L.elem, (L.listsize + LISEINCREMENT) * sizeof(ElemType));
		if (!newbase) exit(OVERFLOW);
		L.elem = newbase;
		L.listsize += LISEINCREMENT;
	}
	q = &(L.elem[i - 1]);
	for (p = &(L.elem[L.length - 1]); p >= q; --p)
		*(p + 1) = *p;
	*q = e;
	L.length++;
	return OK;
}//ListInsert
Status ListDelete(Sqlist &L, int i, ElemType &e)//ɾ������Ԫ��
{
	ElemType  *q, *p;
	if (i<1 || i>ListLength(L)) return ERROR;
	p = &(L.elem[i - 1]);
	e = *p;
	q = L.elem + L.length - 1;
	for (++p; p <= q; ++p)
		*(p - 1) = *p;
	--L.length;
	return OK;
}//ListDelete
Status visit(int a)
{
    cout<<a<<endl;
    return OK;
}//visit
Status ListTraverse(Sqlist L,Status(*visit)(int a))
{
    int i;
    for(i = 0;i < L.length ;i++)
    {
        visit(L.elem[i]);
    }
    return OK;
}//ListTraverse
Status ListReverse(Sqlist &L)//��ת���Ա�
{
	int temp, front, back;
	front = 0;
	back = L.length - 1;
	while(front < back)
	{
		temp = L.elem[back];
		L.elem[back] = L.elem[front];
		L.elem[front] = temp;
		back--;
		front++;
	}
	return OK;
}//ListReverse
Status Delete_ik(Sqlist &L,int i,int k)//ɾ���ӵ�i����ʼ��k��Ԫ��
{
	if (i < 0 || k < 0 || (i + k)>L.length)
		return ERROR;
	int shift = i;
	while((shift+k+1)<=L.length)
	{
		L.elem[shift - 1] = L.elem[shift + k];
		shift++;
	}
	return OK;
}//Delete_ik
typedef struct LNode {
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;
void CreatList_L(LinkList &Q,Sqlist L)//��˳���ת��������
{
	LinkList p;
	Q = (LinkList)malloc(sizeof(LNode));
	Q->next = NULL;//�½�һ��ͷ���
	int i;
	for (i = L.length-1; i >= 0; --i) {
		p = (LinkList)malloc(sizeof(LNode));
		p->data = L.elem[i];
		p->next = Q->next;//����
		Q->next = p;
	}
}//CreatList_L
void GetOut_L(LinkList &L, int n, int m)//Լɪ����������
{
	LinkList cur = L->next;
	int i = 2;                                         //��length��ȡǰn��
	LinkList p, q;
	while (i <= n) {                                      //�ҵ���n��
		if (i < n&&cur->next == NULL) exit(OVERFLOW);     //����û��n��Ԫ��
		cur = cur->next;
		i++;
	}
	q = cur->next;											//ɾ��n�����Ԫ��
	cur->next = NULL;
	while (q != NULL) {                                     //����ɾ��
		p = q;
		q = q->next;
		p->next = NULL;
		free(p);
	}

	int count = 0, length = n;
	ElemType e;
	cur = L->next;
	LinkList Delete;
	while (cur->next != NULL) {//�ҵ����һ��Ԫ��
		cur = cur->next;
	}
	cur->next = L->next;//�Ƴ�ѭ��������
	while (length != 1) {
		while ((count + 1) != m) {
			cur = cur->next;
			count++;
		}
		Delete = cur->next;		   //ɾ������
		cur->next = Delete->next;
		e = Delete->data;
		free(Delete);
		length--;
		printf("%d", e);            //��ӡ��ɾ����Ԫ��
		count = 0;	                //���Ƽ�����
	}
	e = cur->data;
	printf("%d ", e);                //��ӡ�����һ��Ԫ��
}//GetOut_L
void GetOut(Sqlist L,int n,int m)//Լɪ������˳���
{
	LinkList Q;
	CreatList_L(Q, L);
	GetOut_L(Q, n, m);
}//GetOut
Status QuickSort(Sqlist &L) 
{

}
void Insert_sort(Sqlist &L)//��������˳���
{
	ElemType temp, temp_1;
	int i, j;
	//ElemType *A = L.elem;
	for (i = 0; i < L.length; i++) {
		for (j = 0; j < i; j++) {
			if (L.elem[j] > L.elem[i]) {
				ListDelete(L, i + 1, temp);
				ListInsert(L, j + 1, temp);
				break;
			}
		}
	}
}//Insert_sort
/*int main()
{//��������
	ElemType e;
	Sqlist L;
	int n, m;
	cin >> n;
	cin >> m;
	if (!InitList(L))
		return ERROR;
	int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
	L.elem = a;
	L.length = 10;
	ListTraverse(L, *visit);
	ElemType pre, next;
	PriorElem(L, n, pre);
	NextElem(L, n, next);
	cout << pre << " " << next << " " << endl;
	ListInsert(L, m, 99);
	ListDelete(L, m, e);
	ListTraverse(L, *visit);
	cout << e << endl;
	cout << ListLength(L) << endl;

}*/

 /*int main()//����
{
    int i;
    Sqlist New_list;
    if(!InitList(New_list))
        return ERROR;
    int a[10]={0,1,2,3,4,5,6,7,8,9};
    New_list.elem = a;
    New_list.length=10;
    ListReverse(New_list);
    for(i=0;i<10;i++){
        cout<<New_list.elem[i]<<" ";
    }
    cout<<endl;
    ListReverse(New_list);
    ListTraverse(New_list,*visit);

}*/

int main()//Լɪ������
{
    Sqlist L;
    int n,m;
    cin>>n;
    cin>>m;
    if(!InitList(L))
        return ERROR;
    int a[10]={1,2,3,4,5,6,7,8,9,10};
    L.elem = a;
    L.length = 10;
    ListTraverse(L,*visit);
    GetOut(L,n,m);

}












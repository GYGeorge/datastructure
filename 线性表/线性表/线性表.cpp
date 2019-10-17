#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
#include"STATUS.h"
#define LIST_INIT_SIZE 100    //线性表存储空间的初始分配量
#define LISEINCREMENT  10	  //线性表存储空间的分配增量
typedef int ElemType;
typedef struct {
	ElemType *elem;			  //存储空间基址
	int length;				  //当前长度
	int listsize;	        //当前分配的存储总量
}Sqlist;
Status InitList(Sqlist &L)//创建一个空表
{
	L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L.elem) exit(OVERFLOW);   //存储分配失败
	L.length = 0;				   //空表长度为0
	L.listsize = LIST_INIT_SIZE;   //初始存储容量
	return OK;
}//InitList
Status DestoryList(Sqlist &L)//销毁线性表
{
	free(L.elem);
	return OK;
}//DestoryList
Status ClearList(Sqlist &L)//重制为空表
{
	free(L.elem);
	L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	return OK;
}//ClearList
Status ListEmpty(Sqlist L)//检查是否为空
{
	if (L.length = 0) return TRUE;
	else return FALSE;
}//ListEmpty
int ListLength(Sqlist L)//返回数据元素个数
{
	return L.length;
}//ListEmpty
Status GetElem(Sqlist L, int i, ElemType &e)//返回第i个元素的值
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
int BINARY_SEARCH(ElemType A[],int f ,int b,ElemType x) //二分查找函数
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
Status PriorElem(Sqlist L, ElemType cur_e, ElemType &pre_e)//找cur_e的前驱
{
	if (cur_e == L.elem[0]) return ERROR;
	int m;
	m = BINARY_SEARCH(L.elem, 0, L.length - 1, cur_e);
	pre_e = L.elem[m - 1];
	return OK;
}//PriorElem
Status NextElem(Sqlist L, ElemType cur_e, ElemType &next_e)//找cur_e的后继
{
	if (cur_e == L.elem[L.length-1]) return ERROR;
	int m;
	m = BINARY_SEARCH(L.elem, 0, L.length - 1, cur_e);
	next_e= L.elem[m + 1];
	return OK;
}//NextElem
Status ListInsert(Sqlist &L, int i, ElemType e)//i前插入数据元素
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
Status ListDelete(Sqlist &L, int i, ElemType &e)//删除数据元素
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
Status ListReverse(Sqlist &L)//逆转线性表
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
Status Delete_ik(Sqlist &L,int i,int k)//删除从第i个开始的k个元素
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
void CreatList_L(LinkList &Q,Sqlist L)//将顺序表转换成链表
{
	LinkList p;
	Q = (LinkList)malloc(sizeof(LNode));
	Q->next = NULL;//新建一个头结点
	int i;
	for (i = L.length-1; i >= 0; --i) {
		p = (LinkList)malloc(sizeof(LNode));
		p->data = L.elem[i];
		p->next = Q->next;//插入
		Q->next = p;
	}
}//CreatList_L
void GetOut_L(LinkList &L, int n, int m)//约瑟夫环问题链表
{
	LinkList cur = L->next;
	int i = 2;                                         //从length中取前n个
	LinkList p, q;
	while (i <= n) {                                      //找到第n个
		if (i < n&&cur->next == NULL) exit(OVERFLOW);     //链表没有n个元素
		cur = cur->next;
		i++;
	}
	q = cur->next;											//删除n后面的元素
	cur->next = NULL;
	while (q != NULL) {                                     //依次删除
		p = q;
		q = q->next;
		p->next = NULL;
		free(p);
	}

	int count = 0, length = n;
	ElemType e;
	cur = L->next;
	LinkList Delete;
	while (cur->next != NULL) {//找到最后一个元素
		cur = cur->next;
	}
	cur->next = L->next;//制成循环单链表
	while (length != 1) {
		while ((count + 1) != m) {
			cur = cur->next;
			count++;
		}
		Delete = cur->next;		   //删除操作
		cur->next = Delete->next;
		e = Delete->data;
		free(Delete);
		length--;
		printf("%d", e);            //打印出删除的元素
		count = 0;	                //重制计数器
	}
	e = cur->data;
	printf("%d ", e);                //打印出最后一个元素
}//GetOut_L
void GetOut(Sqlist L,int n,int m)//约瑟夫环问题顺序表
{
	LinkList Q;
	CreatList_L(Q, L);
	GetOut_L(Q, n, m);
}//GetOut
Status QuickSort(Sqlist &L) 
{

}
void Insert_sort(Sqlist &L)//插入排序顺序表
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
{//基本操作
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

 /*int main()//倒置
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

int main()//约瑟夫问题
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












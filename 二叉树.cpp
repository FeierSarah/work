#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100 /* 存储空间初始分配量 */
#define MAX_TREE_SIZE 100 /* 二叉树的最大结点数 */

typedef int Status;		
typedef int TElemType; 
typedef TElemType SqBiTree[MAX_TREE_SIZE];

typedef struct
{
	int level,order; 
}Position;

TElemType Nil=0;

Status visit(TElemType c)
{
	printf("%d ",c);
	return OK;
}

Status InitBiTree(SqBiTree T)
{
	int i;
	for(i=0;i<MAX_TREE_SIZE;i++)
		T[i]=Nil; /* 初值为空 */
	return OK;
}

/* 按层序次序输入构造顺序存储的二叉树T */
Status CreateBiTree(SqBiTree T)
{ 
	int i=0;
	while(i<10)
	{
		T[i]=i+1;
		
		if(i!=0&&T[(i+1)/2-1]==Nil&&T[i]!=Nil) 
		{
			printf("出现无双亲的非根结点%d\n",T[i]);
			exit(ERROR);
		}
		i++;
	}
	while(i<MAX_TREE_SIZE)
	{
		T[i]=Nil;
		i++;
	}

	return OK;
}

#define ClearBiTree InitBiTree 
Status BiTreeEmpty(SqBiTree T)
{ 
	if(T[0]==Nil) 
		return TRUE;
	else
		return FALSE;
}

int BiTreeDepth(SqBiTree T)
{ 
   int i,j=-1;
   for(i=MAX_TREE_SIZE-1;i>=0;i--) 
     if(T[i]!=Nil)
       break;
   i++; 
   do
     j++;
   while(i>=powl(2,j));
   return j;
}

Status Root(SqBiTree T,TElemType *e)
{ 
	if(BiTreeEmpty(T)) 
		return ERROR;
	else
	{	
		*e=T[0];
		return OK;
	}
}

TElemType Value(SqBiTree T,Position e)
{ 
	 return T[(int)powl(2,e.level-1)+e.order-2];
}

Status Assign(SqBiTree T,Position e,TElemType value)
{ 
	int i=(int)powl(2,e.level-1)+e.order-2; 
	if(value!=Nil&&T[(i+1)/2-1]==Nil) 
		return ERROR;
	else if(value==Nil&&(T[i*2+1]!=Nil||T[i*2+2]!=Nil)) 
		return ERROR;
	T[i]=value;
	return OK;
}

TElemType Parent(SqBiTree T,TElemType e)
{ 
	int i;
	if(T[0]==Nil) 
		return Nil;
	for(i=1;i<=MAX_TREE_SIZE-1;i++)
		if(T[i]==e) 
			return T[(i+1)/2-1];
	return Nil; 
}

TElemType LeftChild(SqBiTree T,TElemType e)
{ 
	int i;
	if(T[0]==Nil) 
		return Nil;
	for(i=0;i<=MAX_TREE_SIZE-1;i++)
		if(T[i]==e)
			return T[i*2+1];
	return Nil; 
}

TElemType RightChild(SqBiTree T,TElemType e)
{ 
	int i;
	if(T[0]==Nil) 
		return Nil;
	for(i=0;i<=MAX_TREE_SIZE-1;i++)
		if(T[i]==e) 
			return T[i*2+2];
	return Nil; 
}

TElemType LeftSibling(SqBiTree T,TElemType e)
{ 
	int i;
	if(T[0]==Nil) 
		return Nil;
	for(i=1;i<=MAX_TREE_SIZE-1;i++)
		if(T[i]==e&&i%2==0) 
			return T[i-1];
	return Nil;
}

TElemType RightSibling(SqBiTree T,TElemType e)
{ 
	int i;
	if(T[0]==Nil) 
		return Nil;
	for(i=1;i<=MAX_TREE_SIZE-1;i++)
		if(T[i]==e&&i%2) 
			return T[i+1];
	return Nil;
}

void PreTraverse(SqBiTree T,int e)
{ 
	visit(T[e]);
	if(T[2*e+1]!=Nil) 
		PreTraverse(T,2*e+1);
	if(T[2*e+2]!=Nil) 
		PreTraverse(T,2*e+2);
}


Status PreOrderTraverse(SqBiTree T)
{ 
	if(!BiTreeEmpty(T))
	 PreTraverse(T,0);
	printf("\n");
	return OK;
}

void InTraverse(SqBiTree T,int e)
{ 
	if(T[2*e+1]!=Nil) 
		InTraverse(T,2*e+1);
	visit(T[e]);
	if(T[2*e+2]!=Nil) 
		InTraverse(T,2*e+2);
}

Status InOrderTraverse(SqBiTree T)
{ 
	if(!BiTreeEmpty(T)) 
		InTraverse(T,0);
	printf("\n");
	return OK;
}

void PostTraverse(SqBiTree T,int e)
{ 
	if(T[2*e+1]!=Nil) 
		PostTraverse(T,2*e+1);
	if(T[2*e+2]!=Nil) 
		PostTraverse(T,2*e+2);
	visit(T[e]);
}

Status PostOrderTraverse(SqBiTree T)
{ 
	if(!BiTreeEmpty(T))
		PostTraverse(T,0);
	printf("\n");
	return OK;
}

void LevelOrderTraverse(SqBiTree T)
{ 
	int i=MAX_TREE_SIZE-1,j;
	while(T[i]==Nil)
		i--; 
	for(j=0;j<=i;j++) 
		if(T[j]!=Nil)
			visit(T[j]); 
	printf("\n");
}

void Print(SqBiTree T)
{ 
	int j,k;
	Position p;
	TElemType e;
	for(j=1;j<=BiTreeDepth(T);j++)
	{
		printf("第%d层: ",j);
		for(k=1;k<=powl(2,j-1);k++)
		{
			p.level=j;
			p.order=k;
			e=Value(T,p);
			if(e!=Nil)
				printf("%d:%d ",k,e);
		}
		printf("\n");
	}
}

typedef int Status;		
typedef int TElemmType;  
typedef TElemmType SqBiTree[MAX_TREE_SIZE];

typedef struct
{
	int level,order; 
}Positions;

TElemmType Nill=0; 

Status visits(TElemmType d)
{
	printf("%d ",d);
	return OK;
}

Status InitBiTreTree(SqBiTree S)
{
	int j;
	for(j=0;j<MAX_TREE_SIZE;j++)
		S[j]=Nill; 
	return OK;
}

Status CreateBiTreTree(SqBiTree S)
{ 
	int j=0;
	while(j<10)
	{
		S[j]=j+1;
		
		if(j!=0&&S[(j+1)/2-1]==Nill&&S[j]!=Nill) 
		{
			printf("出现无双亲的非根结点%d\n",S[j]);
			exit(ERROR);
		}
		j++;
	}
	while(j<MAX_TREE_SIZE)
	{
		S[j]=Nill; 
		j++;
	}

	return OK;
}

typedef int Status;	
typedef int TElemmType;
typedef enum {Link,Thread} PointerTag;
typedef  struct BiThrNode
{
	TElemmType data;
	struct BiThrNode *lchild, *rchild;	
	PointerTag LTag;
	PointerTag RTag;	
} BiThrNode, *BiThrTree;

Status CreateBiThrTree(BiThrTree *S)
{ 
	TElemmType h;
	scanf("%c",&h);

	if(h==Nil)
		*S=NULL;
	else
	{
		*S=(BiThrTree)malloc(sizeof(BiThrNode));
		if(!*S)
			exit(OVERFLOW);
		(*S)->data=h; 
		CreateBiThrTree(&(*S)->lchild); 
		if((*S)->lchild) 
			(*S)->LTag=Link;
		CreateBiThrTree(&(*S)->rchild);
		if((*S)->rchild) 
			(*S)->RTag=Link;
	}
	return OK;
}

BiThrTree pre;
void InThreading(BiThrTree p)
{ 
	if(p)
	{
		InThreading(p->lchild);
		if(!p->lchild) 
		{
			p->LTag=Thread; 
			p->lchild=pre;
		}
		if(!pre->rchild)
		{
			pre->RTag=Thread;
			pre->rchild=p; 
		}
		pre=p; 
		InThreading(p->rchild); 
	}
}

Status InOrderThreading(BiThrTree *Thrt,BiThrTree S)
{ 
	*Thrt=(BiThrTree)malloc(sizeof(BiThrNode));
	if(!*Thrt)
		exit(OVERFLOW);
	(*Thrt)->LTag=Link; 
	(*Thrt)->RTag=Thread;
	(*Thrt)->rchild=(*Thrt); 
	if(!S) 
		(*Thrt)->lchild=*Thrt;
	else
	{
		(*Thrt)->lchild=S;
		pre=(*Thrt);
		InThreading(S); 
		pre->rchild=*Thrt;
		pre->RTag=Thread; 
		(*Thrt)->rchild=pre;
	}
	return OK;
}

Status InOrderTraverse_Thr(BiThrTree S)
{ 
	BiThrTree p;
	p=S->lchild; 
	while(p!=S)
	{ 	while(p->LTag==Link)
			p=p->lchild;
		if(!visit(p->data)) 
			return ERROR;
		while(p->RTag==Thread&&p->rchild!=S)
		{
			p=p->rchild;
			visit(p->data);
		}
		p=p->rchild;
	}
	return OK;
}

int main()
{
	Status i;
	Position p;
	TElemType e;
	SqBiTree T;
	InitBiTree(T);
	BiThrTree H,S;
	CreateBiTree(T);
	printf("层序遍历二叉树:\n");
	LevelOrderTraverse(T);
	printf("前序遍历二叉树:\n");
	PreOrderTraverse(T);
	printf("中序遍历二叉树:\n");
	InOrderTraverse(T);
	printf("后序遍历二叉树:\n"); 
	PostOrderTraverse(T); 
	InOrderThreading(&H,S); 
	printf("中序遍历二叉树:\n");
	InOrderTraverse_Thr(H); 
	return 0;
}



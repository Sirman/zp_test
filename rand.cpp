#include<stdlib.h>
#include<time.h>
#include<stdio.h>
#define Max 3
#define Len 20
typedef struct Lnode
{
	int data;
	struct Lnode *next;
}LNode, *LinkList;
typedef struct Dnode			//双向链表
{
	int data;
	struct Dnode *pre,*next;
}Dnode,*DLinkList;


int initLinkList(LinkList *L)
{
	*L=(LinkList)malloc(sizeof(LNode));
	if(*L==NULL)
		return 0;
	(*L)->next=NULL;
	return 1;
}
int insertLinkList(LinkList L,int x,LinkList &Lq)	//应用头插法
{
	LinkList p=L,s;
	s=(LinkList)malloc(sizeof(LNode));
	s->data=x;
	s->next=p->next;
	p->next=s;
	Lq=s;
	return 1;
}
int Compare(LinkList L,int a)
{
	LinkList p=L;
	int m=0;
	for(p;p->next!=NULL;p=p->next)
		if(a==p->next->data)
			m++;
	return m;
}
int ModfiyLinkList(LinkList L,int x,LinkList &Lq)	//插在队尾，得保留一个队尾指针
{
	LinkList p=L->next,q=L,s;
	s=(LinkList)malloc(sizeof(LNode));
	q->next=p->next;	//丢掉紧跟着头指针的第一个指针
	s->data=x;
	s->next=NULL;
	Lq->next=s;	//Lq尾指针
	Lq=s;//Lq接着指向最后一个数据
	free(p);
	return 1;
}
void print(LinkList P)
{
	for(P;P->next!=NULL;P=P->next)
		printf("%d ",P->next->data);
	printf("\n");
}
int Find(int a[],LinkList L,LinkList &Lq)
{
	LinkList q=L;
	int count=0;
	for(int i=Max;i<Len;i++)
		if(Compare(q,a[i])==0)
		{
				ModfiyLinkList(q,a[i],Lq);
				print(q);
				count++;
		}
	return count;
}


int initDLinkList(DLinkList *dL)
{
	*dL=(DLinkList)malloc(sizeof(Dnode));
	if(*dL==NULL)
		return 0;
	(*dL)->pre=(*dL)->next=*dL;
	return 1;
}		//////
int insertDLinkList(DLinkList dL,int x)
{
	DLinkList p=dL,s;
	p=dL;
	s=(DLinkList)malloc(sizeof(Dnode));
	s->data=x;
	s->pre=p;
	s->next=p->next;
	p->next->pre=s;
	p->next=s;
	return 1;
}
int dCompare(DLinkList dL,int a)			//LRU算法之比较页面
{
	DLinkList p=dL;
	int m=0;
	for(p;p->next!=dL;p=p->next)		//陷入死循环
	{
			int b=p->next->data;
			if(a==b)
				m++;
	}
	return m;
}
int ModfiyDLinkList(DLinkList dL,int x)			//在双向链表的头指针后插入新节点，并删除尾部
{
	DLinkList p=dL->pre,q=dL,s;
	s=(DLinkList)malloc(sizeof(Dnode));
	s->data=x;
	s->next=q->next;
	s->pre=q;
	q->next->pre=s;
	q->next=s;
	//q->next=s;
	//s->next->pre=s;
	p->pre->next=q;
	q->pre=p->pre;
	free(p);
	return 1;
}
void Dprint(DLinkList dL)
{
	DLinkList p=dL;
	for(p;p->next!=dL;p=p->next)
		printf("%d ",p->next->data);
	printf("\n");
}
void SortDLinkList(DLinkList dL,int x)
{
	DLinkList p=dL->pre;	//将尾节点位置调整到头节点之后,
	DLinkList p1=p->pre,q1=dL->next;
	if(p1->data==x)
	{
		p1->pre=dL;
		dL->next=p1;
		q1->next=p;
		p->pre=q1;
		p1->next=q1;
		q1->pre=p1;
	}
	if(p->data==x)
	{
		p->pre=dL;
		dL->next=p;
		p1->next=dL;
		dL->pre=p1;
		p->next=q1;
		q1->pre=p;
	}
	/*if(p->data==x)
	{
		dL->pre=p->pre;		//头结点的前驱节点指向尾节点的前驱节点
		p->next=dL->next;	//尾节点的后继节点指向头节点的后继节点
		p->pre=dL;			//尾节点的前驱节点指向头节点
		dL->next->pre=p;		//头结点的后继节点的前驱节点指向尾节点
		p->pre->next=dL;
		q->next=p;			//头节点的后继节点指向尾节点
		Dprint(dL);

	}*/
}
int DFind(int a[],DLinkList dL)
{
	DLinkList q=dL;
	int count=0;
	for(int i=Max;i<Len;i++)
		if(dCompare(q,a[i])==0)
		{
			ModfiyDLinkList(q,a[i]);
				Dprint(q);
				count++;
		}
		else
		{
			SortDLinkList(q,a[i]);
			Dprint(q);
		}
		return count;
}
void random(int page[])
{
    int i,num;
    srand(time(NULL));
    for(i =0; i<20;i++)
	{
        num = rand()%10+1;
		page[i]=num;
	}
	printf("\n");

}
int menu()
{
	printf("请选择编号：1-FIFO 2-LRU\n");
	int i;
	scanf("%d",&i);
	return i;
}


void main()
{
	int page[20];
    random(page);
	LinkList L,Q,P,Lq;
	DLinkList dL,p,q;
	int x,Lack1,Lack2;
	printf("页面访问列表为:");
	for(int i=0;i<20;i++)
		printf("%d ",page[i]);
	printf("\n");
	if(initLinkList(&L))
		printf("FIFO申请成功\n");
	else
	{
		printf("FIFO申请不成功\n");
		exit(0);
	}
	if(initDLinkList(&dL))
		printf("LRU申请成功\n");
	else
	{
		printf("LRU申请不成功\n");
		exit(0);
	}
	Q=L;
	P=L;
	Lq=L;
	p=dL;
	q=dL;
	for(int j=0;j<Max;j++)
	{
		x=page[j];
		insertLinkList(Q,x,Lq);
		insertDLinkList(p,x);
		Q=Q->next;
		p=p->next;
	}
	while(1)
	{
		int n=menu();
		switch(n)
		{
		case 1:
			Lack1=Find(page,L,Lq);
			printf("所缺页数为:\n");
			printf("%d \n",Lack1);
			printf("缺页中断率为百分之%0.2f\n",(Lack1*1.0)/Len*100);
			break;
		case 2:
			Lack2=DFind(page,dL);
			printf("所缺页数为:\n");
			printf("%d \n",Lack2);
			printf("缺页中断率为百分之%0.2f\n",(Lack2*1.0)/Len*100);
			break;
		default :
			printf("Error!\n");
		}
	}
}
/*
printf("页面访问列表为:");
	for(int i=0;i<20;i++)
		printf("%d ",page[i]);
	printf("\n");
	if(initLinkList(&L))
		printf("FIFO申请成功\n");
	else
	{
		printf("FIFO申请不成功\n");
		exit(0);
	}
	if(initDLinkList(&dL))
		printf("LRU申请成功\n");
	else
	{
		printf("LRU申请不成功\n");
		exit(0);
	}
	printf("FIFO内存\n");
	for(P;P->next!=NULL;P=P->next)
	printf("%d ",P->next->data);
	printf("\n");
	printf("LRU内存\n");
	for(q;q->next!=dL;q=q->next)
		printf("%d ",q->next->data);
	printf("\n");
	printf("%d \n",dL->pre->data);
	*/

#include <stdio.h>
#define MAXSIZE 100

typedef struct
{
	int data;
	int cur;
}node;

node LinkList [MAXSIZE];

//备用链表第一个首元节点的下标 
int p = 0;
//链表的一个首元节点的下标，若链表为空则q为-1 
int q = -1;

//将下标为K的空闲节点回收到备用链表
void Free(int k)
{
	LinkList[k].cur = LinkList[p].cur;
	LinkList[p].cur = k;
} 
//初始化 
void Init()
{
	unsigned short i;
	for(i = 0; i < MAXSIZE - 1; i++) LinkList[i].cur = i + 1;
	LinkList[MAXSIZE - 1].cur = -1; 
}
//插入第一个元素，值为i 
void InsertFirstData(int i)
{
	q = p;
    LinkList[q].data = i;
    p = LinkList[p].cur;
    LinkList[q].cur = -1;
}

//返回LinkList中数据元素个数
int ListLength()
{
	int cacu = 0;//记录元素个数 
	int q1 = q;
	if(q1 == -1) return 0;
	while(q1 != -1)
	{
		q1 = LinkList[q1].cur; 
		cacu ++;
	}
	return cacu; 
}

//求前驱元素 cur_e是当前数据值，m返回为其前驱元素下标 
int PriorElem(int cur_e, int m)
{ 
  int j, i = q; //i指示链表第一个结点的位置
  do  //向后移动结点
  { j = i; //j指向i所指元素
    i = LinkList[i].cur; //i指向下一个元素
  }while(i && cur_e!=LinkList[i].data); //i所指元素存在且其值不是cur_e，继续循环
  if(LinkList[i].data == cur_e) //找到该元素
  { 
    m = j;
	return m; //j是i所指元素的前驱元素的下标，赋给m
  }
}

//在第i个元素前插入元素e 
void SLinkInsert(int i, int e){
	if(i < 1||i > ListLength()) return;
    int m = -1;//前驱元素返回的数组下标
	if(i > 1)
	{
        int q1 = q;
		for(int k = 1; k < i; k++)
		{ 
			q1 = LinkList[q1].cur;
			int cur_e = LinkList[q1].data;
			m = PriorElem(cur_e, m);
		} 
		int n = p; //临时指针
		LinkList[p].data = e;
		LinkList[m].cur = p;
		p = LinkList[n].cur;
		LinkList[n].cur = q1;
		return;
	}
    if(i = 1)
    {
    	int k = q; //临时指针
		q = p;
		p = LinkList[p].cur;
		LinkList[q].cur = k;
		LinkList[q].data = e; 
	}
	return;
}
//删除第i个元素 
void SLinkListDelet(int i)
{
	if(i < 1||i > ListLength()) return;
    int m = -1;//前驱元素返回的数组下标
	if(i > 1)
	{
	    int q1 = q;
		for(int k = 1; k < i; k++)
		{
			q1 = LinkList[q1].cur;
			int cur_e = LinkList[q1].data;
			m = PriorElem(cur_e, m);
		}
		LinkList[m].cur = LinkList[q1].cur;
		Free(q1);
		return;
	}
	if(i = 1)
	{
		int k = q;//临时指针
		q = LinkList[q].cur;
		Free(k);
		return; 
	}

}



int main(){
	Init();//初始化 
	InsertFirstData(1);//插入之前需要链表中有至少一个元素 (1)
	SLinkInsert(1, 0);//在第一个元素之前插入0 输出：0 -> 1 
	SLinkInsert(2, 2);//在第二个元素之前插入2 输出：0 -> 2 -> 1 
	SLinkListDelet(2);//删除第二个元素 输出：0 -> 1 
	printf("链表长度为%d\n",ListLength());
	int k = q;//临时指针 
    for(int i = 1; i <= ListLength(); i++){
        printf("第%d个数据是%d\t",i,LinkList[k].data);
        k = LinkList[k].cur;
    }
	return 0;
}


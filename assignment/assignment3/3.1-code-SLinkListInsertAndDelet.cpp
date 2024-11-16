#include <stdio.h>
#define MAXSIZE 100

typedef struct
{
	int data;
	int cur;
}node;

node LinkList [MAXSIZE];

//���������һ����Ԫ�ڵ���±� 
int p = 0;
//�����һ����Ԫ�ڵ���±꣬������Ϊ����qΪ-1 
int q = -1;

//���±�ΪK�Ŀ��нڵ���յ���������
void Free(int k)
{
	LinkList[k].cur = LinkList[p].cur;
	LinkList[p].cur = k;
} 
//��ʼ�� 
void Init()
{
	unsigned short i;
	for(i = 0; i < MAXSIZE - 1; i++) LinkList[i].cur = i + 1;
	LinkList[MAXSIZE - 1].cur = -1; 
}
//�����һ��Ԫ�أ�ֵΪi 
void InsertFirstData(int i)
{
	q = p;
    LinkList[q].data = i;
    p = LinkList[p].cur;
    LinkList[q].cur = -1;
}

//����LinkList������Ԫ�ظ���
int ListLength()
{
	int cacu = 0;//��¼Ԫ�ظ��� 
	int q1 = q;
	if(q1 == -1) return 0;
	while(q1 != -1)
	{
		q1 = LinkList[q1].cur; 
		cacu ++;
	}
	return cacu; 
}

//��ǰ��Ԫ�� cur_e�ǵ�ǰ����ֵ��m����Ϊ��ǰ��Ԫ���±� 
int PriorElem(int cur_e, int m)
{ 
  int j, i = q; //iָʾ�����һ������λ��
  do  //����ƶ����
  { j = i; //jָ��i��ָԪ��
    i = LinkList[i].cur; //iָ����һ��Ԫ��
  }while(i && cur_e!=LinkList[i].data); //i��ָԪ�ش�������ֵ����cur_e������ѭ��
  if(LinkList[i].data == cur_e) //�ҵ���Ԫ��
  { 
    m = j;
	return m; //j��i��ָԪ�ص�ǰ��Ԫ�ص��±꣬����m
  }
}

//�ڵ�i��Ԫ��ǰ����Ԫ��e 
void SLinkInsert(int i, int e){
	if(i < 1||i > ListLength()) return;
    int m = -1;//ǰ��Ԫ�ط��ص������±�
	if(i > 1)
	{
        int q1 = q;
		for(int k = 1; k < i; k++)
		{ 
			q1 = LinkList[q1].cur;
			int cur_e = LinkList[q1].data;
			m = PriorElem(cur_e, m);
		} 
		int n = p; //��ʱָ��
		LinkList[p].data = e;
		LinkList[m].cur = p;
		p = LinkList[n].cur;
		LinkList[n].cur = q1;
		return;
	}
    if(i = 1)
    {
    	int k = q; //��ʱָ��
		q = p;
		p = LinkList[p].cur;
		LinkList[q].cur = k;
		LinkList[q].data = e; 
	}
	return;
}
//ɾ����i��Ԫ�� 
void SLinkListDelet(int i)
{
	if(i < 1||i > ListLength()) return;
    int m = -1;//ǰ��Ԫ�ط��ص������±�
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
		int k = q;//��ʱָ��
		q = LinkList[q].cur;
		Free(k);
		return; 
	}

}



int main(){
	Init();//��ʼ�� 
	InsertFirstData(1);//����֮ǰ��Ҫ������������һ��Ԫ�� (1)
	SLinkInsert(1, 0);//�ڵ�һ��Ԫ��֮ǰ����0 �����0 -> 1 
	SLinkInsert(2, 2);//�ڵڶ���Ԫ��֮ǰ����2 �����0 -> 2 -> 1 
	SLinkListDelet(2);//ɾ���ڶ���Ԫ�� �����0 -> 1 
	printf("������Ϊ%d\n",ListLength());
	int k = q;//��ʱָ�� 
    for(int i = 1; i <= ListLength(); i++){
        printf("��%d��������%d\t",i,LinkList[k].data);
        k = LinkList[k].cur;
    }
	return 0;
}


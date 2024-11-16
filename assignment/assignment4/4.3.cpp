/*
3、算法设计：假设以带头结点的循环链表表示队列，
并且只设一个指针指向队尾元素结点(注意不设头指针) ，
试编写相应的置空队、判队空 、入队和出队等算法。
*/

#include <stdio.h>
#include<stdlib.h>
#define MaxSize 100
struct LNode{
	int data;
	struct LNode* next;
};

typedef struct {
	LNode* rear;
	int length;
}Queue;

//初始化
void InitQueue(Queue &Q){
	LNode* head = (LNode*)malloc(sizeof(LNode));
	head->next = NULL;
	Q.rear = head;
}
//入队
void enQueue(int x, Queue Q) {
	LNode* newNode = (LNode*)malloc(sizeof(LNode));
	if (!newNode) return;
	newNode->data = x;
	newNode->next = Q.rear->next;
	Q.rear = newNode;
}

//出队
void deQueue(Queue Q) {
	LNode* p = Q.rear->next;
	p->next = p->next->next;
	free(p->next);
}

//判断队空
bool IsQueueEmpty(Queue Q) {
	if (Q.rear->next->next = NULL)	return true;
	else return false;
}

//置队空
void SetQueueEmpty(Queue Q) {
	if (IsQueueEmpty(Q)) {
		printf("当前队伍已经为空");
		return;
	}
	LNode* p = Q.rear->next;
	do
	{
		p = p->next;
		if (p = Q.rear) {
			Q.rear = Q.rear->next;
			Q.rear->next = NULL;
		}
		else Q.rear->next->next = p->next;
		free(p);
	} while (Q.rear->next->next != NULL); 
}



int main() {
	
	return 0;
}


/*
可以对该代码进行优化，具体如下：

enQueue函数和deQueue函数中的Queue参数应该改为Queue&，这样才能修改实参，否则只是在函数内部修改了形参。

IsQueueEmpty函数中的判断条件应该是==，而不是=，否则会将Q.rear->next->next的值赋为NULL，导致错误。

SetQueueEmpty函数中的do-while循环应该改为while循环，并将条件改为p->next != Q.rear。

优化后的代码如下：

#include <stdio.h>
#include <stdlib.h>

struct LNode{
    int data;
    struct LNode* next;
};

typedef struct {
    LNode* rear;
    int length;
}Queue;

//初始化
void InitQueue(Queue& Q){
    LNode* head = (LNode*)malloc(sizeof(LNode));
    head->next = NULL;
    Q.rear = head;
}

//入队
void enQueue(int x, Queue& Q) {
    LNode* newNode = (LNode*)malloc(sizeof(LNode));
    if (!newNode) return;
    newNode->data = x;
    newNode->next = Q.rear->next;
    Q.rear->next = newNode;
    Q.rear = newNode;
}

//出队
void deQueue(Queue& Q) {
    LNode* p = Q.rear->next->next;
    Q.rear->next->next = p->next;
    if (p == Q.rear) Q.rear = Q.rear->next;
    free(p);
}

//判断队空
bool IsQueueEmpty(Queue Q) {
    if (Q.rear->next == NULL) return true;
    else return false;
}

//置队空
void SetQueueEmpty(Queue Q) {
    if (IsQueueEmpty(Q)) {
        printf("当前队伍已经为空");
        return;
    }
    LNode* p = Q.rear->next->next;
    while (p != Q.rear) {
        Q.rear->next->next = p->next;
        free(p);
        p = Q.rear->next->next;
    }
    free(p);
    Q.rear->next = NULL;
}

int main() {
    Queue
*/
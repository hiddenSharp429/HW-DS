/*
 * @Author: hiddenSharp429 z404878860@163.com
 * @Date: 2023-06-12 16:10:38
 * @LastEditors: hiddenSharp429 z404878860@163.com
 * @LastEditTime: 2023-06-12 16:55:27
 * @FilePath: \appe:\C OR C++\code\HW15.2.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <stdio.h>
#include <stdlib.h>

// 链表节点结构
struct Node
{
    int data;          // 数据
    struct Node *prev; // 前驱
    struct Node *next; // 后继
};

// 创建新节点
struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode; // 返回新节点
}

// 在链表末尾添加节点
void appendNode(struct Node **head, int data) // 传入指针的指针
{
    struct Node *newNode = createNode(data); // 创建新节点
    if (*head == NULL)
    {
        *head = newNode; // 如果链表为空, 则新节点为头节点
        return;
    }
    struct Node *temp = *head; // 临时指针指向头节点
    while (temp->next != NULL)
    {
        temp = temp->next; // 遍历链表, 直到最后一个节点
    }
    temp->next = newNode; // 最后一个节点的后继指向新节点
    newNode->prev = temp; // 新节点的前驱指向最后一个节点
}

// 交换节点数据
void swapData(struct Node *a, struct Node *b) // 传入的参数a和b是指针
{
    int temp = a->data; // 交换a和b的数据
    a->data = b->data;
    b->data = temp;
}

// 双向冒泡排序
void bilateralBubbleSort(struct Node *head)
{
    int swapped; // 标记是否发生交换
    struct Node *start = head;
    struct Node *end = NULL;

    // 检查链表是否为空
    if (head == NULL)
        return;

    do
    {
        swapped = 0;
        struct Node *current = start; // 从头开始冒泡

        // 从左往右冒泡，将较大的节点冒泡到右侧或者最后一个节点
        while (current->next != end)
        {
            if (current->data > current->next->data)// 如果当前节点的数据大于下一个节点的数据则交换
            {
                swapData(current, current->next);
                swapped = 1;
            }
            current = current->next;// 指针后移
        }
        end = current; // 将最后一个节点赋值给end

        if (!swapped)// 如果没有发生交换则说明已经排好序了，则退出循环
            break;

        swapped = 0; // 前面有交换的话swapped为1，这里需要重置swapped
        current = end; // 从最后一个节点开始冒泡

        // 从右往左冒泡，将较小的节点冒泡到左侧
        while (current->prev != start)
        {
            if (current->data < current->prev->data)
            {
                swapData(current, current->prev);
                swapped = 1;
            }
            current = current->prev;
        }
        start = current;// 将第一个节点赋值给start
        // 重复以上步骤，直到没有发生交换
    } while (swapped);
}

// 打印链表
void printList(struct Node *head)
{
    struct Node *temp = head;
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// 主函数
int main()
{
    struct Node *head = NULL;
    int n, data;

    printf("输入链表中记录的个数: ");
    scanf("%d", &n);

    printf("输入链表中的记录: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &data);
        appendNode(&head, data);
    }

    printf("排序前的链表: ");
    printList(head);

    bilateralBubbleSort(head);

    printf("排序后的链表: ");
    printList(head);

    return 0;
}

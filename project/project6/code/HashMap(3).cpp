/*
 * @Author: hiddenSharp429 z404878860@163.com
 * @Date: 2023-06-14 17:28:46
 * @LastEditors: hiddenSharp429 z404878860@163.com
 * @LastEditTime: 2023-06-14 17:46:28
 * @FilePath: \appe:\C OR C++\code\HashMap(3).cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HashTABLE_SIZE 61  // 哈希表的大小，选择一个较大的素数
#define MAX_NAME_LENGTH 20 // 人名的最大长度
#define NOT_FOUND -1       // 未找到的标志

typedef struct PersonNode
{
    char name[MAX_NAME_LENGTH]; // 人名
    struct PersonNode *next;    // 指向下一个节点的指针
} PersonNode;

typedef struct
{
    PersonNode **data; // 哈希表的数据
    int size;          // 哈希表的大小
} HashTable;

// 哈希函数：自定义哈希函数
int hashFunction(char *name, int size)
{
    int hash = 0;
    int nameLength = strlen(name);

    for (int i = 0; i < nameLength; i++)
    {
        hash = (hash * 31 + name[i]) % size;
    }

    return hash;
}

// 初始化哈希表
void initHashTable(HashTable *table, int size)
{
    table->data = (PersonNode **)malloc(sizeof(PersonNode *) * size); // 为哈希表分配空间
    table->size = size;                                               // 设置哈希表的大小
    for (int i = 0; i < size; i++)
    {
        table->data[i] = NULL; // 初始化每个槽位为空
    }
}

// 插入人名到哈希表中
void insertName(HashTable *table, char *name)
{
    int index = hashFunction(name, table->size); // 计算人名在哈希表中的位置

    // 创建新节点
    PersonNode *newNode = (PersonNode *)malloc(sizeof(PersonNode));
    strcpy(newNode->name, name);
    newNode->next = NULL;

    if (table->data[index] == NULL)
    {
        // 槽位为空，直接插入新节点
        table->data[index] = newNode;
    }
    else
    {
        // 槽位非空，遍历链表找到尾节点并插入新节点
        PersonNode *currentNode = table->data[index];
        while (currentNode->next != NULL)
        {
            currentNode = currentNode->next;
        }
        currentNode->next = newNode;
    }

    printf("Inserted %s\n", name);
}

// 查找人名在哈希表中的位置
int findName(HashTable *table, char *name)
{
    int index = hashFunction(name, table->size); // 计算人名在哈希表中的位置

    // 遍历链表查找人名
    PersonNode *currentNode = table->data[index];
    while (currentNode != NULL)
    {
        if (strcmp(currentNode->name, name) == 0)
        {
            return index; // 找到了人名，返回索引位置
        }
        currentNode = currentNode->next;
    }

    return NOT_FOUND; // 未找到人名
}

int main()
{
    HashTable table;
    initHashTable(&table, HashTABLE_SIZE);

    // 待填入哈希表的人名
    char names[30][MAX_NAME_LENGTH] = {
        "chencaiyi", "chenxinxin", "fangsongjie", "huangjiawei", "huangjunlin", "leiyang",
        "luwei", "wangzhanqi", "wuweidong", "longjiajing", "huangweiqin", "chenshangming", "huangtao",
        "maixupeng", "chenying", "liujunhui", "chenqingdong", "guoziming", "chenyilong", "libaiyang", "liangdeguang",
        "zhangyuxing", "huangyibin", "liuwenlong", "zengzihao", "wangshulian", "zhuzixian", "lidingkun", "caofu", "yuemingju"};

    // 建立哈希表
    for (int i = 0; i < 30; i++)
    {
        insertName(&table, names[i]);
    }

    // 查找程序
    char searchName[MAX_NAME_LENGTH];
    printf("Enter a name to search: ");
    scanf("%s", searchName);

    int index = findName(&table, searchName);
    if (index != NOT_FOUND)
    {
        printf("Found at index %d\n", index);
    }
    else
    {
        printf("Not found\n");
    }

    return 0;
}
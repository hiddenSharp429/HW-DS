/*
 * @Author: hiddenSharp429 z404878860@163.com
 * @Date: 2023-06-13 16:38:25
 * @LastEditors: hiddenSharp429 z404878860@163.com
 * @LastEditTime: 2023-06-14 17:28:58
 * @FilePath: \appe:\C OR C++\code\HashMap.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HashTABLE_SIZE 61  // 哈希表的大小，选择一个较大的素数
#define MAX_NAME_LENGTH 20 // 人名的最大长度
#define NOT_FOUND -1       // 未找到的标志

typedef struct
{
    char name[MAX_NAME_LENGTH]; // 人名
} Person;

typedef struct
{
    Person *data; // 哈希表的数据
    int *flags;   // 标记哈希表中的位置是否为空
    int size;     // 哈希表的大小
} HashTable;

// 哈希函数：除留余数法
int hashFunction(char *name, int size)
{
    int sum = 0;
    for (int i = 0; i < strlen(name); i++)
    {
        sum += name[i]; // 将人名中每个字符的ASCII码相加
    }
    return sum % size;
}

// 初始化哈希表
void initHashTable(HashTable *table, int size)
{
    table->data = (Person *)malloc(sizeof(Person) * size); // 为哈希表分配空间
    table->flags = (int *)malloc(sizeof(int) * size);      // 为标记数组分配空间
    table->size = size;                                    // 设置哈希表的大小
    for (int i = 0; i < size; i++)
    {
        strcpy(table->data[i].name, ""); // 初始化人名为空
        table->flags[i] = 0;             // 初始化标记数组为0
    }
}
// 插入人名到哈希表中
void insertName(HashTable *table, char *name)
{
    int index = hashFunction(name, table->size); // 计算人名在哈希表中的位置
    int i = 0;
    int conflicts = 0;               // 记录发生冲突的次数
    while (table->flags[index] == 1) // 人名发生冲突
    {
        // 发生冲突时，使用伪随机探测再散列法处理
        i++;
        index = (index + i * i) % table->size;
        conflicts++;
    }
    strcpy(table->data[index].name, name); // 将人名填入哈希表中
    table->flags[index] = 1;               // 标记数组中的位置为1，表示该位置已经有人名

    printf("Inserted %s with %d conflicts.\n", name, conflicts);
}

// 查找人名在哈希表中的位置
int findName(HashTable *table, char *name)
{
    int index = hashFunction(name, table->size); // 计算人名在哈希表中的位置
    int i = 0;
    while (table->flags[index] != 0) // 人名发生冲突
    {
        if (strcmp(table->data[index].name, name) == 0) // 比较人名是否相同
        {
            return index; // 找到了人名，返回索引位置
        }
        i++;
        index = (index + i * i) % table->size; // 发生冲突时，使用伪随机探测再散列法处理
    }
    return NOT_FOUND; // 未找到人名
}

int main()
{
    HashTable table;
    initHashTable(&table, HashTABLE_SIZE); // 初始化哈希表

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
    printf("Enter a name to search: "); // 输入要查找的人名
    scanf("%s", searchName);            // 读取人名

    int index = findName(&table, searchName); // 查找人名在哈希表中的位置
    if (index != NOT_FOUND)                   // 找到了人名
    {
        printf("Found at index %d\n", index);
    }
    else // 未找到人名
    {
        printf("Not found\n");
    }

    return 0;
}




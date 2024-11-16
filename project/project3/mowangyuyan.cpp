#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define MAX_SIZE 100

// 定义一个结构体，用来表示栈中的节点
struct node
{
    char val;
    node *next;
};

// 定义一个栈类
class Stack
{
private:
    // 栈顶指针
    node *top_ptr = nullptr;

public:
    // 判断栈是否为空
    bool isEmpty()
    {
        return top_ptr == nullptr ? true : false;
    }
    // 获取栈顶元素
    char top()
    {
        return top_ptr->val;
    }
    // 入栈操作
    void push(char c)
    {
        node *new_node = new node{c, top_ptr};
        top_ptr = new_node;
    }
    // 弹出栈顶元素
    bool pop()
    {
        if (isEmpty())
            return false;
        node *to_be_deleted = top_ptr;
        top_ptr = top_ptr->next;
        delete to_be_deleted;
        return true;
    }
    // 置空栈
    void clear()
    {
        while (top_ptr)
        {
            node *tmp = top_ptr;
            top_ptr = top_ptr->next;
            delete tmp;
        }
    }
    // 析构函数
    ~Stack()
    {
        clear();
    }
};
// 将字符串逆置
void reverseStr(char str[], int length)
{
    int start = 0;
    int end = length - 1;
    while (start < end)
    {
        swap(str[start], str[end]);
        start++;
        end--;
    }
}
// 将一条语句倒着放入栈中
void invert(Stack &sta, char setence[])
{
    // 一句话的长度
    int len = strlen(setence) / sizeof(char);
    for (int i = len - 1; i >= 0; --i)
    {
        sta.push(setence[i]);
    }
}
// 将一句话正着放入栈中
void reverseInvert(Stack &sta, char setence[])
{
    // 一句话的长度
    int len = strlen(setence) / sizeof(char);
    for (int i = 0; i <= len - 1; ++i)
    {
        sta.push(setence[i]);
    }
}

// 检查输入的字符是否全为小写字符 ch为输入的字符，index为其字符的ASCII码 - A的ASCII的值, text为预处理后的各大写字母的表示
void inputAndCheck(Stack &sta, char ch, int index, char test[26][MAX_SIZE])
{
    char supperVoca[MAX_SIZE]; // 存放用户输入该大写字母的表示
    int vocaVal;               // 输入解释字符的ASCII码
    char final[MAX_SIZE];      // 最终的解释
    printf("请输入%c字符的解释", ch);
    scanf("%s", supperVoca);
    for (int i = 0; i < strlen(supperVoca) / sizeof(char); i++) // 挨个检查输入的解释是否为小写字母
    {
        vocaVal = supperVoca[i];
        if (isupper(vocaVal) && test[vocaVal - 'A'][0] == '\0') // 如果输入的是大写字母且该大写字母并无解释
        {
            if (vocaVal - 'A' != index) // 检查是否为已经处理过的字母，避免死循环
            {
                Stack newSta;                                              // 创建一个空栈(易漏)
                inputAndCheck(newSta, supperVoca[i], vocaVal - 'A', test); // 递归
            }
        }
        if (isupper(vocaVal) && test[vocaVal - 'A'][0] != '\0') // 如果输入的是大写字母且该大写字母有相应的解释
        {
            reverseInvert(sta, test[vocaVal - 'A']); // 将该大写字母的解释正着插入栈中
        }
        else
            sta.push(supperVoca[i]); // 如果是小写字母则直接插入栈中
    }
    int i = 0; // 共有多少个字符
    while (!sta.isEmpty())
    {
        char tmp = sta.top();
        sta.pop();
        final[i] = tmp;
        i++;
    }
    reverseStr(final, i);
    int j = 0;
    while (j < i)
    {
        test[index][j] = final[j];
        j++;
    }
    test[index][j] = '\0'; // 在每个大写字母的最终解释后加个\0
}
int main()
{
    // test
    char test[26][MAX_SIZE];        // 存放26个大写英文字母的所对应的小写字母解释
    char language[MAX_SIZE];        // 一开始的魔王语言
    char inBrackets[MAX_SIZE];      // 括号内的字符
    char translatedInBra[MAX_SIZE]; // 转化括号内的字符
    char translation[MAX_SIZE];     // 最终解释的字符
    bool flag = false;              // 是否在括号内的标志
    Stack translatedLanguage;       // 经过大小写转换后的栈
    Stack finalInterp;              // 每个大写字母最终解释的栈
    for (int i = 0; i < 26; ++i)    // 初始化
    {
        test[i][0] = '\0';
    }
    scanf("%s", language);                            // 输入魔王语言
    int langLength = strlen(language) / sizeof(char); // 求出输入字符的长度
    for (int i = 0; i < langLength; i++)
    {
        int Char = language[i]; // 字符的ASCII码值
        if (isupper(Char))
        {
            if (test[Char - 'A'][0] == '\0')
            {
                // 输入并检查是否含有大写字幕
                inputAndCheck(finalInterp, language[i], Char - 'A', test);
            }
        }
    }
    reverseInvert(translatedLanguage, language);
    int i = 0;
    int j = 0;
    while (!translatedLanguage.isEmpty())
    {
        char tmp = translatedLanguage.top();
        translatedLanguage.pop();
        if (isupper(tmp))
        {
            reverseInvert(translatedLanguage, test[tmp - 'A']);
        }
        else if (tmp == ')')
        {
            flag = true;
        }
        else if (tmp == '(')
        {
            flag = false;
            int inBracketsLength = strlen(inBrackets) / sizeof(char);
            int counter1 = 0;
            int counter2 = 0;
            while (counter1 != inBracketsLength)
            {
                translatedInBra[counter2] = inBrackets[inBracketsLength - 1];
                if (counter1 != (inBracketsLength - 1))
                {
                    translatedInBra[counter2 + 1] = inBrackets[counter1];
                }
                counter1 = counter1 + 1;
                counter2 = counter2 + 2;
            }
            reverseInvert(translatedLanguage, translatedInBra);
        }
        else
        {
            if (flag)
            {
                inBrackets[i] = tmp;
                i = i + 1;
            }
            if (!flag)
            {
                translation[j] = tmp;
                j++;
            }
        }
    }
    reverseStr(translation, j);
    for (int k = 0; k < j; k++)
    {
        printf("%c", translation[k]);
    }
    return 0;
}
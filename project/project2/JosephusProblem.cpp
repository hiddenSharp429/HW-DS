/*问题描述
约瑟夫问题的一种描述是：编号为1,2,...,n的n个人按顺时针方向围坐一圈，每人持有一个密码(正整数)。一开始任选一个正整数作为报数上限值m，从第一个人开始。按顺时针方向自1开始顺序报数，报到m时停止报数。报m的人出列，将他的密码作为新的m值，从他在顺时针方向上的下一个人开始重新从1报数，如此下去，直至所有人全部出列为止。试设计程序求出出列顺序。
基本要求
利用单向循环链表存储结构模拟此过程，按照出列的顺序印出个人的编号。
测试数据
m的初值为20;n=7,7个人的密码: 3,1,7,2,4,8,4。(正确的结果应为6,1,4,7,2,3,5) 
(报告上要求写出多批数据测试结果
实现提示
程序运行后首先要求用户指定初始报数上限值与人数，然后读取各人的密码*/

#include <iostream>
#include <vector>
using namespace std;

//人类
class Person {
public:
    //密码
    int code;
    //编号
    int No;
    //下一个人的指针
    Person *next = nullptr;
    //构造函数
    Person(int c, int N):code(c), No(N) {
        
    }
};

int main() {
    //下一次要走的步数
    int step;
    //有多少个人
    int num;
    cout << "请输入报数上限值" ;
    cin >> step;
    cout << "请输入总共有多少个人";
    cin >> num;

    //head存循环单链表的头，即编号为1的人的位置；tmp为临时变量，但最后它将存放最后一个人的位置
    Person *head, *tmp;
    //构造循环单链表，这是一个没有头节点的循环单链表
    for(int i = 0; i < num; ++i) {
        int code;
        //读取密码
        printf("请输入第%d个人的密码",i + 1); 
        cin >> code;
        if(i == 0) {
            //head,即第一个人的位置
            head = new Person(code, i + 1);
            tmp = head;
        }else {
            tmp->next = new Person(code, i + 1);
            //更新
            tmp = tmp->next;
        }
    }
    //将尾衔接到头上
    tmp->next = head;

    //start每一次报数开始的位置，随着每个人报数一步步移动
    Person *start = head;
    //前驱指针
    Person *pre = tmp;
    //存放最终结果的序号列表
    vector<int> NoList;
    for(int i = 0; i < num; ++i) {//num次循环，即num次报数
        for(int j = 0; j < step - 1; ++j) {
            //前驱结点更新
            pre = start;
            //随着报数进行，一步步指向下一个人
            start = start->next;
        }//循环结束，指到的人便出列
        //读取密码
        step = start->code;
        //存入序号
        NoList.push_back(start->No);
        //记录一下下一个结点的位置，方便删除此结点，即指到的人出列
        Person *newStart = start->next;
        //删除结点
        pre->next = start->next;
        //释放空间
        delete start;
        //更新
        start = newStart;
    }
    //输出结果
    for(auto i : NoList) {
        cout << i << ' ';
    }
    return 0;
}

#pragma once
#include "sporter.h"
#include <vector>

//管理类
class SportsManager{
public:
    //构造函数
    SportsManager();

    //操作页面菜单
    void showMenu();

    //退出程序
    void quit();

    //查看比赛项目信息
    void checkEventInfo();

    //运动员报名登记
    void registerSporter();

    //删除运动员报名信息
    void deleteSporter();

    //查找运动员报名信息
    int findSporter();

    //修改运动员报名信息
    void modifySporter();

    //查看运动员报名信息
    void checkRegistrationInfo();

    //查看秩序册
    void checkProgram();

    //比赛成绩录入
    void inputGrade();

    //比赛成绩查询
    void checkGrade();
    
    //查看各学院的得分
    void checkCollegeGrade();

    //析构函数
    ~SportsManager();
    
private:
    //运动员报名信息数量
    int sporterNum;
    //开辟堆保存运动员信息
    Sporter **registerForm;
    //判断运动员信息表是否为空的标志
    bool isEmpty;
    //运动会项目时间安排表
    vector<Event> eventForm;

    //载入项目计划表
    void loadSchedule();

    //查询可以报名的项目
    bool findAbledEvent(string, string);

    //查找项目的索引
    int findEvent();

    //计算排名和得分
    vector<Sporter *> caculateRankAndScore(int);

    //获取已存的运动员报名表中的运动员数量
    int getSporterNum();

    //将已存的运动员报名表读入内存中
    void loadSporterForm();



    //将内存中的运动员数据保存到硬盘中
    void saveSporterForm();
};

bool cmp1(Sporter *, Sporter *);

bool cmp2(Sporter *, Sporter *);
#pragma once
#include <string>
#include <vector>
#include "event.h"
using namespace std;

class Sporter{
    public:
        //运动员所在学院
        string m_college;
        //运动员姓名
        string m_name;
        //运动员的性别
        string m_gender;
        //运动员报名的项目的索引
        int m_registeredEventNum;
        //运动员该项目的成绩
        string m_grade = "无";

        int m_rank = -1;
        int m_score = -1;

        //构造函数
        //有成绩时的构造函数
        Sporter(string college, string name, string gender, int registeredEventNum, string grade, int rank, int score):m_college(college), m_name(name), m_gender(gender), m_registeredEventNum(registeredEventNum), m_grade(grade), m_rank(rank), m_score(score) {
            
        }
        //无成绩时的构造函数
        Sporter(string college, string name, string gender, int registeredEventNum):m_college(college), m_name(name), m_gender(gender), m_registeredEventNum(registeredEventNum) {
            
        }

};
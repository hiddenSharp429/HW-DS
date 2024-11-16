#pragma once
#include <string>
using namespace std;

//运动会项目类
class Event {
public:
    //名称
    string m_name;
    //性别限制
    string m_gender;
    //比赛时间
    string m_time;
    //比赛场地
    string m_venue;
    //该项目成绩已录入的标志
    bool hasInputGrade = false;

    //排序方法标志
    char m_sortMark;

    //项目的构造函数
    Event(string name, string gender, string venue, string time, char sortMark):m_name(name), m_gender(gender), m_venue(venue), m_time(time), m_sortMark(sortMark){

    }
};
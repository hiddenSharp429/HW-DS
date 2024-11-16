#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <algorithm>
#include "event.h"
#include "sprotsManager.h"
using namespace std;


SportsManager::SportsManager() {
    //载入项目安排表
    loadSchedule();
    ifstream iftr;
    iftr.open("sporterForm.txt", ios::in);

    //第一种情况：文件不存在，即没有运动员名单
    if(!iftr.is_open()){
        //运动员人数为0
        sporterNum = 0;
        registerForm = nullptr;
        isEmpty = true;
        iftr.close();
        return;
    }

    //第二种情况：文件存在但为空，既没有运动员报名
    char tmp;
    iftr >> tmp;
    if(!iftr.is_open()){
        //运动员人数为0
        sporterNum = 0;
        registerForm = nullptr;
        isEmpty = true;
        iftr.close();
        return;
    }

    //第三种情况：文件存在且不为空，即已经有人报名了
    isEmpty = false;
    sporterNum = getSporterNum();
    registerForm = new Sporter* [sporterNum];
    loadSporterForm();
}

void SportsManager::showMenu() {
    cout << "---------------------------" << endl;
    cout << "请选择您需要办理的业务：" << endl;
    cout << "0 退出系统" << endl;
    cout << "1 查询比赛项目信息" << endl;
    cout << "2 运动员报名登记" << endl;
    cout << "3 删除运动员报名信息" << endl;
    cout << "4 查找运动员报名信息" << endl;
    cout << "5 修改运动员报名信息" << endl;
    cout << "6 参赛信息查询" << endl;
    cout << "7 查看秩序册" << endl;
    cout << "8 比赛成绩录入" << endl;
    cout << "9 比赛成绩查询" << endl;
    cout << "10 各学院得分统计" << endl;
}

void SportsManager::quit() {
    cout << "感谢您的使用和支持！" << endl;
    exit(0);
}

void SportsManager::checkEventInfo() {
    cout << setw(20) << left << "项目" << setw(20) << left << "男/女" << setw(20) << left << "地点" << setw(20) << left << "时间" << endl;
    for(auto i : eventForm) {
        cout << setw(20) << left << i.m_name << setw(20) << left << i.m_gender << setw(20) << left << i.m_venue << "第" << i.m_time.substr(0, 2) <<"天 " << i.m_time.substr(2, 12) << endl;
    }
    system("pause");
}

void SportsManager::registerSporter() {
    string college, sporterName, gender;
    cout << "请输入运动员所在学院：";
    cin >> college;
    cout << "请输入运动员的名字：";
    cin >> sporterName;
    cout << "请输入运动员的性别（男/女）：";
    cin >> gender;
    //找寻可报名的项目
    if(!findAbledEvent(sporterName, gender))
        //无适合的项目，故停止报名
        return;

    //项目编号
    int eventNum;
    cout << "请输入您要报名的项目的编号：";
    cin >> eventNum;
    
    Sporter *newSporter = new Sporter(college, sporterName, gender, eventNum);

    //开辟新空间
    Sporter **newRegister = new Sporter*[sporterNum + 1];
    //将原空间的运动员报名信息拷贝至新空间
    for(int i = 0; i < sporterNum; ++i){
        newRegister[i] = new Sporter(registerForm[i]->m_college, registerForm[i]->m_name, registerForm[i]->m_gender, registerForm[i]->m_registeredEventNum);
    }
    //更新新的运动员报名信息
    newRegister[sporterNum] = newSporter;
    //释放原有空间
    if(registerForm != nullptr){
        for(int i = 0; i < sporterNum; i++){
            delete registerForm[i];
            registerForm[i] = nullptr;
        }
    }
    delete []registerForm;
    //更新新的空间地址
    registerForm = newRegister;
    //更新运动员数量
    ++sporterNum;
    //文件为空标志赋false
    isEmpty = false;
    saveSporterForm();
    cout << "报名成功！" << endl;
    system("pause");
}

void SportsManager::deleteSporter() {
    int index = findSporter();
    if(index != -1){
        if(eventForm[registerForm[index]->m_registeredEventNum].hasInputGrade) {
            cout << "删除失败，该比赛已结束，如有疑问请联系管理员：186xxxx2222" << endl;
            system("pause");
            return;
        }
        for(int i = index; i < sporterNum; ++i){
            registerForm[i] = registerForm[i+1];
        }
        --sporterNum;
    }
    saveSporterForm();
    cout << "删除成功！" << endl;
    system("pause");
    return;
}

int SportsManager::findSporter() {
    if(isEmpty){
        cout << "运动员报名信息表为空" << endl;
        system("pause");
        return -1;
    }
    string sporterName, eventName;
    cout << "请输入运动员的姓名：";
    cin >> sporterName;
    cout << "请输入运动员所报名的项目名字：";
    cin >> eventName;

    for(int i = 0; i < sporterNum; ++i){
        if(registerForm[i]->m_name == sporterName && eventForm[registerForm[i]->m_registeredEventNum].m_name == eventName){
            cout << setw(20) << left << "学院" << setw(20) << left << "运动员姓名" << setw(20) << left << "男/女" << setw(20) << left << "参赛项目" << setw(20) << left << "地点" << setw(20) << left << "时间" << endl;
            cout << setw(20) << left << registerForm[i]->m_college << setw(20) << left << registerForm[i]->m_name << setw(20) << left << registerForm[i]->m_gender << setw(20) << left << eventForm[registerForm[i]->m_registeredEventNum].m_name << setw(20) << left << eventForm[registerForm[i]->m_registeredEventNum].m_venue << "第" << eventForm[registerForm[i]->m_registeredEventNum].m_time.substr(0, 2) <<"天 " << eventForm[registerForm[i]->m_registeredEventNum].m_time.substr(2, 12) << endl;
            cout << "确认吗？";
            getchar();
            getchar();
            return i; 
        }
    }
    cout << "未找到此报名信息" << endl;
    system("pause");
    return -1;
}

void SportsManager::modifySporter() {
    int index = findSporter();
    if(index != -1){
        if(eventForm[registerForm[index]->m_registeredEventNum].hasInputGrade) {
            cout << "修改失败，该比赛已结束，如有疑问请联系管理员：186xxxx2222" << endl;
            system("pause");
            return;
        }
        string college, sporterName, gender;
        int eventNum;
        cout << "请输入新的学院：";
        cin >> college;
        cout << "请输入新的姓名：";
        cin >> sporterName;
        cout << "请输入新的性别：";
        cin >> gender;

        //寻找可报名的项目
        findAbledEvent(sporterName, gender);
        cout << "请输入您要报名的新的运动项目编号：" << endl;
        cin >> eventNum;
        registerForm[index]->m_college = college;
        registerForm[index]->m_name = sporterName;
        registerForm[index]->m_gender = gender;
        registerForm[index]->m_registeredEventNum = eventNum;
        saveSporterForm();
        cout << "修改成功！" << endl;
        system("pause");
        return;
    }
}

void SportsManager::checkRegistrationInfo() {
    int num = findEvent();
    //未找到
    if(num == -1) 
        return;
    //找到
    cout << eventForm[num].m_name << '(' << eventForm[num].m_gender << ')' << " 时间：" <<  "第" << eventForm[num].m_time.substr(0, 2) <<"天" << eventForm[num].m_time.substr(2, 12) << " 地点：" << eventForm[num].m_venue << endl;
    int cnt = 0;
    for(int i = 0; i < sporterNum; ++i) {
        if(registerForm[i]->m_registeredEventNum == num) {
            cout << registerForm[i]->m_college << ' ' << registerForm[i]->m_name << ' ' << registerForm[i]->m_gender << endl;
            ++cnt;
        }
    }
    cout << "报名此项目的人总计：" << cnt << "（人）" << endl;
    system("pause");
    return ;
}

void SportsManager::checkProgram() {
    ifstream iftr;
    iftr.open("program.txt", ios::in);
    if (iftr.is_open()) { // 或者if (in_file)
        cout << "Open File Successfully" << endl;
        string line;
        while (getline(iftr, line)) {
            cout << line << endl;
        }
    }
    else {
        cout << "Cannot Open File: " << "program.txt" << endl;
    }
    iftr.close();
    //创建一个string类型的数组用来存放所有报名运动员的名字（有重复的）
    vector<string>SporterName;
    for (int i = 0; i < sporterNum; ++i) {
        //存入vector
        SporterName.push_back(registerForm[i]->m_name);
    }
    //进行数组去重
    sort(SporterName.begin(), SporterName.end());
    SporterName.erase(unique(SporterName.begin(), SporterName.end()), SporterName.end());
    cout << endl;
    //输出去重后的数组
    cout << "报名的运动员如下：" << endl;
    for (int i = 0; i < SporterName.size(); i++)
    {
        if(i < SporterName.size()-1){
            cout << SporterName[i] << ",";
        }
        else{
            cout << SporterName[i];
        }
    }
    cout << endl;
    system("pause");
}

void SportsManager::inputGrade() {
    int num = findEvent();
    if(num == -1)
        return;
    //判断项目成绩录入标志是否为真
    if(eventForm[num].hasInputGrade) {
        cout << "该项目已录入成绩" << endl;
        system("pause");
        return;
    }
    //用来判断是否真的有录入成绩（即至少有一个人参加此项目）
    bool  isExit = false;
    cout << eventForm[num].m_name << '(' << eventForm[num].m_gender << ')' << " 时间：" <<  "第" << eventForm[num].m_time.substr(0, 2) <<"天" << eventForm[num].m_time.substr(2, 12) << " 地点：" << eventForm[num].m_venue << endl;
    for(int i = 0; i < sporterNum; ++i) {
        if(registerForm[i]->m_registeredEventNum == num) {
            if(!isExit) {
                isExit = true;
            }
            cout << "请输入" << registerForm[i]->m_name << "的成绩（xxx.xxx）：";
            cin >> registerForm[i]->m_grade; 
        }
    }
    if(!isExit) {
        cout << "无人参加此项目！" << endl;
    }else {
        //更新项目已录入成绩的标志
        eventForm[num].hasInputGrade = true;
        caculateRankAndScore(num);
        //保存成绩
        saveSporterForm();
        cout << "该项目成绩录入完毕！" << endl;
    }
   
    system("pause");
}

vector<Sporter*> SportsManager::caculateRankAndScore(int num) {
    //创建一个数组用来存放排好序后的运动员信息
    vector<Sporter*> gradeRank;
    for (int i = 0; i < sporterNum; ++i) {
        if (registerForm[i]->m_registeredEventNum == num) {
            gradeRank.push_back(registerForm[i]);
        }
    }
    //使用sort方法来排序（升序或降序）
    if (eventForm[num].m_sortMark == '>')
        sort(gradeRank.begin(), gradeRank.end(), cmp1);
    else
        sort(gradeRank.begin(), gradeRank.end(), cmp2);

    for (int i = 0; i < gradeRank.size(); i++) {
        //将排好序了的数组的每一个元素与运动员报名表一一匹配
        for (int j = 0; j < sporterNum; ++j)
        {
            //如果报名表内的项目以及姓名匹配的上
            if ((registerForm[j]->m_registeredEventNum == num) && (registerForm[j]->m_name == gradeRank[i]->m_name)) {
                //给与其排名以及得分
                registerForm[j]->m_rank = i + 1;
                if (i + 1 > 3) {
                    registerForm[j]->m_score = 0;
                }
                else {
                    registerForm[j]->m_score = 4 - i - 1;
                }
            }
        }
    }
    //保存数据
    saveSporterForm();
    return gradeRank;
}

void SportsManager::checkGrade() {
    int num = findEvent();
    if(num == -1)
        return;
    //判断项目成绩录入标志是否为假
    if(!eventForm[num].hasInputGrade) {
        cout << "该项目尚未录入成绩" << endl;
        system("pause");
        return;
    }
    vector<Sporter*> gradeRank(caculateRankAndScore(num));
    // 成绩录入标志为真
    if (eventForm[num].hasInputGrade) {
        cout << eventForm[num].m_name << '(' << eventForm[num].m_gender << ')' << " 时间：" << eventForm[num].m_time << " 地点：" << eventForm[num].m_venue << endl;
  
        for (int i = 0; i < gradeRank.size(); i++) {
            if(i < 3)
                cout << "第" << i + 1 << "名 " << gradeRank[i]->m_college << ' ' << gradeRank[i]->m_name << ' ' << gradeRank[i]->m_grade << "得分:" << 3 - i << endl;
            else
                cout << "第" << i + 1 << "名 " << gradeRank[i]->m_college << ' ' << gradeRank[i]->m_name << ' ' << gradeRank[i]->m_grade << "得分:" << 0 << endl;
        }
        cout << "以上" << endl;
        system("pause");
        return;
    }
}


void SportsManager::loadSchedule() {
    ifstream iftr;
    iftr.open("schedule.txt", ios::in);
    string name, gender, time, venue;
    char sortMark;
    //读取硬盘中的项目安排表
    while(iftr >> name >> gender >> venue >> time >> sortMark) {
        Event event(name, gender, venue, time, sortMark);
        eventForm.push_back(event);
    }
    iftr.close();
}

bool SportsManager::findAbledEvent(string sporterName, string gender) {
    //已报名的项目
    vector<int> registeredEventNumList;
    for(int i = 0; i < sporterNum; ++i) {
        if(registerForm[i]->m_name == sporterName) {
            registeredEventNumList.push_back(registerForm[i]->m_registeredEventNum);
        }
    }

    //可报名的项目列表
    vector<int> abledEventNumList;
    //判断与已报名的项目不冲突且符合其它要求的可报名的项目
    if(registeredEventNumList.size() < 3) {//报名项目不能超过三个
        for(int i = 0; i < eventForm.size(); ++i) {
            bool ok = true;
            if(!eventForm[i].hasInputGrade && (gender == eventForm[i].m_gender)) {//项目没有结束（即尚未录入成绩）和性别相符（女子不能参加男子项目）
                for(int j = 0; j < registeredEventNumList.size(); ++j) {
                    //判断与已报的项目是否有时间冲突
                    if(eventForm[i].m_time == eventForm[registeredEventNumList[j]].m_time) {
                        ok = false;
                        break;
                    }
                }
                if(ok)
                    abledEventNumList.push_back(i);
            }
        }
    }

    //一个可以报名的项目都没有
    if(abledEventNumList.size() == 0) {
        cout << "Sorry, 您报名的项目太多（按照学校规定，一个运动员最多只能报名三个项目）或因时间冲突已经没有适合您的项目了，真的非常抱歉" << endl;
        system("pause");
        return false;
    }
    cout << "您可以报名的项目有：" << endl;
    cout << setw(20) << left << "编号" << setw(20) << left << "名称" << setw(20) << left << "地点" << "时间" << endl;
    for(auto i : abledEventNumList) {
        cout << setw(20) << left << i << setw(20) << left << eventForm[i].m_name << setw(20) << left << eventForm[i].m_venue << "第" << eventForm[i].m_time.substr(0, 2) <<"天 " << eventForm[i].m_time.substr(2, 12) << endl;
    }
    return true;
}

int SportsManager::findEvent() {
    string eventName, gender;
    cout << "请输入需要选择的项目名称：";
    cin >> eventName;
    cout << "请选择男子组或女子组（男/女）：";
    cin >> gender;
    int num = -1;
    //找寻项目在项目表中的位置
    for(int i = 0; i < eventForm.size(); ++i) {
        if(eventForm[i].m_name == eventName && eventForm[i].m_gender == gender) 
            num = i;
    }
    if(num == -1) {
        cout << "本届运动会无此项目" << endl;
        system("pause");
    }
    return num;
}

int SportsManager::getSporterNum() {
    ifstream iftr;
    iftr.open("sporterForm.txt", ios::in);
    int num = 0;
    string college, name, gender, grade;
    int registeredEventNum, rank, score;
    //文件有多少行就有多少条报名信息
    while(iftr >> college >> name >> gender >> registeredEventNum >> grade >> rank >> score) {
        ++num;
    }
    return num;
}

void SportsManager::loadSporterForm() {
    ifstream iftr;
    iftr.open("sporterForm.txt", ios::in);
    int cnt = 0;
    string college, name, gender, grade;
    int registeredEventNum, rank, score;
    //读取硬盘即txt文件中的已存的报名表信息
    while(iftr >> college >> name >> gender >> registeredEventNum >> grade >> rank >> score){
        registerForm[cnt] = new Sporter(college, name, gender, registeredEventNum, grade, rank, score);
        if(grade != "无" && !eventForm[registeredEventNum].hasInputGrade)//如果已经有成绩了，就将录入成绩标志赋为true
            eventForm[registeredEventNum].hasInputGrade = true;

        cnt++;
    }
    iftr.close();
}

void SportsManager::saveSporterForm() {
    ofstream oftr;
    oftr.open("sporterForm.txt", ios::out);
    //保存报名信息表和成绩
    for(int i = 0; i < sporterNum; ++i){
        oftr << registerForm[i]->m_college << ' ' << registerForm[i]->m_name << ' ' << registerForm[i]->m_gender << ' ' << registerForm[i]->m_registeredEventNum << ' ' << registerForm[i]->m_grade << ' ' << registerForm[i]->m_rank << ' ' << registerForm[i]->m_score << endl;
    }
    oftr.close();
}

void SportsManager::checkCollegeGrade() {
    vector<string> CollegeGrade;
    for (int i = 0; i < sporterNum; ++i) {
        CollegeGrade.push_back(registerForm[i]->m_college);
    }
    sort(CollegeGrade.begin(), CollegeGrade.end());
    CollegeGrade.erase(unique(CollegeGrade.begin(), CollegeGrade.end()), CollegeGrade.end());
    int n = CollegeGrade.size();
    vector<int> collegeScore(n, 0);
    cout << "以下是各学院的得分情况" << endl;
    //输出去重后的数组
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < sporterNum; ++j) {
            if (registerForm[j]->m_college == CollegeGrade[i]) {
                if(eventForm[registerForm[j]->m_registeredEventNum].hasInputGrade)      collegeScore[i] += registerForm[j]->m_score;
            }
        }

        cout << "学院:" << CollegeGrade[i] << " " << "总得分:" << collegeScore[i] << endl;
    }
    system("pause");
}

SportsManager::~SportsManager() {
    //释放开辟的堆空间
    if(registerForm != nullptr){
        for(int i = 0; i < sporterNum; i++){
            delete registerForm[i];
            registerForm[i] = nullptr;
        }
    }
    delete []registerForm;
    registerForm = nullptr;
}



bool cmp1(Sporter *a, Sporter *b) {
        return a->m_grade > b->m_grade;
}

bool cmp2(Sporter *a, Sporter *b) {
        return a->m_grade < b->m_grade;
}
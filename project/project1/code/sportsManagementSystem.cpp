#include <iostream>
#include "sprotsManager.h"
using namespace std;

int main() {
    SportsManager manager;
    int choice = 0;
    cout << "欢迎使用校园运动会管理系统！" << endl;
    while(true) {
        manager.showMenu();
        cin >> choice;
        switch(choice) {
            case 0:
                manager.quit();
                break;

            case 1:
                manager.checkEventInfo();
                break;
            
            case 2:
                manager.registerSporter();
                break;

            case 3:
                manager.deleteSporter();
                break;

            case 4:
                manager.findSporter();
                break;

            case 5:
                manager.modifySporter();
                break;

            case 6:
                manager.checkRegistrationInfo();
                break;

            case 7:
                manager.checkProgram();
                break;

            case 8:
                manager.inputGrade();
                break;

            case 9:
                manager.checkGrade();
                break;

            case 10:
                manager.checkCollegeGrade();
                break;
            
            default:
                system("cls");
                break;
        }
    }
}
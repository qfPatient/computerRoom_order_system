#include <iostream>
#include <fstream>
#include "identity.h"
#include "student.h"
#include "teacher.h"
#include "manager.h"
#include "globalFile.h"
using namespace std;

// 初始菜单
void menu();
// 退出系统
void exitSystem();
// 错误处理
void errorSave();
// 登录 文件名 操作身份
void logIn(string fileName, int type);
// 进入管理员的子菜单界面
void managerMenu(Identity *&manager);
// 进入学生的子菜单界面
void studentMenu(Identity *&student);
// 进入老师的子菜单界面
void teacherMEnu(Identity *&teacher);

int main()
{
    int select = 0;
    
    while(true)
    {
        menu();
        cin >> select;

        switch(select)
        {
            case 1: // 学生
                logIn(STUDENT_FILE, 1);
                break;
            case 2: // 牢师
                logIn(TEACHER_FILE, 2);
                break;
            case 3: // 管理员
                logIn(ADIMIN_FILE, 3);
                break;
            case 0: // 退出系统
                exitSystem();
                return 0;
            default:
                errorSave();
                break;
        }
    }



    return 0;
}

void logIn(string fileName,int type)
{
    // 父类指针,指向子类对象
    Identity *person = NULL;

    // 读文件
    ifstream ifs;
    ifs.open(fileName, ios::in);

    // 判断文件是否存在
    if(!ifs.is_open())
    {
        cout << "文件不存在！" << endl;
        ifs.close();
        return;
    }

    // 储存用户信息
    int id;
    string name;
    string pwd;

    // 判断身份
    if(type==1)
    {
        cout << "请输入你的学号: " << endl;
        cin >> id;
    }
    else if(type==2)
    {
        cout << "请输入您的职工号: " << endl;
        cin >> id;
    }

    cout << "请输入用户名:" << endl;
    cin >> name;

    cout << "请输入密码:" << endl;
    cin >> pwd;
    
    if(type==1)
    {
        // 学生身份验证
        ifstream ifs;
        ifs.open(STUDENT_FILE, ios::in);

        int fId;
        string fName;
        string fpwd;

        while(ifs>>fId && ifs>>fName && ifs>>fpwd)
        {
            if(fId==id && fName==name && fpwd==pwd)
            {
                
                cout << "学生信息验证成功!" << endl;
                person = new Student(id, name, pwd);
                system("pause");
                system("cls");

                // 进入到学生身份的子菜单
                studentMenu(person);

                return;
            }
        }
    }
    else if(type==2)
    {
        // 老师身份验证
        ifstream ifs;
        ifs.open(TEACHER_FILE, ios::in);

        int fId;
        string fName;
        string fpwd;

        while (ifs >> fId && ifs >> fName && ifs >> fpwd)
        {
            if (fId == id && fName == name && fpwd == pwd)
            {

                cout << "牢师信息验证成功!" << endl;
                person = new Teacher(id, name, pwd);
                system("pause");
                system("cls");

                // 进入到老师身份的子菜单
                teacherMEnu(person);
                return;
            }
        }
    }
    else if(type==3)
    {
        // 管理员身份验证
        ifstream ifs;
        ifs.open(ADIMIN_FILE, ios::in);

        string fName;
        string fpwd;

        while (ifs >> fName && ifs >> fpwd)
        {
            if (fName == name && fpwd == pwd)
            {

                cout << "管理员信息验证成功!" << endl;
                person = new Manager(name, pwd);
                system("pause");
                system("cls");

                // 进入到管理员身份的子菜单
                managerMenu(person);
                return;
            }
        }
    }
    
    cout << "验证登录失败！" << endl;
    system("pause");
    system("cls");

    return;
}

void exitSystem()
{
    cout << "欢迎下一次使用!" << endl;
    system("pause");
}

void errorSave()
{
    cout << "输入有误，请重新选择!" << endl;
    system("pause");
    system("cls");
}

void menu()
{
    cout << "======================  欢迎来到传智播客机房预约系统  ====================="<< endl;
    cout << endl<< "请输入您的身份" << endl;
    cout << "\t\t -------------------------------\n";
    cout << "\t\t|                               |\n";
    cout << "\t\t|          1.学生代表           |\n";
    cout << "\t\t|                               |\n";
    cout << "\t\t|          2.老    师           |\n";
    cout << "\t\t|                               |\n";
    cout << "\t\t|          3.管 理 员           |\n";
    cout << "\t\t|                               |\n";
    cout << "\t\t|          0.退    出           |\n";
    cout << "\t\t|                               |\n";
    cout << "\t\t -------------------------------\n";
    cout << "输入您的选择: ";
}

void managerMenu(Identity *&manager)
{
    while(true)
    {
        // 调用管理员子菜单
        manager->operMenu();

        // 父类指针转换为子类指针, 调用子类里其它接口
        Manager *man = (Manager *)manager;

        int select = 0;
        // 接受用户选择
        cin >> select;

        if(select==1) // 添加账号
        {
            man->addPerson();
        }
        else if(select==2) // 查看账号
        {
            man->showPerson();
        }
        else if(select==3) // 查看机房
        {
            man->showComputer();
        }
        else if(select==4) // 清空预约
        {
            man->clearFile();
        }
        else // 注销登录
        {
            delete manager;
            cout << "注销成功" << endl;
            system("pause");
            system("cls");
            return;
        }
    }
}

void studentMenu(Identity *&student)
{
    while(true)
    {
        // 调用学生子菜单
        student->operMenu();

        // 父类指针转为子类学生指针,调用学生类其它接口
        Student *man = (Student *)student;

        int select = 0;
        // 接受用户选择
        cin >> select;

        if (select == 1) // 申请预约
        {
            man->applyOrder();
        }
        else if (select == 2) // 查看我的预约
        {
            man->showMyOrder();
        }
        else if (select == 3) // 查看所有预约
        {
            man->showAllOrder();
        }
        else if (select == 4) // 取消预约
        {
            man->cancelOrder();
        }
        else // 注销登录
        {
            delete student;
            cout << "注销成功" << endl;
            system("pause");
            system("cls");
            return;
        }
    }
}

void teacherMEnu(Identity *&teacher)
{
    while(true)
    {
        // 调用老师子菜单
        teacher->operMenu();

        // 将父类指针强转为老师类指针
        Teacher *man = (Teacher *)teacher;

        int select = 0;
        // 接受用户选择
        cin >> select;

        if(select==1)
        {
            man->showAllOrder();
        }
        else if(select==2)
        {
            man->validOrder();
        }
        else
        {
            delete teacher;
            cout << "注销成功!" << endl;
            system("pause");
            system("cls");
            return;
        }
    }
}
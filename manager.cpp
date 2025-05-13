#include "manager.h"
#include "globalFile.h"

// 默认构造
Manager::Manager()
{
}

// 有参构造
Manager::Manager(string name, string pwd)
{
    // 初始化管理员的信息
    this->m_Name = name;
    this->m_Pwd = pwd;

    this->initVector();
}

// 选择菜单
void Manager::operMenu()
{
    cout << "欢迎管理员：" << this->m_Name << "登录！" << endl;
    cout << "\t\t ---------------------------------\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          1.添加账号            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          2.查看账号            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          3.查看机房            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          4.清空预约            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          0.注销登录            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t ---------------------------------\n";
    cout << "请选择您的操作： " << endl;
}

// 添加账号
void Manager::addPerson()
{
    cout << "当前学生数量为: " << vStu.size() << endl;
    cout << "当前老师数量为: " << vTea.size() << endl;
    cout << "请输入添加账号的类型:" << endl;
    cout << "1. 学生" << endl;
    cout << "2. 老师" << endl;

    string fileName;
    int id;
    string name;
    string pwd;

    int select = 0;
    cin >> select;

    while(select!=1&&select!=2)
    {
        cout << "输入错误,请重新输入!" << endl;
        cin >> select;
    }

    if(select==1)
    {
        fileName = STUDENT_FILE;
    }
    else if(select==2)
    {
        fileName = TEACHER_FILE;
    }

    ofstream ofs;
    ofs.open(fileName, ios::out | ios::app);

    if(!ofs.is_open())
    {
        cout << "Failed to open " << fileName << "." << endl;
        return;
    }

    bool is_exist = 0;
    if(select==1)
    {
        do
        {
            is_exist = 0;
            cout << "请输入学号:" << endl;
            cin >> id;
            for (int i = 0; i < vStu.size(); i++)
            {
                if (id == vStu[i].m_Id)
                {
                    is_exist = 1;
                    break;
                }
            }

            if (is_exist)
            {
                cout << "学号已存在,请重新输入!" << endl;
            }

        } while (is_exist==1);
    }
    else
    {
        do
        {
            is_exist = 0;
            cout << "请输入职工号:" << endl;
            cin >> id;
            for (int i = 0; i < vTea.size(); i++)
            {
                if (id == vTea[i].m_EmpId)
                {
                    is_exist = 1;
                    break;
                }
            }

            if (is_exist)
            {
                cout << "职工号已存在,请重新输入!" << endl;
            }

        } while (is_exist == 1);
    }

    cout << "请输入用户名:" << endl;
    cin >> name;

    cout << "请输入密码:" << endl;
    cin >> pwd;

    ofs << id << " " << name << " " << pwd << endl;
    cout << "信息已成功添加!" << endl;

    if(select==1)
    {
        Student s;
        s.m_Id = id;
        s.m_Name = name;
        s.m_Pwd = pwd;
        vStu.push_back(s);
    }
    else if(select==2)
    {
        Teacher t;
        t.m_EmpId = id;
        t.m_Name = name;
        t.m_Pwd = pwd;
        vTea.push_back(t);
    }

    system("pause");
    system("cls");
    ofs.close();
}

// 查看账号
void Manager::showPerson()
{
    cout << "请选择查看内容:" << endl;
    cout << "1. 学生" << endl;
    cout << "2. 老师" << endl;

    int select = 0;
    cin >> select;
    while(select!=1&&select!=2)
    {
        cout << "输入错误,请重新输入！" << endl;
        cin >> select;
    }

    if(select==1)
    {
        for (int i = 0; i < vStu.size();i++)
        {
            cout << "学号: " << vStu[i].m_Id << " 用户名: " << vStu[i].m_Name << " 密码: " << vStu[i].m_Pwd << endl;
        }
    }
    else if(select==2)
    {
        for (int i = 0; i < vTea.size(); i++)
        {
            cout << "职工号: " << vTea[i].m_EmpId << " 用户名: " << vTea[i].m_Name << " 密码: " << vTea[i].m_Pwd << endl;
        }
    }

    system("pause");
    system("cls");
}

// 查看机房信息
void Manager::showComputer()
{
    cout << "机房信息如下:" << endl;
    cout << "当前机房数量为: " << vCom.size() << endl;

    for (int i = 0; i < vCom.size();i++)
    {
        cout << "机房编号: " << vCom[i].m_ComId << " 机房最大容量: " << vCom[i].m_MaxNum << endl;
    }

    system("pause");
    system("cls");
}

// 清空预约记录
void Manager::clearFile()
{
    ofstream ofs(ORDER_FILE, ios::trunc);
    ofs.close();

    cout << "清空成功!" << endl;
    system("pause");
    system("cls");
}

// 容器初始化
void Manager::initVector()
{
    this->vStu.clear();
    this->vTea.clear();

    ifstream ifs1;
    ifs1.open(STUDENT_FILE, ios::in);

    if(!ifs1.is_open())
    {
        cout << "student.txt is failed to open ." << endl;
        return;
    }

    Student s;
    while(ifs1>>s.m_Id && ifs1>>s.m_Name && ifs1>>s.m_Pwd)
    {
        vStu.push_back(s);
    }
    ifs1.close();

    ifstream ifs2;
    ifs2.open(TEACHER_FILE, ios::in);

    if (!ifs2.is_open())
    {
        cout << "teacher.txt is failed to open ." << endl;
        return;
    }

    Teacher t;
    while (ifs2 >> t.m_EmpId && ifs2 >> t.m_Name && ifs2 >> t.m_Pwd)
    {
        vTea.push_back(t);
    }
    ifs2.close();

    // 获取机房信息
    ifstream ifs;
    ifs.open(COMPUTER_FILE, ios::in);

    ComputerRoom c;
    while(ifs>>c.m_ComId && ifs>>c.m_MaxNum)
    {
        vCom.push_back(c);
    }
    ifs.close();
}
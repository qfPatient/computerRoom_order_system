#pragma once
#include <vector>
#include "identity.h"
#include "student.h"
#include "teacher.h"
#include "computerRoom.h"

class Manager:public Identity
{
public:
    // 默认构造
    Manager();

    // 有参构造
    Manager(string name, string pwd);

    // 选择菜单
    virtual void operMenu();

    // 添加账号
    void addPerson();

    // 查看账号
    void showPerson();

    // 查看机房信息
    void showComputer();

    // 清空预约记录
    void clearFile();

    // 容器初始化
    void initVector();

    // 学生容器
    vector<Student> vStu;

    // 老师容器
    vector<Teacher> vTea;

    // 机房容器
    vector<ComputerRoom> vCom;
};
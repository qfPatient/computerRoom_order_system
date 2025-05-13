#pragma once
#include <vector>
#include "identity.h"
#include "computerRoom.h"
#include "globalFile.h"
#include "orderFile.h"

class Student:public Identity
{
public:
    int m_Id; // 学号

    Student(); // 默认构造

    Student(int id, string name, string pwd); // 姓名 学号 密码

    virtual void operMenu(); // 菜单

    void applyOrder(); // 申请预约

    void showMyOrder(); // 查看我的预约

    void showAllOrder(); // 查看所有预约

    void cancelOrder(); // 取消预约

    vector<ComputerRoom> vCom;
};
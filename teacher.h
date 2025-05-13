#pragma once
#include <vector>
#include "identity.h"
#include "computerRoom.h"
#include "globalFile.h"
#include "orderFile.h"
class Teacher:public Identity
{
public:
    int m_EmpId; // 工号

    Teacher(); // 默认构造

    Teacher(int id, string name, string pwd); // 有参构造

    virtual void operMenu(); // 菜单界面

    void showAllOrder(); // 查看所有预约

    void validOrder(); // 审核预约
};
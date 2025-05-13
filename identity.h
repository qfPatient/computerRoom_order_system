#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Identity
{
public:
    string m_Name; // 用户名
    string m_Pwd; // 密码
    virtual void operMenu() = 0; // 操作菜单
};
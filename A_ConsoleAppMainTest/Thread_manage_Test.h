#pragma once
class Thread_manage_Test
{
public:
    Thread_manage_Test();
    ~Thread_manage_Test();

    DWORD RunSecond(int nID, int nSecond = 5);
    DWORD RunAll(int nID);
};


#include "stdafx.h"
#include "Thread_manage_Test.h"
#include <time.h>


Thread_manage_Test::Thread_manage_Test()
{
}


Thread_manage_Test::~Thread_manage_Test()
{
}


DWORD Thread_manage_Test::RunSecond(int nID, int nSecond)
{
    //cout << "RunSecond:" << nID << " start" << endl;
    Sleep(nSecond * 1000);
    //cout << "RunSecond:" << nID << " end" << endl;
    return 0;
}

DWORD Thread_manage_Test::RunAll(int nID)
{
    //cout << "RunAll:" << nID << " start" << endl;
    Sleep(50 * 1000);
    //cout << "RunAll:" << nID << " end" << endl;
    return 0;
}

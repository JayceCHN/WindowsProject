#include "stdafx.h"
#include "Thread_manage_Test.h"
#include "../Thread_manage/Thread_manage.h"

int main()
{
    int nBusyNum = 0, nAllNum = 0;
    Thread_manage *pTmanage = new Thread_manage();
    Thread_manage_Test *pTmanageTest = new Thread_manage_Test();
    pTmanage->getThreadNum(nBusyNum, nAllNum);
    cout << "#####  nBusyNum:" << nBusyNum << "     nAllNum:" << nAllNum << endl;
    for (size_t i = 0; i < 3; i++)
    {
        CallbackP1<Thread_manage_Test, int> *pP1 = new CallbackP1<Thread_manage_Test, int>(pTmanageTest, &Thread_manage_Test::RunAll);
        pP1->setParam(i);
        pTmanage->AddTask(pP1);
    }
    pTmanage->getThreadNum(nBusyNum, nAllNum);
    cout << "#####  nBusyNum:" << nBusyNum << "     nAllNum:" << nAllNum << endl;
    for (size_t i = 0; i < 3; i++)
    {
        CallbackP2<Thread_manage_Test, int, int> *pP2 = new CallbackP2<Thread_manage_Test, int, int>(pTmanageTest, &Thread_manage_Test::RunSecond);
        pP2->setParam(i + 3,5);
        pTmanage->AddTask(pP2);
    }
    pTmanage->getThreadNum(nBusyNum, nAllNum);
    cout << "#####  nBusyNum:" << nBusyNum << "     nAllNum:" << nAllNum << endl;
    for (size_t i = 0; i < 3; i++)
    {
        CallbackP2<Thread_manage_Test, int, int> *pP2 = new CallbackP2<Thread_manage_Test, int, int>(pTmanageTest, &Thread_manage_Test::RunSecond);
        pP2->setParam(i + 6, 3);
        pTmanage->AddTask(pP2);
    }
    int nTime = 60;
    while (nTime)
    {
        Sleep(1000);
        pTmanage->getThreadNum(nBusyNum, nAllNum);
        cout << "#####  nBusyNum:" << nBusyNum << "     nAllNum:" << nAllNum << endl;
        if (nTime == 50)
        {
            CallbackP2<Thread_manage_Test, int, int> *pP2 = new CallbackP2<Thread_manage_Test, int, int>(pTmanageTest, &Thread_manage_Test::RunSecond);
            pP2->setParam(nTime, 10);
            pTmanage->AddTask(pP2);
        }
        if (nTime == 47)
        {
            CallbackP2<Thread_manage_Test, int, int> *pP2 = new CallbackP2<Thread_manage_Test, int, int>(pTmanageTest, &Thread_manage_Test::RunSecond);
            pP2->setParam(nTime, 10);
            pTmanage->AddTask(pP2);
        }
        if (nTime == 20)
        {
            CallbackP2<Thread_manage_Test, int, int> *pP2 = new CallbackP2<Thread_manage_Test, int, int>(pTmanageTest, &Thread_manage_Test::RunSecond);
            pP2->setParam(nTime, 5);
            pTmanage->AddTask(pP2);
        }
        nTime--;
    }
    return 0;
}
#include "ucpu.h"
#include <qglobal.h>
#ifdef Q_OS_WIN

double GetCPUUsages()
{
    SYSTEM_BASIC_INFORMATION		SysBaseInfo;
    SYSTEM_TIME_INFORMATION			SysTimeInfo;
    SYSTEM_PERFORMANCE_INFORMATION	SysPerfInfo;
    LONG							status = NO_ERROR;
    LARGE_INTEGER					liOldIdleTime = {{0, 0}};
    LARGE_INTEGER					liOldSystemTime = {{0, 0}};
    double							dbIdleTime;
    double							dbSystemTime;
    PROCNTQSI						NtQuerySystemInformation;

    HMODULE hDLL = GetModuleHandle(TEXT("ntdll.dll"));

    NtQuerySystemInformation = (PROCNTQSI)GetProcAddress(hDLL, "NtQuerySystemInformation");
    if (!NtQuerySystemInformation)
        return 0;

    status = NtQuerySystemInformation(SystemBasicInformation, &SysBaseInfo, sizeof(SysBaseInfo), NULL);
    if (status != NO_ERROR)
        return 0;


    // get system time
    status = NtQuerySystemInformation(SystemTimeInformation, &SysTimeInfo, sizeof(SysTimeInfo), NULL);
    if (status != NO_ERROR)
        return 0;


    // get system idle time
    status = NtQuerySystemInformation(SystemPerformanceInformation, &SysPerfInfo, sizeof(SysPerfInfo), NULL);
    if (status != NO_ERROR)
        return 0;


    liOldIdleTime = SysPerfInfo.IdleTime;
    liOldSystemTime = SysTimeInfo.liKeSystemTime;

    // wait one second
    Sleep(1000);

    // get new System time
    status = NtQuerySystemInformation(SystemTimeInformation, &SysTimeInfo, sizeof(SysTimeInfo), NULL);

    if (status != NO_ERROR)
        return 0;

    // get new system idle time
    status = NtQuerySystemInformation(SystemPerformanceInformation, &SysPerfInfo, sizeof(SysPerfInfo), NULL);

    if (status != NO_ERROR)
        return 0;
    // current value = new value - old value
    dbIdleTime = Li2Double(SysPerfInfo.IdleTime) - Li2Double(liOldIdleTime);
    dbSystemTime = Li2Double(SysTimeInfo.liKeSystemTime) - Li2Double(liOldSystemTime);

    // currentCpuIdle = IdleTime / SystemTime;
    dbIdleTime = dbIdleTime / dbSystemTime;

    // currentCpuUsage% = 100 - (CurrentCpuIdle * 100) / NumberOfProcessors
    dbIdleTime = 100.0 - dbIdleTime * 100.0 / (double)SysBaseInfo.NumberOfProcessors + 0.5;

    return dbIdleTime;
}
#endif

#ifdef Q_OS_LINUX
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
static unsigned long long lastTotalUser, lastTotalUserLow, lastTotalSys, lastTotalIdle;


void init()
{
    FILE* file = fopen("/proc/stat", "r");
    fscanf(file, "cpu %Ld %Ld %Ld %Ld", &lastTotalUser, &lastTotalUserLow,
           &lastTotalSys, &lastTotalIdle);
    fclose(file);
}

double GetCPUUsages()
{

    sleep(1);
    double percent;
    FILE* file;
    unsigned long long totalUser, totalUserLow, totalSys, totalIdle, total;


    file = fopen("/proc/stat", "r");
    fscanf(file, "cpu %Ld %Ld %Ld %Ld", &totalUser, &totalUserLow,
           &totalSys, &totalIdle);
    fclose(file);


    if (totalUser < lastTotalUser || totalUserLow < lastTotalUserLow ||
            totalSys < lastTotalSys || totalIdle < lastTotalIdle){
        //Overflow detection.
        percent = -1.0;
    }
    else{
        total = (totalUser - lastTotalUser) + (totalUserLow - lastTotalUserLow) +
                (totalSys - lastTotalSys);
        percent = total;
        total += (totalIdle - lastTotalIdle);
        percent /= total;
        percent *= 100;
    }


    lastTotalUser = totalUser;
    lastTotalUserLow = totalUserLow;
    lastTotalSys = totalSys;
    lastTotalIdle = totalIdle;

    return percent;
}
#endif


#ifdef Q_OS_WIN
#include "windows.h"
/*NTSYSAPI NTSTATUS NTAPI NtQuerySystemInformation(
        IN UINT SystemInformationClass,		// information type
        OUT PVOID SystemInformation,		// pointer to buffer
        IN ULONG SystemInformationLength,	// buffer size in bytes
        OUT PULONG ReturnLength OPTIONAL	// pointer to a 32 bit variable that
                                            // receives the number of bytes written
                                            // to the buffer
 );*/

#define Li2Double(x)	((double)((x).HighPart) * 4.294967296E9 + (double)((x).LowPart))
#define SystemBasicInformation 0
#define SystemPerformanceInformation 2
#define SystemTimeInformation 3

typedef struct _SYSTEM_BASIC_INFORMATION {
    BYTE Reserved1[4];
    ULONG MaximumIncrement;
    ULONG PhysicalPageSize;
    ULONG NumberOfPhysicalPages;
    ULONG LowestPhysicalPage;
    ULONG HighestPhysicalPage;
    ULONG AllocationGranularity;
    ULONG_PTR LowestUserAddress;
    ULONG_PTR HighestUserAddress;
    ULONG_PTR ActiveProcessors;
    CCHAR NumberOfProcessors;
  } SYSTEM_BASIC_INFORMATION,*PSYSTEM_BASIC_INFORMATION;


typedef struct _SYSTEM_PERFORMANCE_INFORMATION {
  LARGE_INTEGER IdleTime;
  LARGE_INTEGER ReadTransferCount;
  LARGE_INTEGER WriteTransferCount;
  LARGE_INTEGER OtherTransferCount;
  ULONG ReadOperationCount;
  ULONG WriteOperationCount;
  ULONG OtherOperationCount;
  ULONG AvailablePages;
  ULONG TotalCommittedPages;
  ULONG TotalCommitLimit;
  ULONG PeakCommitment;
  ULONG PageFaults;
  ULONG WriteCopyFaults;
  ULONG TransitionFaults;
  ULONG CacheTransitionFaults;
  ULONG DemandZeroFaults;
  ULONG PagesRead;
  ULONG PageReadIos;
  ULONG CacheReads;
  ULONG CacheIos;
  ULONG PagefilePagesWritten;
  ULONG PagefilePageWriteIos;
  ULONG MappedFilePagesWritten;
  ULONG MappedFilePageWriteIos;
  ULONG PagedPoolUsage;
  ULONG NonPagedPoolUsage;
  ULONG PagedPoolAllocs;
  ULONG PagedPoolFrees;
  ULONG NonPagedPoolAllocs;
  ULONG NonPagedPoolFrees;
  ULONG TotalFreeSystemPtes;
  ULONG SystemCodePage;
  ULONG TotalSystemDriverPages;
  ULONG TotalSystemCodePages;
  ULONG SmallNonPagedLookasideListAllocateHits;
  ULONG SmallPagedLookasideListAllocateHits;
  ULONG Reserved3;
  ULONG MmSystemCachePage;
  ULONG PagedPoolPage;
  ULONG SystemDriverPage;
  ULONG FastReadNoWait;
  ULONG FastReadWait;
  ULONG FastReadResourceMiss;
  ULONG FastReadNotPossible;
  ULONG FastMdlReadNoWait;
  ULONG FastMdlReadWait;
  ULONG FastMdlReadResourceMiss;
  ULONG FastMdlReadNotPossible;
  ULONG MapDataNoWait;
  ULONG MapDataWait;
  ULONG MapDataNoWaitMiss;
  ULONG MapDataWaitMiss;
  ULONG PinMappedDataCount;
  ULONG PinReadNoWait;
  ULONG PinReadWait;
  ULONG PinReadNoWaitMiss;
  ULONG PinReadWaitMiss;
  ULONG CopyReadNoWait;
  ULONG CopyReadWait;
  ULONG CopyReadNoWaitMiss;
  ULONG CopyReadWaitMiss;
  ULONG MdlReadNoWait;
  ULONG MdlReadWait;
  ULONG MdlReadNoWaitMiss;
  ULONG MdlReadWaitMiss;
  ULONG ReadAheadIos;
  ULONG LazyWriteIos;
  ULONG LazyWritePages;
  ULONG DataFlushes;
  ULONG DataPages;
  ULONG ContextSwitches;
  ULONG FirstLevelTbFills;
  ULONG SecondLevelTbFills;
  ULONG SystemCalls;
} SYSTEM_PERFORMANCE_INFORMATION, *PSYSTEM_PERFORMANCE_INFORMATION;

typedef LONG (WINAPI *PROCNTQSI) (UINT, PVOID, ULONG, PULONG);

typedef struct
{
    LARGE_INTEGER	liKeBootTime;
    LARGE_INTEGER	liKeSystemTime;
    LARGE_INTEGER	liExpTimeZoneBias;
    ULONG			uCurrentTimeZoneID;
    DWORD			dwReserved;
} SYSTEM_TIME_INFORMATION;


#endif





#ifdef Q_OS_WIN

static double GetCPUUsages()
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

static double GetCPUUsages()
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


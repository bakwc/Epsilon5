#pragma once
#include <QGLWidget>
#include <QImage>
#include <QThread>
#include <QQueue>
#include <QHash>
#include <QVector>
#include "../Epsilon5-Proto/Epsilon5.pb.h"
#include "imagestorage.h"
#include "map.h"
#include "objects.h"
#include "../utils/ufullscreenwrapper.h"
#include "menu.h"

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


class TApplication;
double GetCPUUsages();

class TCPUThread : public QThread {
public:
    void run() {
        time = GetCPUUsages();
    }

    double time;
};

enum ETeam {
    T_One,
    T_Second,
    T_Neutral
};

struct TRespPoint {
    int X;
    int Y;
    ETeam Team;
};

struct TPlayerStat {
    size_t Id;
    size_t Score;
    size_t Deaths;
    size_t Kills;
};

class TMainDisplay : public QGLWidget, public utils::UFullscreenWrapper
{
    Q_OBJECT
public:
    explicit TMainDisplay(TApplication* application, QGLWidget* parent = 0);
    void Init();
    ~TMainDisplay();
    inline const Epsilon5::Control& GetControl() { return Control; }
    QPoint GetCenter();
    QPoint GetCursorPos();
public slots:
    void RedrawWorld();
    void toggleFullscreen();

private:
    void paintEvent(QPaintEvent*);
    void timerEvent(QTimerEvent*);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

    QPoint GetPlayerCoordinatesAndPing();
    void DrawText(QPainter& painter, const QPoint& pos,
            const QString& text, int FONT_SIZE_PT);
    void DrawFps(QPainter& painter);
    void DrawPing(QPainter& painter);
    void DrawCpu(QPainter &painter);
    void DrawWorld(QPainter& painter);
    void DrawPlayers(QPainter& painter, QPainter& miniMap,
            const QPoint& playerPos, const QPoint& widgetCenter);
    void DrawBullets(QPainter& painter, const QPoint& playerPos,
            const QPoint& widgetCenter);
    template<typename T>
    void DrawObjects(const T& GetObjFunc, TObjects* objects, size_t size,
            QPainter& painter, QPainter& miniMap,
            const QPoint& playerPos, const QPoint& widgetCenter);
    void DrawRespPoints(QPainter& painter, QPainter& miniMap,
            const QPoint& playerPos, const QPoint& widgetCenter);
    void DrawStats(QPainter& painter);

    void SetMovementKeysState(bool state, const QKeyEvent* event);

private:
    TApplication* Application;
    TImageStorage* Images;
    QQueue<Epsilon5::World> PacketsQueue;
    Epsilon5::Control Control;
    TMap* Map;
    TObjects* Objects;
    TObjects* Vehicles;
    const Epsilon5::World* CurrentWorld;
    QHash<size_t, QString> PlayerNames;
    QVector<TRespPoint> RespPoints;
    QVector<TPlayerStat> Stats;
    bool ShowStats;
    TMenu Menu;
    int Ping;
    TCPUThread Thread;
};

#include <QObject>
#include <QtCharts/QLineSeries>
#include <QLabel>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <mutex>
#include "CPUClass.h"
#include "RAMClass.h"
#include "DiskSpaceClass.h"
#include "StaticData.h"
#include "ReadingMethods.h"
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

class MonitorWorker : public QObject {
    Q_OBJECT

public:
    MonitorWorker(CPUClass& cpuClass, RAMClass& ramClass, DiskSpaceClass& diskSpaceClass, StaticData& staticData, ReadingMethods& readingMethods)
        : cpuClass(cpuClass), ramClass(ramClass), diskSpaceClass(diskSpaceClass), staticData(staticData), readingMethods(readingMethods), cpuTimeCounter(0), ramTimeCounter(0), diskTimeCounter(0) {}

public slots:
    void monitorCPU(QLineSeries* cpuSeries);
    void monitorRAM(QLineSeries* ramSeries);
    void monitorDiskSpace(QLineSeries* diskSeries);
    void monitorProcesses(QLabel* processLabel);
    void monitorCycles(QLabel* cyclesLabel);

private:
    CPUClass& cpuClass;
    RAMClass& ramClass;
    DiskSpaceClass& diskSpaceClass;
    StaticData& staticData;
    ReadingMethods& readingMethods;
    int cpuTimeCounter;
    int ramTimeCounter;
    int diskTimeCounter;
};

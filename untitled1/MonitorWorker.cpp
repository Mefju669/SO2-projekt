#include "MonitorWorker.h"

mutex ramMutex;
mutex cpuMutex;
mutex diskSpaceMutex;
mutex staticDataMutex;


void MonitorWorker::monitorCPU(QLineSeries* cpuSeries) {
        while (true) {
            double CPUUsage = readingMethods.CountCPUUsage();
            {
                lock_guard<mutex> writeLock(cpuMutex);
                cpuClass.addData(CPUUsage);
            }

            cpuSeries->append(cpuTimeCounter++, CPUUsage);

            this_thread::sleep_for(chrono::seconds(1));
        }
    }

void MonitorWorker::monitorRAM(QLineSeries* ramSeries) {
        while (true) {
            double RAMUsage = readingMethods.CountRAMUsage();
            {
                lock_guard<mutex> writeLock(ramMutex);
                ramClass.addData(RAMUsage);
            }

            ramSeries->append(ramTimeCounter++, RAMUsage);

            this_thread::sleep_for(chrono::seconds(1));
        }
    }

void MonitorWorker::monitorDiskSpace(QLineSeries* diskSeries) {
    while (true) {
        double DiskUsage = readingMethods.CountDiskSpace();
        {
            lock_guard<mutex> writeLock(diskSpaceMutex);
            diskSpaceClass.addData(DiskUsage);
        }

        diskSeries->append(diskTimeCounter++, DiskUsage);

        this_thread::sleep_for(chrono::seconds(1));
    }
}


void MonitorWorker::monitorProcesses(QLabel* processLabel) {
        while (true) {
            int numProcesses = readingMethods.CountProcesses();
            {
                lock_guard<mutex> writeLock(staticDataMutex);
                staticData.numProcesses = numProcesses;
            }
            QString processText = QString("<font color='blue'>Number of Processes: %1</font>").arg(numProcesses);
            QMetaObject::invokeMethod(processLabel, "setText", Qt::QueuedConnection, Q_ARG(QString, processText));
            this_thread::sleep_for(chrono::seconds(1));
        }
    }

void MonitorWorker::monitorCycles(QLabel* cyclesLabel) {
        while (true) {
            unsigned long long numCycles = readingMethods.CountCycles();
            {
                lock_guard<mutex> writeLock(staticDataMutex);
                staticData.numCycles = numCycles;
            }
            QString cyclesText = QString("<font color='blue'>Number of CPU Cycles: %1</font>").arg(numCycles);
            QMetaObject::invokeMethod(cyclesLabel, "setText", Qt::QueuedConnection, Q_ARG(QString, cyclesText));
            this_thread::sleep_for(chrono::seconds(1));
        }
    }



#include "MonitorWorker.h"

// Mutexes to ensure thread-safe access to shared resources
mutex ramMutex;
mutex cpuMutex;
mutex diskSpaceMutex;
mutex staticDataMutex;

// Function to monitor CPU usage
void MonitorWorker::monitorCPU(QLineSeries* cpuSeries) {
    while (true) {
        // Calculate CPU usage
        double CPUUsage = readingMethods.CountCPUUsage();

        // Store CPU usage data safely
        {
            lock_guard<mutex> writeLock(cpuMutex);
            cpuClass.addData(CPUUsage);
        }

        // Append the CPU usage data to the series for the chart
        cpuSeries->append(cpuTimeCounter++, CPUUsage);

        // Sleep for 1 second before the next update
        this_thread::sleep_for(chrono::seconds(1));
    }
}

// Function to monitor RAM usage
void MonitorWorker::monitorRAM(QLineSeries* ramSeries) {
    while (true) {
        // Calculate RAM usage
        double RAMUsage = readingMethods.CountRAMUsage();

        // Store RAM usage data safely
        {
            lock_guard<mutex> writeLock(ramMutex);
            ramClass.addData(RAMUsage);
        }

        // Append the RAM usage data to the series for the chart
        ramSeries->append(ramTimeCounter++, RAMUsage);

        // Sleep for 1 second before the next update
        this_thread::sleep_for(chrono::seconds(1));
    }
}

// Function to monitor Disk Space usage
void MonitorWorker::monitorDiskSpace(QLineSeries* diskSeries) {
    while (true) {
        // Calculate Disk Space usage
        double DiskUsage = readingMethods.CountDiskSpace();

        // Store Disk Space usage data safely
        {
            lock_guard<mutex> writeLock(diskSpaceMutex);
            diskSpaceClass.addData(DiskUsage);
        }

        // Append the Disk Space usage data to the series for the chart
        diskSeries->append(diskTimeCounter++, DiskUsage);

        // Sleep for 1 second before the next update
        this_thread::sleep_for(chrono::seconds(1));
    }
}

// Function to monitor the number of processes
void MonitorWorker::monitorProcesses(QLabel* processLabel) {
    while (true) {
        // Calculate the number of processes
        int numProcesses = readingMethods.CountProcesses();

        // Store the number of processes safely
        {
            lock_guard<mutex> writeLock(staticDataMutex);
            staticData.numProcesses = numProcesses;
        }

        // Update the label with the number of processes using a thread-safe method
        QString processText = QString("<font color='blue'>Number of Processes: %1</font>").arg(numProcesses);
        QMetaObject::invokeMethod(processLabel, "setText", Qt::QueuedConnection, Q_ARG(QString, processText));

        // Sleep for 1 second before the next update
        this_thread::sleep_for(chrono::seconds(1));
    }
}

// Function to monitor the number of CPU cycles
void MonitorWorker::monitorCycles(QLabel* cyclesLabel) {
    while (true) {
        // Calculate the number of CPU cycles
        unsigned long long numCycles = readingMethods.CountCycles();

        // Store the number of CPU cycles safely
        {
            lock_guard<mutex> writeLock(staticDataMutex);
            staticData.numCycles = numCycles;
        }

        // Update the label with the number of CPU cycles using a thread-safe method
        QString cyclesText = QString("<font color='blue'>Number of CPU Cycles: %1</font>").arg(numCycles);
        QMetaObject::invokeMethod(cyclesLabel, "setText", Qt::QueuedConnection, Q_ARG(QString, cyclesText));

        // Sleep for 1 second before the next update
        this_thread::sleep_for(chrono::seconds(1));
    }
}

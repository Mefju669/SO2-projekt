#include <iostream>
#include <thread>
#include <chrono>
#include "ReadingMethods.h"
#include "SystemMetrics.h"

using namespace std;

// Funkcje monitorujące
void monitorProcesses(SystemMetrics& metrics, ReadingMethods& readingMethods, mutex& mtx) {
    while (true) {
        int numProcesses = readingMethods.CountProcesses();
        {
            lock_guard<mutex> lock(mtx);
            metrics.numProcesses = numProcesses;
        }
        this_thread::sleep_for(chrono::seconds(1));
    }
}

void monitorDiskSpace(SystemMetrics& metrics, ReadingMethods& readingMethods, mutex& mtx) {
    while (true) {
        double diskSpacePercent = readingMethods.CountDiskSpace();
        {
            lock_guard<mutex> lock(mtx);
            metrics.diskSpacePercent = diskSpacePercent;
        }
        this_thread::sleep_for(chrono::seconds(1));
    }
}

void monitorProcessorCycles(SystemMetrics& metrics, ReadingMethods& readingMethods, mutex& mtx) {
    while (true) {
        unsigned long long procCycles = readingMethods.CountCycles();
        {
            lock_guard<mutex> lock(mtx);
            metrics.processorCycles = procCycles;
        }
        this_thread::sleep_for(chrono::seconds(1));
    }
}

void monitorCPUUsage(SystemMetrics& metrics, ReadingMethods& readingMethods, mutex& mtx) {
    while (true) {
        double CPUUsage = readingMethods.CountCPUUsage();
        {
            lock_guard<mutex> lock(mtx);
            metrics.cpuUsage = CPUUsage;
        }
        this_thread::sleep_for(chrono::seconds(1));
    }
}

void monitorRAMUsage(SystemMetrics& metrics, ReadingMethods& readingMethods, mutex& mtx) {
    while (true) {
        double RAMUsage = readingMethods.CountRAMUsage();
        {
            lock_guard<mutex> lock(mtx);
            metrics.ramUsage = RAMUsage;
        }
        this_thread::sleep_for(chrono::seconds(1));
    }
}

int main() {
    SystemMetrics systemMetrics;
    ReadingMethods readingMethods;
    mutex mtx;

    // 5 wątków do pomiarów
    thread processesThread(monitorProcesses, ref(systemMetrics), ref(readingMethods), ref(mtx));
    thread diskSpaceThread(monitorDiskSpace, ref(systemMetrics), ref(readingMethods), ref(mtx));
    thread processorCyclesThread(monitorProcessorCycles, ref(systemMetrics), ref(readingMethods), ref(mtx));
    thread cpuUsageThread(monitorCPUUsage, ref(systemMetrics), ref(readingMethods), ref(mtx));
    thread ramUsageThread(monitorRAMUsage, ref(systemMetrics), ref(readingMethods), ref(mtx));


    while (true) {
        {

            systemMetrics.displayMetrics();
        }
        this_thread::sleep_for(chrono::seconds(1));
    }

    // tu trzeba jakieś action listenery zamiast while dodać żeby te joiny się robiły po zakończeniu
    //programu np po zamknięciu czy coś
    processesThread.join();
    diskSpaceThread.join();
    processorCyclesThread.join();
    cpuUsageThread.join();
    ramUsageThread.join();

    return 0;
}

#include "SystemMetrics.h"
#include <iostream>

using namespace std;



SystemMetrics::SystemMetrics() : numProcesses(0), diskSpacePercent(0.0), processorCycles(0), cpuUsage(0.0), ramUsage(0.0) {}


void SystemMetrics::displayMetrics() const {
    lock_guard<mutex> lock(mtx);


    cout << "Liczba otwartych procesów: " << numProcesses << endl;
    cout << "Miejsce na dysku C: " << diskSpacePercent << "%" << endl;
    cout << "Cykle procesora od uruchomienia: " << processorCycles << endl;
    cout << "Zużycie CPU: " << cpuUsage << "%" << endl;
    cout << "Zużycie RAM: " << ramUsage << " %" << endl;
}


void SystemMetrics::updateMetrics(int numProcesses, double diskSpacePercent, unsigned long long processorCycles, double cpuUsage, double ramUsage) {
    lock_guard<mutex> lock(mtx);
    this->numProcesses = numProcesses;
    this->diskSpacePercent = diskSpacePercent;
    this->processorCycles = processorCycles;
    this->cpuUsage = cpuUsage;
    this->ramUsage = ramUsage;
}

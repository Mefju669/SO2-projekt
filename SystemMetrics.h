#ifndef SYSTEM_METRICS_H
#define SYSTEM_METRICS_H

#include <mutex>
using namespace std;

class SystemMetrics {
public:
    int numProcesses;
    double diskSpacePercent;
    unsigned long long processorCycles;
    double cpuUsage;
    double ramUsage;


    SystemMetrics();


    void displayMetrics() const;

private:
    mutable mutex mtx;

    void updateMetrics(int numProcesses, double diskSpacePercent, unsigned long long processorCycles, double cpuUsage, double ramUsage);
};

#endif // SYSTEM_METRICS_H

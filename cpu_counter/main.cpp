#include <iostream>
#include <windows.h>
#include <Pdh.h>
#include <thread>
#include <chrono>
#include <mutex>

#pragma comment(lib, "pdh.lib")

std::mutex outputMutex;

double readCpuUsage() {
    PDH_HQUERY cpuQuery;
    PDH_HCOUNTER cpuTotal;

    PdhOpenQuery(NULL, NULL, &cpuQuery);
    PdhAddCounter(cpuQuery, "\\Processor(_Total)\\% Processor Time", NULL, &cpuTotal);
    PdhCollectQueryData(cpuQuery);
    Sleep(1000); // Wait for 1 second to get accurate readings
    PdhCollectQueryData(cpuQuery);

    PDH_FMT_COUNTERVALUE counterVal;
    PdhGetFormattedCounterValue(cpuTotal, PDH_FMT_DOUBLE, NULL, &counterVal);

    PdhCloseQuery(cpuQuery);

    return counterVal.doubleValue;
}

double readDiskUsage() {
    ULARGE_INTEGER freeBytesAvailable, totalNumberOfBytes, totalNumberOfFreeBytes;

    if (!GetDiskFreeSpaceEx(NULL, &freeBytesAvailable, &totalNumberOfBytes, &totalNumberOfFreeBytes)) {
        std::cerr << "Error getting disk usage\n";
        return -1.0;
    }

    double diskUsagePercent = ((totalNumberOfBytes.QuadPart - totalNumberOfFreeBytes.QuadPart) / (double)totalNumberOfBytes.QuadPart) * 100.0;
    return diskUsagePercent;
}

void cpuUsageThread() {
    while (true) {
        double cpuUsage = readCpuUsage();

        // Lock the mutex before printing CPU usage
        outputMutex.lock();
        std::cout << "CPU Usage: " << cpuUsage << "%" << std::endl;
        outputMutex.unlock();

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

void diskUsageThread() {
    while (true) {
        double diskUsage = readDiskUsage();

        // Lock the mutex before printing disk usage
        outputMutex.lock();
        std::cout << "Disk Usage: " << diskUsage << "%" << std::endl;
        outputMutex.unlock();

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

int main() {
    std::thread cpuThread(cpuUsageThread);
    std::thread diskThread(diskUsageThread);

    cpuThread.join();
    diskThread.join();

    return 0;
}

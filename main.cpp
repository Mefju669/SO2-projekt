#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include "RAMClass.h"
#include "DiskSpaceClass.h"
#include "StaticData.h"
#include "CPUClass.h"
#include "ReadingMethods.h"

using namespace std;

// Global mutexes to ensure thread-safe access to shared resources
mutex ramMutex;
mutex cpuMutex;
mutex diskSpaceMutex;
mutex staticDataMutex;

// Function to continuously monitor and record CPU usage
void monitorCPU(CPUClass& cpuClass, ReadingMethods& readingMethods) {
    while (true) {
        // Read the current CPU usage
        double CPUUsage = readingMethods.CountCPUUsage();

        // Safely add the CPU usage data to cpuClass
        {
            lock_guard<mutex> writeLock(cpuMutex);
            cpuClass.addData(CPUUsage);
        }

        // Sleep for 1 second before reading the CPU usage again
        this_thread::sleep_for(chrono::seconds(1));
    }
}

// Function to continuously monitor and record RAM usage
void monitorRAM(RAMClass& ramClass, ReadingMethods& readingMethods) {
    while (true) {
        // Read the current RAM usage
        double RAMUsage = readingMethods.CountRAMUsage();

        // Safely add the RAM usage data to ramClass
        {
            lock_guard<mutex> writeLock(ramMutex);
            ramClass.addData(RAMUsage);
        }

        // Sleep for 1 second before reading the RAM usage again
        this_thread::sleep_for(chrono::seconds(1));
    }
}

// Function to continuously monitor and record available disk space
void monitorDiskSpace(DiskSpaceClass& diskSpaceClass, ReadingMethods& readingMethods) {
    while (true) {
        // Read the current disk space usage
        double diskSpace = readingMethods.CountDiskSpace();

        // Safely add the disk space data to diskSpaceClass
        {
            lock_guard<mutex> writeLock(diskSpaceMutex);
            diskSpaceClass.addData(diskSpace);
        }

        // Sleep for 1 second before reading the disk space again
        this_thread::sleep_for(chrono::seconds(1));
    }
}

// Function to continuously monitor and record the number of processes
void monitorProcesses(StaticData& staticData, ReadingMethods& readingMethods) {
    while (true) {
        // Read the current number of processes
        int numProcesses = readingMethods.CountProcesses();

        // Safely update the number of processes in staticData
        {
            lock_guard<mutex> writeLock(staticDataMutex);
            staticData.numProcesses = numProcesses;
        }

        // Sleep for 1 second before reading the number of processes again
        this_thread::sleep_for(chrono::seconds(1));
    }
}

// Function to continuously monitor and record the number of CPU cycles
void monitorCycles(StaticData& staticData, ReadingMethods& readingMethods) {
    while (true) {
        // Read the current number of CPU cycles
        unsigned long long numCycles = readingMethods.CountCycles();

        // Safely update the number of CPU cycles in staticData
        {
            lock_guard<mutex> writeLock(staticDataMutex);
            staticData.numCycles = numCycles;
        }

        // Sleep for 1 second before reading the number of CPU cycles again
        this_thread::sleep_for(chrono::seconds(1));
    }
}

// Function to display the collected data from all monitored resources
void displayData(CPUClass& cpuClass, RAMClass& ramClass, DiskSpaceClass& diskSpaceClass, StaticData& staticData) {
    while (true) {
        // Display CPU usage data safely
        {
            lock_guard<mutex> readLock(cpuMutex);
            cpuClass.displayData();
        }

        // Display RAM usage data safely
        {
            lock_guard<mutex> readLock(ramMutex);
            ramClass.displayData();
        }

        // Display disk space data safely
        {
            lock_guard<mutex> readLock(diskSpaceMutex);
            diskSpaceClass.displayData();
        }

        // Display the number of processes and CPU cycles safely
        {
            lock_guard<mutex> readLock(staticDataMutex);
            cout << "Number of processes: " << staticData.numProcesses << endl;
            cout << "Number of CPU cycles: " << staticData.numCycles << endl;
        }

        // Sleep for 1 second before updating the display again
        this_thread::sleep_for(chrono::seconds(1));
    }
}

int main() {
    // Instantiate the classes that handle resource readings
    ReadingMethods readingMethods;
    CPUClass cpuClass;
    RAMClass ramClass;
    DiskSpaceClass diskSpaceClass;
    StaticData staticData;

    // Create threads to monitor different system resources concurrently
    thread cpuThread(monitorCPU, ref(cpuClass), ref(readingMethods));
    thread ramThread(monitorRAM, ref(ramClass), ref(readingMethods));
    thread diskSpaceThread(monitorDiskSpace, ref(diskSpaceClass), ref(readingMethods));
    thread processThread(monitorProcesses, ref(staticData), ref(readingMethods));
    thread cyclesThread(monitorCycles, ref(staticData), ref(readingMethods));
    thread displayThread(displayData, ref(cpuClass), ref(ramClass), ref(diskSpaceClass), ref(staticData));

    // Join the threads to ensure they complete execution
    cpuThread.join();
    ramThread.join();
    diskSpaceThread.join();
    processThread.join();
    cyclesThread.join();
    displayThread.join();

    return 0;
}

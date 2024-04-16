//
// Created by User on 13.04.2024.
//

#include "ReadingMethods.h"
#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>

double ReadingMethods::CountRAMUsage() {
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(memoryStatus);
    if (!GlobalMemoryStatusEx(&memoryStatus)) {
        return -1;
    }
    double ramUsage = 100.0 - ((double)memoryStatus.ullAvailPhys / (double)memoryStatus.ullTotalPhys * 100.0);
    return ramUsage;
}

double ReadingMethods::CountCPUUsage() {
    FILETIME idleTime, kernelTime, userTime;
    if (GetSystemTimes(&idleTime, &kernelTime, &userTime) == 0) {
        return -1;
    }
    Sleep(1000);
    FILETIME newIdleTime, newKernelTime, newUserTime;
    if (GetSystemTimes(&newIdleTime, &newKernelTime, &newUserTime) == 0) {
        return -1;
    }
    ULONGLONG oldIdle, newIdle, oldKernel, newKernel, oldUser, newUser;
    oldIdle = ((ULONGLONG)idleTime.dwHighDateTime << 32) | idleTime.dwLowDateTime;
    newIdle = ((ULONGLONG)newIdleTime.dwHighDateTime << 32) | newIdleTime.dwLowDateTime;
    oldKernel = ((ULONGLONG)kernelTime.dwHighDateTime << 32) | kernelTime.dwLowDateTime;
    newKernel = ((ULONGLONG)newKernelTime.dwHighDateTime << 32) | newKernelTime.dwLowDateTime;
    oldUser = ((ULONGLONG)userTime.dwHighDateTime << 32) | userTime.dwLowDateTime;
    newUser = ((ULONGLONG)newUserTime.dwHighDateTime << 32) | newUserTime.dwLowDateTime;
    ULONGLONG idleDelta = newIdle - oldIdle;
    ULONGLONG kernelDelta = newKernel - oldKernel;
    ULONGLONG userDelta = newUser - oldUser;
    ULONGLONG totalDelta = kernelDelta + userDelta;
    double cpuUsage = (totalDelta - idleDelta) * 100.0 / totalDelta;
    return cpuUsage;
}

unsigned long long ReadingMethods::CountCycles() {
    unsigned long long cycles = __rdtsc();
    return cycles;
}

double ReadingMethods::CountDiskSpace() {
    ULARGE_INTEGER freeBytesAvailable;
    ULARGE_INTEGER totalNumberOfBytes;
    ULARGE_INTEGER totalNumberOfFreeBytes;
    if (GetDiskFreeSpaceEx(NULL, &freeBytesAvailable, &totalNumberOfBytes, &totalNumberOfFreeBytes)) {
        double freeSpacePercent = (double)totalNumberOfFreeBytes.QuadPart / totalNumberOfBytes.QuadPart * 100;
        return freeSpacePercent;
    } else {
        return -1;
    }
}

int ReadingMethods::CountProcesses() {
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        return -1;
    }
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);
    if (!Process32First(hProcessSnap, &pe32)) {
        CloseHandle(hProcessSnap);
        return -1;
    }
    int numProcesses = 0;
    do {
        numProcesses++;
    } while (Process32Next(hProcessSnap, &pe32));
    CloseHandle(hProcessSnap);
    return numProcesses;
}
#ifndef READING_METHODS_H
#define READING_METHODS_H

class ReadingMethods {
public:
    // Deklaracje funkcji monitorujących zasoby
    int CountProcesses();
    double CountDiskSpace();
    unsigned long long CountCycles();
    double CountCPUUsage();
    double CountRAMUsage();
};

#endif // READING_METHODS_H

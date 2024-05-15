#ifndef CPUCLASS_H
#define CPUCLASS_H

#include <queue>
#include <iostream>

class CPUClass {
private:
    std::queue<double> CPUChart;
    const int maxSize = 10;

public:
    void addData(double newData);
    void displayData();
};

#endif // CPUCLASS_H

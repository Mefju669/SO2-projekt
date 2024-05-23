#ifndef CPUCLASS_H
#define CPUCLASS_H

#include <queue>
#include <vector>

class CPUClass {
private:
    std::queue<double> CPUChart;
    const int maxSize = 10;

public:
    void addData(double newData);
    std::vector<double> getData() const;
};

#endif // CPUCLASS_H



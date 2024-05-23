#include "CPUClass.h"

void CPUClass::addData(double newData) {
    if (CPUChart.size() >= maxSize) {
        CPUChart.pop();
    }
    CPUChart.push(newData);
}

std::vector<double> CPUClass::getData() const {
    std::vector<double> data;
    std::queue<double> tempQueue = CPUChart;

    while (!tempQueue.empty()) {
        data.push_back(tempQueue.front());
        tempQueue.pop();
    }

    return data;
}

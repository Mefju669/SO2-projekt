#include "DiskSpaceClass.h"

void DiskSpaceClass::addData(double newData) {
    if (diskSpaceChart.size() >= maxSize) {
        diskSpaceChart.pop();
    }
    diskSpaceChart.push(newData);
}

std::vector<double> DiskSpaceClass::getData() const {
    std::vector<double> data;
    std::queue<double> tempQueue = diskSpaceChart;

    while (!tempQueue.empty()) {
        data.push_back(tempQueue.front());
        tempQueue.pop();
    }

    return data;
}

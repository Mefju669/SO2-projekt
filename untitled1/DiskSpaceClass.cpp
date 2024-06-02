#include "DiskSpaceClass.h"

// Adds new disk space usage data to the chart, maintaining a maximum size
void DiskSpaceClass::addData(double newData) {
    // If the chart has reached its maximum size, remove the oldest data
    if (diskSpaceChart.size() >= maxSize) {
        diskSpaceChart.pop();
    }
    // Add the new data to the chart
    diskSpaceChart.push(newData);
}

// Retrieves all disk space usage data as a vector
std::vector<double> DiskSpaceClass::getData() const {
    std::vector<double> data;
    std::queue<double> tempQueue = diskSpaceChart; // Create a copy of the queue

    // Transfer data from the queue to the vector
    while (!tempQueue.empty()) {
        data.push_back(tempQueue.front());
        tempQueue.pop();
    }

    return data;
}

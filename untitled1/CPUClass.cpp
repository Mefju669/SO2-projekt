#include "CPUClass.h"

// Adds new CPU usage data to the chart, maintaining a maximum size
void CPUClass::addData(double newData) {
    // If the chart has reached its maximum size, remove the oldest data
    if (CPUChart.size() >= maxSize) {
        CPUChart.pop();
    }
    // Add the new data to the chart
    CPUChart.push(newData);
}

// Retrieves all CPU usage data as a vector
std::vector<double> CPUClass::getData() const {
    std::vector<double> data;
    std::queue<double> tempQueue = CPUChart; // Create a copy of the queue

    // Transfer data from the queue to the vector
    while (!tempQueue.empty()) {
        data.push_back(tempQueue.front());
        tempQueue.pop();
    }

    return data;
}

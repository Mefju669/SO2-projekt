#include "CPUClass.h"

using namespace std;

// Method to add new CPU usage data to the queue
void CPUClass::addData(double newData) {
    // Add new data to the queue
    CPUChart.push(newData);

    // Remove the oldest data if the queue exceeds the maximum size
    if (CPUChart.size() > maxSize) {
        CPUChart.pop();
    }
}

// Method to display the CPU usage data
void CPUClass::displayData() {
    // Create a copy of the queue to avoid modifying the original
    std::queue<double> tempQueue = CPUChart;

    cout << "CPU Usage: ";
    // Iterate through the copied queue and display each data point
    while (!tempQueue.empty()) {
        std::cout << tempQueue.front() << "%" << " "; // Display the front element of the queue
        tempQueue.pop(); // Remove the displayed element from the queue
    }
    std::cout << std::endl;
}

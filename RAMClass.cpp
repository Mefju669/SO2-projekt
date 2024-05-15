#include "RAMClass.h"

using namespace std;

// Method to add new RAM usage data to the queue
void RAMClass::addData(double newData) {
    // Add new data to the queue
    RAMChart.push(newData);

    // Remove the oldest data if the queue exceeds the maximum size
    if (RAMChart.size() > maxSize) {
        RAMChart.pop();
    }
}

// Method to display the RAM usage data
void RAMClass::displayData() {
    // Create a copy of the queue to avoid modifying the original
    std::queue<double> tempQueue = RAMChart;

    cout << "RAM Usage: ";
    // Iterate through the copied queue and display each data point
    while (!tempQueue.empty()) {
        std::cout << tempQueue.front() << "%" << " "; // Display the front element of the queue
        tempQueue.pop(); // Remove the displayed element from the queue
    }
    std::cout << std::endl;
}

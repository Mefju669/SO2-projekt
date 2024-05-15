#include "DiskSpaceClass.h"

using namespace std;

// Method to add new disk space usage data to the queue
void DiskSpaceClass::addData(double newData) {
    // Add new data to the queue
    diskSpaceChart.push(newData);

    // Remove the oldest data if the queue exceeds the maximum size
    if (diskSpaceChart.size() > maxSize) {
        diskSpaceChart.pop();
    }
}

// Method to display the disk space usage data
void DiskSpaceClass::displayData() {
    // Create a copy of the queue to avoid modifying the original
    std::queue<double> tempQueue = diskSpaceChart;

    cout << "Disk Space Usage on Drive C: ";
    // Iterate through the copied queue and display each data point
    while (!tempQueue.empty()) {
        std::cout << tempQueue.front() << "%" << " "; // Display the front element of the queue
        tempQueue.pop(); // Remove the displayed element from the queue
    }
    std::cout << std::endl;
}

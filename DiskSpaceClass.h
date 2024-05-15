#ifndef DISKSPACECLASS_H
#define DISKSPACECLASS_H

#include <queue>
#include <iostream>

class DiskSpaceClass {
private:
    std::queue<double> diskSpaceChart;
    const int maxSize = 10;

public:
    void addData(double newData);
    void displayData();
};

#endif // DISKSPACECLASS_H

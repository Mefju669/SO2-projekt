#ifndef RAMCLASS_H
#define RAMCLASS_H

#include <queue>
#include <iostream>

class RAMClass {
private:
    std::queue<double> RAMChart;
    const int maxSize = 10;

public:
    void addData(double newData);
    void displayData();
};

#endif // RAMCLASS_H

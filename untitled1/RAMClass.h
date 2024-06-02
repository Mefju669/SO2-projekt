#ifndef RAMCLASS_H
#define RAMCLASS_H

#include <queue>
#include <vector>


class RAMClass {
private:
    std::queue<double> RAMChart;
    const int maxSize = 10;

public:
    void addData(double newData);
    void displayData() const;
};

#endif // RAMCLASS_H

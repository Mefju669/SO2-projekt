#ifndef DISKSPACECLASS_H
#define DISKSPACECLASS_H

#include <queue>
#include <vector>

class DiskSpaceClass {
private:
    std::queue<double> diskSpaceChart;
    const int maxSize = 10;

public:
    void addData(double newData);
    std::vector<double> getData() const;
};

#endif // DISKSPACECLASS_H

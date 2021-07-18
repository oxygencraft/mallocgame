#pragma once

#include <vector>
#include "data.h"

class DataAllocationManager {
public:
    void Update();
    void AddData(Data& data);
    void AccessData(Data& data);
private:
    struct DataInfo {
        DataInfo(Data &data, int garbageCount);

        Data* data;
        double nextAccess;
        double accessTimeout;
        int accessedCount;
        int garbageCount;
    };
    std::vector<DataInfo> dataList;
    static double GetNextAccessTime();
};

#include "dataallocationmanager.h"

void DataAllocationManager::Update() {
    for (auto& data : dataList) {
        if (data.nextAccess >= GetTime()) {
            // TODO: Implement robot system and send robot to collect data
            // I don't feel like implementing the robot system right now
            // so I will just have it randomly decide to access the data or not
            if (GetRandomValue(0, 2) >= 1)
                AccessData(*data.data);

            data.accessTimeout = GetTime() + GetRandomValue(5, 10);
        }

        if (data.accessTimeout != 0 && data.accessTimeout >= GetNextAccessTime()) {
            AccessData(*data.data);
            // TODO: Add instability
        }
    }
}

void DataAllocationManager::AccessData(Data &data) {
    for (int i = 0; i < dataList.size(); ++i) {
        DataInfo& currentData = dataList[i];
        if (&data == currentData.data) {
            currentData.nextAccess = GetNextAccessTime();
            currentData.accessTimeout = 0;
            currentData.accessedCount++;

            if (currentData.accessedCount == currentData.garbageCount)
                dataList.erase(dataList.begin() + i);

            break;
        }
    }
}

void DataAllocationManager::AddData(Data& data) {
    dataList.emplace_back(data, GetRandomValue(1, 12));
}

double DataAllocationManager::GetNextAccessTime() {
    return GetTime() + GetRandomValue(2, 14);
}

DataAllocationManager::DataInfo::DataInfo(Data &data, int garbageCount) : data(&data), garbageCount(garbageCount) {
    nextAccess = GetNextAccessTime();
    accessedCount = 0;
    accessTimeout = 0;
}

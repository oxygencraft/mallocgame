#pragma once

#include <vector>
#include "data.h"
#include "grid.h"
#include "dataallocationmanager.h"

class DataBufferManager {
public:
    DataBufferManager(double spawnRate, Grid& bufferGrid, DataAllocationManager& dataAllocationManager,
                      Texture2D blueTileTexture, Texture2D yellowTileTexture, Texture2D redTileTexture);
    void Update();
    const std::vector<Data*>& GetQueuedData();
private:
    void NextCurrentData();
    void GenerateData();
    double spawnRate = 4;
    double nextSpawnTime = 0;
    bool hasResizedToEmptyGrid = false;
    Grid* bufferGrid;
    DataAllocationManager* allocationManager;
    std::vector<Data*> queuedData;
    Texture2D blueTileTexture;
    Texture2D yellowTileTexture;
    Texture2D redTileTexture;
};

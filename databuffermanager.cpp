#include "databuffermanager.h"
#include "emptycell.h"

void DataBufferManager::Update() {
    if (GetTime() >= nextSpawnTime) {
        GenerateData();
        nextSpawnTime += spawnRate;
    }

    bool hasCurrentDataMoved = true;
    for (int i = 0; i < bufferGrid->GetCellNumX(); ++i) {
        if (!dynamic_cast<EmptyCell*>(&bufferGrid->GetCell(i, 0))) {
            hasCurrentDataMoved = false;
            break;
        }
    }

    if (hasCurrentDataMoved) {
        NextCurrentData();
    }
}

void DataBufferManager::NextCurrentData() {
    // The most important data should be the next data
    // If there are multiple most important data with the same value, the smallest data is to be chosen
    // If they are the same size, any can be chosen

    // If there is no queue data, just set the buffer grid size to 0,0
    if (queuedData.empty()) {
        if (!hasResizedToEmptyGrid)
            bufferGrid->ResizeGrid(0, 0);
        hasResizedToEmptyGrid = true;
        return;
    }

    int highestImportance = 0;
    std::vector<int> highestImportanceIndexes;

    for (int i = 0; i < queuedData.size(); ++i) {
        if (queuedData[i]->importance > highestImportance) {
            highestImportance = queuedData[i]->importance;
            highestImportanceIndexes.clear();
            highestImportanceIndexes.push_back(i);
        } else if (queuedData[i]->importance == highestImportance) {
            highestImportanceIndexes.push_back(i);
        }
    }

    int lowestSize = 99999;
    int lowestSizeIndex = 0;
    for (int i = 0; i < highestImportanceIndexes.size(); ++i) {
        if (queuedData[highestImportanceIndexes[i]]->cells.size() < lowestSize) {
            lowestSizeIndex = highestImportanceIndexes[i];
            lowestSize = queuedData[highestImportanceIndexes[i]]->cells.size();
        }
    }

    Data* data = queuedData[lowestSizeIndex];
    queuedData.erase(queuedData.begin() + lowestSizeIndex);

    bufferGrid->ResizeGrid(data->cells.size(), 1);
    for (int i = 0; i < data->cells.size(); ++i) {
        bufferGrid->SetCell(i, 0, data->cells[i]);
    }

    hasResizedToEmptyGrid = false;
}

void DataBufferManager::GenerateData() {
    int importance = GetRandomValue(0, 100);
    int size = GetRandomValue(1, 6);
    Data* data = new Data { importance };

    Texture2D cellTexture;
    if (importance > 50)
        cellTexture = redTileTexture;
    else if (importance > 20)
        cellTexture = yellowTileTexture;
    else
        cellTexture = blueTileTexture;

    for (int i = 0; i < size; ++i) {
        data->cells.emplace_back(cellTexture, data, i);
    }

    queuedData.push_back(data);
    allocationManager->AddData(*data);
}

const std::vector<Data*>& DataBufferManager::GetQueuedData() {
    return queuedData;
}

DataBufferManager::DataBufferManager(double spawnRate, Grid& bufferGrid, DataAllocationManager& dataAllocationManager,
                                     Texture2D blueTileTexture, Texture2D yellowTileTexture, Texture2D redTileTexture)
                         : spawnRate(spawnRate), bufferGrid(&bufferGrid), allocationManager(&dataAllocationManager),
                           blueTileTexture(blueTileTexture), yellowTileTexture(yellowTileTexture), redTileTexture(redTileTexture)
                           {}

#ifndef MALLOCGAME_DATABUFFERMANAGER_H
#define MALLOCGAME_DATABUFFERMANAGER_H


#include <vector>
#include "data.h"
#include "grid.h"

class DataBufferManager {
    public:
        DataBufferManager(double spawnRate, Grid& bufferGrid,
                          Texture2D blueTileTexture, Texture2D yellowTileTexture, Texture2D redTileTexture);
        void Update();
        const std::vector<Data>& GetQueuedData();
        void MoveCurrentData();
    private:
        void NextCurrentData();
        void GenerateData();
        double spawnRate = 8;
        double nextSpawnTime;
        bool hasCurrentDataMoved = true;
        bool hasResizedToEmptyGrid = false;
        Grid* bufferGrid;
        std::vector<Data> queuedData;
        Texture2D blueTileTexture;
        Texture2D yellowTileTexture;
        Texture2D redTileTexture;
};


#endif //MALLOCGAME_DATABUFFERMANAGER_H
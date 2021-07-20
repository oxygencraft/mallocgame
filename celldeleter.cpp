#include "celldeleter.h"
#include "datacell.h"
#include "data.h"

void CellDeleter::Update() {
    // If necessary, convert mouse position upscaled position (window size) to normal position (render size)
    int mousePositionX = GetMouseX() / 2;
    int mousePositionY = GetMouseY() / 2;

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        int buttonSizeX = texture.width + position.x;
        int buttonSizeY = texture.height + position.y;

        if (position.x < mousePositionX && buttonSizeX > position.x && position.y < mousePositionY && buttonSizeY > mousePositionY) {
            isDeleting = !isDeleting;
        }

        if (!isDeleting) {
            return;
        }

        Grid* grid = GetGridFromPosition(mousePositionX, mousePositionY, grids);
        if (grid != nullptr) {
            Cell& cell = grid->GetCellFromScreenPosition(mousePositionX - grid->position.x,
                                                         mousePositionY - grid->position.y);
            DataCell* dataCell = dynamic_cast<DataCell*>(&cell);
            if (dataCell) {
                int originalPositionX = dataCell->GetGridPosition().x;
                int originalPositionY = dataCell->GetGridPosition().y;

                Data* originalData = &dataCell->GetDataOwner();
                int currentDataIndex = dataCell->GetIndex();

                for (int i = originalPositionX; i < grid->GetCellNumX(); ++i) {
                    DataCell* currentDataCell = dynamic_cast<DataCell*>(&grid->GetCell(i, originalPositionY));
                    if (!currentDataCell)
                        break;

                    Data& data = currentDataCell->GetDataOwner();
                    if (currentDataCell->GetIndex() != currentDataIndex || &data != originalData)
                        break;

                    grid->SetEmptyCell(i, originalPositionY);

                    std::vector<DataCell*>& dataCellList = currentDataCell->GetDataOwner().cells;
                    int dataListIndex = GetDataCellListIndex(currentDataIndex, data);

                    delete dataCellList[dataListIndex];
                    dataCellList[dataListIndex] = nullptr;

                    currentDataIndex++;
                    if (dataCellList.empty())
                        delete &currentDataCell->GetDataOwner();
                }
            }
        }
    }
}

Texture2D CellDeleter::Draw() {
    if (isDeleting)
        return enabledTexture;
    else
        return texture;
}

Object& CellDeleter::Clone() {
    // Why would anyone do this?
    return *(new CellDeleter(*this));
}

CellDeleter::CellDeleter(std::vector<Grid*> grids, Vector2 position, Texture2D buttonTexture, Texture2D buttonEnabledTexture)  {
    this->grids = grids;
    this->position = position;
    this->texture = buttonTexture;
    this->enabledTexture = buttonEnabledTexture;
}

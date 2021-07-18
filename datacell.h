#pragma once

#include "texturecell.h"

struct Data;

class DataCell : public TextureCell {
public:
    DataCell(Texture2D texture, Data* data, int index);
    void Update() override;
    DataCell& Clone() override;
    Data& GetDataOwner();
    int GetIndex();
private:
    Data* dataOwner;
    int index;
};

#include "datacell.h"

void DataCell::Update() {

}

DataCell& DataCell::Clone() {
    // Why would anyone clone this?
    const Texture2D texture = GetTexture();
    return *(new DataCell(texture, dataOwner, index));
}

Data& DataCell::GetDataOwner() {
    return dataOwner;
}

int DataCell::GetIndex() {
    return index;
}

DataCell::DataCell(Texture2D texture, Data& owner, int index) : TextureCell(texture), dataOwner(owner), index(index) {

}

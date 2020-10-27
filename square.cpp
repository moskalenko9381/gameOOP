#include "square.h"


Type Square::getType(){
    return type;
}

void Square::setType(Type type, CellObject* obj){
    this->type = type;
    object = obj;
}


void Square::setDestroyed(){
    type = CLOSE;
}

Coords Square::getCoords(){
    return coords;
}

void Square::setH(int h){
    coords.h = h;
}
void Square::setW(int w){
    coords.w = w;
}

CellObject* Square::getObject(){
    return object;
}

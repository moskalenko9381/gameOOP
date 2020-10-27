#ifndef SQUARE_H
#define SQUARE_H
#include <QGraphicsRectItem>
#include "coords.h"
#include "wallobject.h"
#include "exitobject.h"
#include "coinObject.h"
#include "vortexobject.h"

class CellObject;

enum Type{
    CLOSE, //0 (WALL)
    OPEN,  //1
    ENTRY, //2
    EXIT,//3
    COINS, //4
    PLAYER, //5
    VORTEX
};

class Square
{
  //  Q_OBJECT
    Type type;
    Coords coords;
    CellObject* object;

public:
     Square(Type type = CLOSE, CellObject* object = nullptr):type(type), object(object){};
     void setType(Type type, CellObject* obj = nullptr);

     Type getType();
     void setDestroyed();

     Coords getCoords();
     CellObject* getObject();


     void setH(int h);
     void setW(int w);
};

#endif // SQUARE_H

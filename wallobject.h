#ifndef WALLOBJECT_H
#define WALLOBJECT_H
#include "cellobject.h"
class WallObject: public CellObject
{
public:
    WallObject();
    bool action(Player* player);
};

#endif // WALLOBJECT_H

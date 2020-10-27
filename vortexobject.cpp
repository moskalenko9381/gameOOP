#include "vortexobject.h"
#include <stdlib.h>
#include <ctime>
#include <random>

VortexObject::VortexObject(){}

bool VortexObject::action(Player* player){
     srand(time(0));
      int a = rand() % 4 ;
    Coords c;
    switch(a){
    case 0:
        c = {3,6};
    case 1:
        c = {5,7};
    case 2:
        c = {7,10};
    case 3:
        c = {9,10};
    }
    player->setCoords(c);
    return true;
}


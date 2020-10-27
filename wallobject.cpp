#include "wallobject.h"

WallObject::WallObject(){}

bool WallObject::action(Player* player){
    player->minusLive();
    return false;
}

#include "coinObject.h"

coinObject::coinObject(){}

bool coinObject::action(Player* player){
    player->addCoin();
    return true;
}

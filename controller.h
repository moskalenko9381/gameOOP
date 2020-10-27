#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "field.h"
#include "player.h"
#include "loggerholder.h"

class Controller
{
    Player player;
    Field* field;
   // LoggerHolder* logs;
public:
    Controller(Player player, Field* field);
    Coords controlMovePlayer(Dir direction);
    Coords getPlayerCoords();
    int controlLivesPlayer();
    int controlCoinsPlayer();
    bool playerWin();

    void minusLivePlayer(int size = 1);
    void connectObject(CellObject* obj);
    bool checkCell(Coords coords, Dir direction);
    CellObject* getCellObject(Coords coords);

    const std::string cellInfo(Type type);

};

#endif // CONTROLLER_H

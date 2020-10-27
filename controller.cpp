#include "controller.h"
#define COIN 3

Controller::Controller(Player player, Field* field){
    this->player = player;
    this->field = field;
    LoggerHolder::init(new FileLogger("Users/elizaveta/Desktop/logggs.txt"));
    LoggerHolder::instance().pushLog(new ConsoleLogger);
}

const std::string Controller::cellInfo(Type type){
    switch(type){
    case CLOSE:
        return "MET A WALL. -2 LIVES\n";
        break;
    case EXIT:
        return "EXIT IS CLOSED. -2 LIVES\n";
        break;
    case VORTEX:
        return "WOW! MET A VORTEX!\n";
        break;
    default:
        return "";
    }
}

Coords Controller::controlMovePlayer(Dir direction){
    if (!(checkCell(player.getCoords(), direction)))
            return player.getCoords();

    Coords newCoords = player.movePlayer(direction);

    player += field->field[newCoords.h][newCoords.w].getObject();

    Type type = field->field[newCoords.h][newCoords.w].getType();

    LoggerHolder::instance() << cellInfo(type);

    if (type == CLOSE)
            return player.getCoords();

    if (type == EXIT && !player.isWinner())
            return player.getCoords();

    if (type == VORTEX)
              return player.getCoords();

    if (player.getCoords().h != newCoords.h || player.getCoords().w != newCoords.w){
             Coords old = player.getCoords();
             player.setCoords(newCoords);
             field->field[newCoords.h][newCoords.w].setType(PLAYER,nullptr);
             field->field[old.h][old.w].setType(OPEN,nullptr);
    }
     LoggerHolder::instance() << player.toString();
    return player.getCoords();
}



int Controller::controlLivesPlayer(){
    return player.getLives();
}

int Controller::controlCoinsPlayer(){
    return player.getCoins();
}

Coords Controller::getPlayerCoords(){
    return player.getCoords();
}

bool Controller::playerWin(){
    return player.isWinner();
}

void Controller::minusLivePlayer(int size){
     player.minusLive(size);
}

void Controller::connectObject(CellObject* obj){
    player += obj;
}


bool Controller::checkCell(Coords coords, Dir direction){
    int y = coords.h;
    int x = coords.w;
    switch(direction){
        case UP:
            return y != 0;
        case DOWN:
            return !(y +1 >= HEIGHT);
        case LEFT:
             return !(x == 0);
        case RIGHT:
            return !(x +1 >= WIDTH);
    }
}

CellObject* Controller::getCellObject(Coords coords){
    return field->field[coords.h][coords.w].getObject();
}

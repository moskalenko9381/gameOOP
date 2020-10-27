#ifndef PLAYER_H
#define PLAYER_H
#include "direction.h"
#include "coords.h"
#include <string>

class CellObject;

class Player
{
    int coins;
    int lives;
    bool win;
    Coords coords;

public:
    Player();
    Player& operator+=(CellObject* object);
    bool isWinner();

    void setCoords(Coords c);

    void addCoin(int size = 1);
    void makeWinner(bool t);
    void minusLive(int size = 1);

    int getLives();
    int getCoins();

    Coords movePlayer(Dir direction);
    Coords getCoords();

    const std::string toString();
    //friend std::ostream& operator<<(std::ostream &output, Player &player);
};

#endif // PLAYER_H

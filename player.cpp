#include "player.h"
#include "field.h"

Player::Player():coins(0),lives(10),win(false),coords{0,0}{}

void Player::setCoords(Coords c){
    coords.h = c.h;
    coords.w = c.w;
}

Coords Player::movePlayer(Dir direction){
    Coords c;
    c.h = coords.h;
    c.w = coords.w;
    switch(direction){
    case UP:
            c.h -=1;
            break;
    case DOWN:
            c.h +=1;
        break;
    case LEFT:
            c.w -=1;
         break;
    case RIGHT:
            c.w +=1;
        break;
      }
   return c;
  }


void Player::addCoin(int size){
    coins += size;
}

bool Player::isWinner(){
    return win;
}

void Player::makeWinner(bool t){
    win = t;
}

void Player::minusLive(int size){
    lives -= size;
}

int Player::getLives(){
    return lives;
}

int Player::getCoins(){
    return coins;
}

Coords Player::getCoords(){
    return coords;
}

Player& Player::operator+=(CellObject* object){
    if (!object)
        return (*this);
    object->action(this);
    return *this;
}


const std::string Player::toString() {
    return  "PLAYER: Coords: " + std::to_string(coords.h) + " ," + std::to_string(coords.w)+ "\n" +
            "        Coins: " +  std::to_string(coins) + "\n" +
            "        Lives: " +  std::to_string(lives) + "\n" +
            "        Win: " + (win ? "true" : "false") + "\n";
}


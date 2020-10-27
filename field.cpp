#include "field.h"

Field *Field::uniqueInstance = nullptr;
SingletonDestroyer Field::destroyer;
const int maxHeight = HEIGHT;
const int maxWidth = WIDTH;
Field::Field() {
    field = nullptr;
}

SingletonDestroyer::~SingletonDestroyer() {
    delete uniqueInstance;
}

void SingletonDestroyer::initialize(Field* p ) {
    uniqueInstance = p;
}

Field& Field::getInstance(int height,int width) {
    if(!uniqueInstance)     {
        uniqueInstance = new Field(height,width);
        destroyer.initialize(uniqueInstance);
    }
    return *uniqueInstance;
}

Field::Field(int height, int width)
{
    this->height = height;
    this->width = width;
    field = new Square*[HEIGHT];

    for (auto i = 0; i < HEIGHT; i++)
        field[i] = new Square[WIDTH];
}


Field::~Field(){
    for (auto i = 0; i < HEIGHT; i++)
       delete[] field[i];
    delete [] field;
}


void Field::makeField(){
    for(auto i = 0; i < height; i++){
            for(auto j = 0; j < width; j++){

                field[i][j].setH(i);


                if((i % 2 != 0 && j % 2 != 0) &&
                    (i < height-1 && j < width-1))
                       field[i][j].setType(CLOSE, new WallObject());


                else field[i][j].setType(OPEN);

                field[i][j].setW(j);
           }
        }
    field[0][0].setType(ENTRY);
    field[HEIGHT-1][WIDTH-1].setType(EXIT, new ExitObject());
    field[HEIGHT/2][WIDTH/2 +1].setType(COINS, new coinObject());
    field[HEIGHT/4 + 1][WIDTH/4].setType(COINS, new coinObject());
    field[HEIGHT - 3][WIDTH/2].setType(COINS, new coinObject());
    field[HEIGHT - 5][WIDTH/3].setType(VORTEX, new VortexObject());
}


Field::Field(const Field& obj){            //конструктор копирования
    height = obj.height;
    width = obj.width;
    field = new Square*[height];
    for (auto i = 0; i < height; i++){
        field[i] = new Square[width];
        for (auto j = 0; j < width; j++)
            field[i][j] = obj.field[i][j];
    }
}

Field::Field(Field&& obj): height(obj.height), width(obj.width){
    field = obj.field;            //конструктор перемещения
    obj.height = 0;
    obj.width = 0;
    obj.field = nullptr;
}

Field &Field::operator=(Field const& obj){  //оператор присваивания копированием
    if (this != &obj)
        for (auto i = 0; i < height; i++)
            delete [] field[i];
    delete []field;
    height = obj.height;
    width = obj.width;
    field = new Square*[height];
    for (auto i = 0; i < height; i++){
        field[i] = new Square[width];
        for (auto j = 0; j < width; j++)
            field[i][j] = obj.field[i][j];
    }
    return *this;
}


Field& Field::operator=(Field&& obj){  //оператор присваивания перемещением
   if (&obj == this)
    return *this;
   std::swap(height, obj.height);
   std::swap(width, obj.width);
   std::swap(field, obj.field);
   return *this;
}


Field::Iterator::Iterator(int nowH, int nowW){
    currentHeight = nowH;
    currentWidth = nowW;
}

Field::Iterator Field::begin(){
    return Iterator(0,0);
}

Field::Iterator Field::end(){
    return Iterator(maxHeight, 0);
}

Square& Field::Iterator::operator*() {
    return Field::getInstance().field[currentHeight][currentWidth];
}

Field::Iterator& Field::Iterator::operator++(){
    if (currentWidth +1 == maxWidth) {
        currentHeight++;
        currentWidth = 0;
    } else
        currentWidth++;
    return *this;
}

Field::Iterator Field::Iterator::operator++(int){
    Iterator iterator(*this);
    operator++();
    return iterator;
}

bool Field::Iterator::operator==(const Iterator& other) {
    return (currentWidth == other.currentWidth && currentHeight == other.currentHeight);
}

bool Field::Iterator::operator!=(const Iterator& other) {
    return !operator==(other);
}

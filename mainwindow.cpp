#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsRectItem>
#include <QDesktopWidget>
#include <QMessageBox>
#include "direction.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    field = &Field::getInstance(HEIGHT,WIDTH);
    player = Player();
   // logs = LoggerHolder();
    //logs.pushLog(new ConsoleLogger());
    playerControl = new Controller(player,field);
    field->makeField();
    makeScene();
   }

void MainWindow::makeScene(){
    scene = new QGraphicsScene();
    screenSize = QDesktopWidget().availableGeometry(this).size();
    setFixedSize(screenSize);
    ui->graphicsView->setFixedSize(screenSize);
    makeRects();
    ui->graphicsView->setScene(scene);
}

void MainWindow::makeRects(){
    int rectHeight = screenSize.height()*0.8/HEIGHT;
    int rectWidth = screenSize.width()*0.8/WIDTH;
    rects = new QGraphicsRectItem** [HEIGHT];

    for (auto i = 0; i < HEIGHT; i++)
        rects[i] = new QGraphicsRectItem*[WIDTH];

       for(Square square : *field){ //ITERATOR
           Coords c = square.getCoords();
           auto i = c.h;
           auto j = c.w;
           rects[i][j] = scene->addRect(QRectF(i*rectWidth, j*rectHeight, rectWidth, rectHeight));

           Type cell = field->field[j][i].getType();
           QBrush brush = getBrush(cell);
           rects[i][j]->setBrush(brush);
            }
 }



QBrush MainWindow::getBrush(Type type){
    int rectHeight = screenSize.height()*0.8/HEIGHT;
    int rectWidth = screenSize.width()*0.8/WIDTH;
    switch(type){
    case ENTRY:
             return (QBrush(QImage(":/new/open.jpg").scaled(rectWidth,rectHeight,Qt :: IgnoreAspectRatio ,Qt::SmoothTransformation)));
             break;
    case CLOSE:
              return (QBrush(QImage(":/new/rock.png").scaled(rectWidth,rectHeight,Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
             break;
    case EXIT:
             return (QBrush(QImage(":/new/doors.jpg").scaled(rectWidth,rectHeight,Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
             break;
    case OPEN:
            return (QBrush(Qt::gray));
            break;
    case COINS:
            return (QBrush(QImage(":/new/coin.png").scaled(rectWidth,rectHeight,Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
            break;
    case PLAYER:
            return (QBrush(QImage(":/new/rat.jpg").scaled(rectWidth,rectHeight,Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
            break;
    case VORTEX:
            return (QBrush(QImage(":/new/vortex.png").scaled(rectWidth,rectHeight,Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
            break;
        }
}



void MainWindow::keyPressEvent(QKeyEvent* event){
     int oldCoin = playerControl->controlCoinsPlayer();

     if (playerControl->playerWin()){
          QMessageBox::information(this, "Game over", "You won! Please start new game.");
          return;
     }

     if (playerControl->controlLivesPlayer() == 0){
             QMessageBox::warning(this, "OOPS", "GAME OVER. YOU LOST.");
             return;
     }


     playerCoords = playerControl->getPlayerCoords();

     switch(event->key()){

         case Qt::Key_W:
             newCoords = playerControl->controlMovePlayer(UP);
             break;

         case Qt::Key_A:
             newCoords = playerControl->controlMovePlayer(LEFT);
         break;

        case Qt::Key_S:
             newCoords = playerControl->controlMovePlayer(DOWN);
         break;

         case Qt::Key_D:
             newCoords = playerControl->controlMovePlayer(RIGHT);
         break;

        default:
            return;
     }


      rects[newCoords.w][newCoords.h]->setBrush(getBrush(PLAYER));

      if (playerCoords.w != newCoords.w || playerCoords.h != newCoords.h )
         rects[playerCoords.w][playerCoords.h]->setBrush(getBrush(OPEN));
      else{
          playerControl->minusLivePlayer();
          QMessageBox::information(this, "MISTAKE. THERE IS A WALL", "YOUR LIVES: " + QString::number(playerControl->controlLivesPlayer()) + "/10");
      }


      if (oldCoin != playerControl->controlCoinsPlayer())
              QMessageBox::information(this, "YOU GOT A COIN!", "COIN " + QString::number(playerControl->controlCoinsPlayer()) + "/3");

     if (playerControl->playerWin()){
         QMessageBox::information(this, "Game over", "You won! Please start new game.");
         return;
     }
}



MainWindow::~MainWindow()
{
    delete ui;
}

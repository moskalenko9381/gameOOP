#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QGraphicsScene>
#include <QMainWindow>
#include <QKeyEvent>
#include "field.h"
#include "controller.h"
#include "loggerholder.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
   void keyPressEvent(QKeyEvent* event);
private:

    QSize screenSize;
    Ui::MainWindow *ui;
    QGraphicsScene* scene;

    Field* field;
    Controller* playerControl;
    LoggerHolder logs;
    FileLogger* file;
    Player player;

    QGraphicsRectItem*** rects;
    QBrush getBrush(Type type);

    void eventsCheck(Dir direction);
    void makeRects();
    void makeScene();

    Coords playerCoords;
    Coords newCoords;
};
#endif // MAINWINDOW_H


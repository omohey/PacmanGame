#ifndef GHOST_H
#define GHOST_H
#include <iostream>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QKeyEvent>
#include <QList>
#include <QGraphicsScene>
#include <cstdlib>
#include <ctime>
#include "pacman.h"
#include <QTimer>

#include <QObject>
using namespace std;
const int Infinity = 9999;
enum ghosttype{Slow, Medium, Fast};
class ghost : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int row;
    int col;
    QString k;          //the movement of the ghost up/down/right/left
    int max;
    int** matrix;
    int pacrow, paccol;
    vector<vector<int>> Dijkstra(int startNode);
    ghosttype type;
    bool stop;
    QTimer *timer;
protected:
    void advance(int phase);
public:
    ghost(QPixmap&, int, int);
    void setrow(int);
    void setcolumn (int);
    int getcolumn();
    int getrow();
    void moveRandomly();    //changes the private variable k to up/down/right/left randomly
    //void getpac(Pacman*);
    int num;
    void stopghost();
public slots:
    void moveghost();

};
#endif // GHOST_H

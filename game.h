#ifndef GAME_H
#define GAME_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include "pacman.h"
#include "lives.h"
#include <score.h>
#include "pellets.h"
#include "superpellets.h"
#include "ghost.h"
#include <QMediaPlayer>
#include "fruit.h"
class Game: public QGraphicsView
{
    Q_OBJECT
public:
    Game();
    QGraphicsScene *scene;
    int boardData[31][28];
    Lives *lives;
    QVector<QGraphicsPixmapItem*> *vec;
    Score *score;
    pellets *pellet[31][28];
    superPellets *super[4];
    ghost *ghosts[3];
    Pacman *pacman;
    void deletelife();
    void initializeghosts();
    void starttimer();
    QTimer *fruittimer, *fruittimer2;
    QMediaPlayer *player;
    Fruit *fruit;
    QVector<int> rowsvec, colsvec;
public slots:
    void createfruit();
    void destroyfruit();
};

#endif // GAME_H

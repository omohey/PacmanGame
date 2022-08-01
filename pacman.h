#ifndef PACMAN_H
#define PACMAN_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include<QKeyEvent>
#include <QList>
#include "pellets.h"
#include <QGraphicsScene>
#include "superpellets.h"
#include <QDialog>
#include <QtGui>
#include <QtCore>
#include <QMessageBox>
#include <QSound>
class ghost;
class Pacman : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int row;
    int col;
    QString k;      //current key that was entered on key
    QString kprev;      //the key entered before in case the key entered is not possible to move to we will move in the previous direction then switch whenever its possible
    QGraphicsTextItem Win;      //Text item will display message if user wins or loses
    bool win;                   //true if user wins
    QPixmap *invincible;        //will carry the symbol that will be displayed if we are in invincible mode
    QPixmap *notinvincible;     //will carry the symbol that will be displayed if we are in normal mode
    QGraphicsPixmapItem inv;    //carrys invincible or notinvincible pixmap items to display
    int i;                      //not important used once to add the invincible icon to the scene
    bool invin;                 //true whenever pacman is in invincible mode
    QTimer *timer;              //timer for invincible mode
    bool lose;                  //true if user loses
    QMessageBox msgBox;         //message box to display win/lose message at the end
    QSound *background;         //background sound to be played at the beggining
    QPixmap *Up, *Down, *Left, *Right;

protected:
    void advance(int phase);    //move pacman everytime the signal timeout() is emitted
public slots:
    void MyTimerSlot();         //after the time for invincibility ends delete timer and stop invincible mode
    void keyPressEvent(QKeyEvent *event);
public:
    Pacman();
    void setrow(int);
    void setcolumn (int);
    int getcolumn();
    int getrow();
    void setlose();
    void reset();
    bool movement();

};
#endif // PACMAN_H

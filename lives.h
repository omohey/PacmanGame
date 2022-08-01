#ifndef LIVES_H
#define LIVES_H
#include <QGraphicsTextItem>
#include <QMessageBox>
class Lives:public QGraphicsTextItem
{
public:
    Lives();
    int getlives();
    void decreaselife();
private:
    int lives;
    QMessageBox msgBox;
};

#endif // LIVES_H

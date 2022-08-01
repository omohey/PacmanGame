#ifndef SCORE_H
#define SCORE_H
#include <QGraphicsTextItem>

class Score:public QGraphicsTextItem
{
public:
    Score();
    void addghost();
    void addpellet();
    void addsuperpellet();
    void addfruit();

private:
    int score ;

};

#endif // SCORE_H

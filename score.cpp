#include "score.h"
#include <QFont>
Score::Score()
{
    score=0;

    setPlainText("Score: "+QString::number(score));
    setDefaultTextColor(Qt::white);
    setPos(370, 950);
    setFont(QFont ("Arial", 16));

}

void Score::addghost()
{
    score += 100;
    setPlainText("Score: "+QString::number(score));
}

void Score::addpellet()
{
    score +=10;
    setPlainText("Score: "+QString::number(score));
}

void Score::addsuperpellet()
{
    score +=50;
    setPlainText("Score: "+QString::number(score));
}

void Score::addfruit()
{
    score +=100;
    setPlainText("Score: "+QString::number(score));
}


#include "lives.h"
#include <QFont>
#include "game.h"
#include <QDebug>
extern Game *game;
Lives::Lives()
{
    lives = 3;
    setPlainText("Lives: "+ QString::number(lives));
    setDefaultTextColor(Qt::white);
    setPos(100, 950);
    setTextWidth(100);
    setFont(QFont ("Arial", 14));
}

int Lives::getlives()
{
    return lives;
}

void Lives::decreaselife()
{
    lives--;
    setPlainText("Lives: "+ QString::number(lives));

    if (lives == 0)     //if lives reach zero we lose
    {
        game->pacman->setlose();
        game->player->stop();
        //Win.setPlainText("You Lose");
        //Win.setDefaultTextColor(Qt::white);
        //Win.setPos(700, 960);
        //Win.setFont(QFont ("Arial", 16));
        //scene()->addItem(&Win);
        //background->stop();
        setPlainText("Lives: "+QString::number(lives));
        game->deletelife();
        msgBox.setText("Game Over, you lost :(");
        msgBox.exec();
        exit(0);
    }
    else        //if lives more than zero then remove a life in text item and life symbol
    {

        game->deletelife();
        game->pacman->setcolumn(13);
        game->pacman->setrow(23);

        game->ghosts[0]->setrow(14);
        game->ghosts[0]->setcolumn(13);
        game->ghosts[0]->setPos(10+30*13, 20+30*14);
        game->ghosts[1]->setrow(14);
        game->ghosts[1]->setcolumn(12);
        game->ghosts[1]->setPos(10+30*12, 20+30*14);
        game->ghosts[2]->setrow(14);
        game->ghosts[2]->setcolumn(14);
        game->ghosts[2]->setPos(10+30*14, 20+30*14);
        game->pacman->reset();

    }
    setPlainText("Lives: "+QString::number(lives));
}

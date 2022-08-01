#include "game.h"
#include <QFile>
#include <QTextStream>
#include <QGraphicsPixmapItem>
#include <QIcon>
#include <QGraphicsRectItem>
#include <QDebug>
#include <QTimer>
#include <QObject>
#include <QMediaPlaylist>
#include <cstdlib>
#include <ctime>
Game::Game()
{

    scene = new QGraphicsScene;

    setBackgroundBrush(QBrush(Qt::black));
    setScene(scene);
        setMinimumSize(860, 990);
        scene->setSceneRect(0, 0, 860, 990);
        setWindowTitle("Pacman");
        QPixmap pacmanpixmap(":/Images/Pacmani.png");
        QIcon icon(pacmanpixmap);
        setWindowIcon(icon);

        QFile file((":/Images/read.txt"));             //creating stream and reading the txt file
        file.open(QIODevice::ReadOnly);
        QTextStream stream(&file);
        QString temp;
        for (int r = 0; r<31; r++)
            for (int c = 0; c<28; c++)
            {
                stream>> temp;
                boardData[r][c]= temp.toInt();
            }


        QGraphicsPixmapItem **boardImages;//giving boardImages a wall if we can't move on it or background if we can move on it
        boardImages = new QGraphicsPixmapItem*[31];
        for (int i=0; i<31;i++)
        {
            boardImages[i] = new QGraphicsPixmapItem[28];
        }
        QPixmap brick(":/Images/Bricks.png");
        brick = brick.scaledToWidth(30);
        brick = brick.scaledToHeight(30);
        QPixmap back(":/Images/background.png");
        back = back.scaledToWidth(30);
        back = back.scaledToHeight(30);


        for (int r = 0; r<31; r++)
            for (int c = 0; c<28; c++)
            {
                if (boardData[r][c] == -1)
                    boardImages[r][c].setPixmap(brick);
                else
                    boardImages[r][c].setPixmap(back);
                boardImages[r][c].setPos(10+30*c, 20+30*r);
                scene->addItem(&boardImages[r][c]);
            }

        QPixmap whitebarrier(":/Images/white.png");              // visual representation of the barrier to the ghost home
        whitebarrier = whitebarrier.scaledToWidth(60);
        whitebarrier = whitebarrier.scaledToHeight(5);
        QGraphicsPixmapItem *barrier = new QGraphicsPixmapItem;
        barrier->setPixmap(whitebarrier);
        barrier->setPos(400,380);
        scene->addItem(barrier);
        this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        lives = new Lives;
        scene->addItem(lives);

        vec = new QVector<QGraphicsPixmapItem*>;
        pacmanpixmap = pacmanpixmap.scaledToWidth(30);
        pacmanpixmap = pacmanpixmap.scaledToHeight(30);

        for (int i = 0; i<3; i++)
        {
            QGraphicsPixmapItem *pacman =  new QGraphicsPixmapItem;
            pacman->setPixmap(pacmanpixmap);
            pacman->setPos(10+30*i,950);
            vec->push_back(pacman);
            scene->addItem(vec->at(i));
        }


        score = new Score;
        scene->addItem(score);



        for (int row = 0; row<31; row++)
            for (int col = 0; col<28;col++)
                pellet[row][col]= NULL;

        for (int row = 0; row<31; row++)
            for (int col = 0; col<28;col++)
            {
                if (boardData[row][col] != -1 && boardData[row][col] != 122 && boardData[row][col] != 123 && (boardData[row][col] < 128 || boardData[row][col] > 133)&& (boardData[row][col] < 146 || boardData[row][col] > 151) && (boardData[row][col] < 164 || boardData[row][col] > 169) && boardData[row][col] != 242 && boardData[row][col] != 232 && boardData[row][col] != 253 && boardData[row][col] != 30 && boardData[row][col] != 35  )
                {

                    pellet[row][col] = new pellets(row, col);
                    scene->addItem(pellet[row][col]);

                }
            }

        super[0]= new superPellets(3,1);
        super[1]= new superPellets(3, 26);
        super[2]= new superPellets(23,1);
        super[3]= new superPellets(23, 26);
        for (int i = 0; i<4;i++)
            scene->addItem(super[i]);








            pacman= new Pacman;      //creating the pacman object and making it focusable to use the keys

            pacman->setFlag(QGraphicsItem::ItemIsFocusable);
            pacman->setFocus();


            QMediaPlaylist *playlist = new QMediaPlaylist();
            playlist->addMedia(QUrl("qrc:/Sound/pacman_beginning.wav"));
            playlist->setPlaybackMode(QMediaPlaylist::Loop);
            player = new QMediaPlayer;
            player->setPlaylist(playlist);
            player->play();




}

void Game::deletelife()
{
    delete vec->at(vec->size()-1);
    vec->pop_back();

}

void Game::initializeghosts()
{
    QPixmap inky(":/Images/INKY.jpg");QPixmap pinky(":/Images/PINKY.jpg");QPixmap clyde(":/Images/Clyde.jpg");         //creating the ghosts and adding to scene
    ghost *Inky= new ghost(inky, 13, 0), *Pinky= new ghost(pinky, 12, 1), *Clyde= new ghost(clyde , 14, 2);
      scene->addItem(Inky); scene->addItem(Pinky); scene->addItem(Clyde);

        ghosts[0] = (Inky);
        ghosts[1]= Pinky;
        ghosts[2]= Clyde;
        scene->addItem(pacman);

}

void Game::starttimer()
{
    QTimer *timer;              //timer to keep moving in the same direction without pressing key again
    timer = new QTimer(scene);
    scene->connect(timer,SIGNAL(timeout()),scene,SLOT(advance()));
    timer->start(200);

    fruittimer = new QTimer(this);
    connect(fruittimer, SIGNAL(timeout()), this, SLOT(createfruit()));
    fruittimer->start(40000);

}

void Game::createfruit()
{
    int size = rowsvec.size();
    int vecposition = rand()%size;
    int rowfruit = rowsvec.at(vecposition);
    int colfruit = colsvec.at(vecposition);
    fruit = new Fruit(rowfruit, colfruit);
    scene->addItem(fruit);

    fruittimer2 = new QTimer(this);
    connect(fruittimer2, SIGNAL(timeout()), this, SLOT(destroyfruit()));
    fruittimer2->start(15000);
}

void Game::destroyfruit()
{
    if (fruit!=NULL)
    {
        delete fruit;
        fruit = NULL;
        delete fruittimer2;
    }
}


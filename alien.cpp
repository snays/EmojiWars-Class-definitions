/** @file alien.cpp
       @brief Contains the class definitions for the alien enemy items.
       @author Sneha Belkhale
       @date January 26, 2016

      Contains the definitions of the initial constructor for the randomly generated alien, and definition of
      the slots that allow the aliens to move, and fire bullets.

*/
#include "emoji.h"
#include "alien.h"
#include "bullet.h"
#include <QPainter>
#include <QPixmap>
#include <QKeyEvent>
#include <QCoreApplication>
#include <QGraphicsScene>
#include <QTimer>
#include <QList>
#include "mainwindow.h"

/** Constructor for enemy alien item, sets the pixmap item to an image of an alien, also determines
    randomly wether the alien will be moving horizontally or vertically, and sets initial position accordingly.
    Also connects the alien item's move and fire slots with a timer.
    @param firing - a bool variable letting us know whether this particular alien will be firing bullets or not.

*/
alien::alien(bool firing)
{
    //set pixmap of the alien item
    QPixmap enemy=QPixmap(":/image/alien.png");
    setPixmap(enemy);

    //generate a random number ( 0 or 1)
    int random=rand()%2;

    //half the aliens move vertically
    if(random==1)
    {
        down=true;
        right=false;
        //set initial position of the alien to be random on the x axis
        int randomx=rand()%350;
        setPos(randomx,-10);
    }
    //other half of the aliens move horizontally
    else
    {
        right=true;
        down=false;
        //set initial position of alien to be random on y axis
        int randomy=rand()%350;
        setPos(-10,randomy);
    }


    //connect the alien's move function to a timer so that the move function is periodically called
    QTimer*timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(100); //move is called 10 times per second

    //connect the alien's fire function to a timer so that the alien periodically fires
    if (firing)
    {
    QTimer*bulletTimer=new QTimer(this);
    connect(bulletTimer,SIGNAL(timeout()),this,SLOT(fire()));
    bulletTimer->start(MainWindow::level_int*200+2400); //fire every 2 seconds
    }
}

/** The move() function is connected to a timer, and is called on the alien object 10 times per second.
    it moves the alien horizontally or vertically (based on parameter down/right), and also removes the alien from
    the scene if it goes off the screen.

*/
void alien::move()
{
    //move alien down if the particular alien is moving vertically
    if(down)
        setPos(x(),y()+4);
    //move alien to the right if the particular alien is moving horizontally
    if(right)
        setPos(x()+4,y());

    //if the position of the alien is outside our scene boundary (400x400 pixels),
    //remove the alien from the scene and delete it to avoid memory leaks
    if(x()>400||x()<-10||y()<-10||y()>400)
    {
        scene()->removeItem(this);
        delete this;
    }
}

/** The fire() function is connected to a timer, and is called on the alien object every 2 seconds.
    it essentially creates a bullet item to add to the scene, every 2 seconds.The bullet item is positioned
    at the aliens position and moves in the opposite direction of its caller alien.

*/
void alien::fire()
{
    //create a new bullet item, specifying its inital location to be the location of the alien. also specify
    //the direction that the alien is moving so that the bullet can know to move in the opposite direction
    bullet* b=new bullet(x(),y(),down);
    //add bullet to the scene
    scene()->addItem(b);

}

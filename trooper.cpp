/** @file trooper.cpp
       @brief Contains the class definitions for the trooper enemy items.
       @author Sneha Belkhale
       @date January 26, 2016

      Contains the definitions of the initial constructor for the randomly generated trooper, and definition of
      the slots that allow the troopers to move.

*/
#include "emoji.h"
#include "trooper.h"
#include "bullet.h"
#include <QPainter>
#include <QPixmap>
#include <QKeyEvent>
#include <QCoreApplication>
#include <QGraphicsScene>
#include <QTimer>
#include <QList>

/** Constructor for enemy trooper item, sets the pixmap item to an image of an trooper, also determines
    randomly whether the trooper will be entering from the top or side of window, and sets initial position accordingly.
    Also connects the trooper item's move slots with a timer.

*/
trooper::trooper()
{
    //set pixmap of the trooper item
    QPixmap enemy=QPixmap(":/image/trooper.png");
    setPixmap(enemy);

    //generate a random number ( 0 or 1)
    int random=rand()%2;

    //half the troopers start at the x axis
    if(random==1)
    {
        //set initial position of the trooper to be random on the x axis
        int randomx=rand()%350;
        setPos(randomx,-10);
    }
    //other half of the troopers start at the y axis
    else
    {
        //set initial position of trooper to be random on y axis
        int randomy=rand()%350;
        setPos(-10,randomy);
    }


    //connect the trooper's move function to a timer so that the move function is periodically called
    QTimer*timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(100); //move is called 10 times per second

}

/** The move() function is connected to a timer, and is called on the trooper object 10 times per second.
    it randomly moves the alien horizontally or vertically, and also removes the alien from
    the scene if it goes off the screen.

*/
void trooper::move()
{
    if(stepSize>0)
    {
        if(direction=="right")
            setPos(x()+2,y());
        if(direction=="left"&&x()>20)
            setPos(x()-2,y());
        if(direction=="down")
            setPos(x(),y()+2);
        stepSize--;

    }
    else
    {
    //generate a random number ( 0 to 3)
    int random=rand()%3;
    //generate a random number ( 1 or 9) for the length in that direction
    stepSize=rand()%75+1;
    //for half of the calls to this method
    if(random==0)
    {
        direction="right";
    }
    //for the other half
    if(random==1)
    {
        direction="left";
    }
    //for half of the calls to this method
    if(random==2)
    {
       direction="down";
    }
    }
    //if the position of the trooper is outside our scene boundary (400x400 pixels),
    //remove the trooper from the scene and delete it to avoid memory leaks
    if(x()>400||x()<-10||y()<-10||y()>400)
    {
        scene()->removeItem(this);
        delete this;
    }
}

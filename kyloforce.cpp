/** @file kyloforce.cpp
       @brief Contains the class definitions for the kylo force class
       @author Sneha Belkhale
       @date January 26, 2016

      Contains the definitions of the initial constructor for the kylo force item that is fired by kylo ren at periodic intervals.
      Also contains a move() slot connected to a timer so kylo ren's attacking force item moves smoothly.

*/
#include "force.h"
#include "emoji.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QList>
#include "trooper.h"
#include "alien.h"
#include "bullet.h"
#include "newwindow.h"
#include "kylo.h"
#include "kyloforce.h"
#include <QDebug>



/** Constructor for kylo force pixmap item. Sets pixmap, direction, and connects the bullet to a timer for smooth movement.

    @param x - the x location of kylo ren at the time of fire
    @param y - the y location of kylo ren at the time of fire
    @param theWindow - pointer to the main window so we have access to the main game window's functions
    @param thePlayer- pointer to the player so we have access to the players functions
    @param direction- direction that kylo force is destined to move

*/
kyloforce::kyloforce(qreal x, qreal y,NewWindow* theWindow, emoji* thePlayer, std::string direction)
{
    //give force pixmap item the kylo force image
    QPixmap force_pix=QPixmap(":/image/kyloforce.png");
    setPixmap(force_pix);
    //set position of force to be close to where kylo ren fired
    setPos(x+5,y+10);


    //connect force's move() SLOT to a timer for automated movement
    QTimer*moveForce=new QTimer(this);
    connect(moveForce,SIGNAL(timeout()),this,SLOT(move()));
    //move force every 15 milliseconds
    moveForce->start(15);

    //set pointer to the game window
    this->theWindow=theWindow;
    //set pointer to the player
    this->thePlayer=thePlayer;
    //set direction
    this->direction=direction;

}


/** function to control the movement of the force. This function is connected to a timer so that it
    is automatically called every 15 milliseconds.

*/
void kyloforce::move()
{
    //if the force is moving left
    if(direction=="left")
        //move position of force to the left
        setPos(x()-2,y());

    //if the force is moving right
    if(direction=="right")
        //move position of force to the right
        setPos(x()+2,y());

    //if the force is moving down
    if(direction=="up")
        //move position of force down
        setPos(x(),y()-2);

    //if the force is moving up
    if(direction=="down")
        //move position of force to the up
        setPos(x(),y()+2);


    //make sure that bullet is within bounds of the game graphic view that is 400 x400 pix
    if(x()>400||x()<0||y()<0||y()>400)
    {
        //if it is not within bounds, remove the bullet from scene
        scene()->removeItem(this);
        //clear heap memory
        delete this;
    }

}


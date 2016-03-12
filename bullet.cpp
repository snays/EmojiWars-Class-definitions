/** @file bullet.cpp
       @brief Contains the class definitions for the bullet class
       @author Sneha Belkhale
       @date January 26, 2016

      Contains the definitions of the initial constructor for the bullet that is fired by an alien at periodic intervals.
      Also contains a move() slot connected to a timer so the bullet moves smoothly.

*/
#include "bullet.h"
#include "emoji.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QList>
#include <QMediaPlayer>

/** Constructor for bullet pixmap item. Sets pixmap, direction, and connects the bullet to a timer for smooth movement.

    @param x - the x location of the alien at the time of fire
    @param y - the y location of the alien at the time of fire
    @param down - the bool letting us know if the alien is moving horizontally or vertically, so that we
    know which direction to fire the bullet

*/
bullet::bullet(qreal x, qreal y, bool down)
{
    //give bullet pixmap item the bullet image
    QPixmap bullet_pix=QPixmap(":/image/bullet.png");
    setPixmap(bullet_pix);
    //set position of bullet to be close to where the alien fired
    setPos(x+10,y+10);
    //set direction of movement
    direction=down;

    //connect bullet's move() SLOT to a timer for automated movement
    QTimer*moveBullet=new QTimer(this);
    connect(moveBullet,SIGNAL(timeout()),this,SLOT(move()));
    //move bullet every 30 milliseconds
    moveBullet->start(30);

    //to help randomly generate movement, we pick a number 0 or 1 randomly
    int random=rand()%2;
    //and then use the random number to pick wether the bullet moves up/down or left/right wrt to the alien
    if(random==0) up=true;
    if(random==1) up=false;

}


/** function to control the movement of the bullet. This function is connected to a timer so that it
    is automatically called every 30 milliseconds.

*/
void bullet::move()
{
    //if alien is moving down
    if(direction)
    {
        //and if we randomly chose up to be true
        if(up)
            //move bullet to the left
            setPos(x()-2,y());
        else
            //or else move bullet to the right
            setPos(x()+2,y());
    }
    //if alien is moving to the right
    else
    {
        //and we randomly chose up to be true
        if(up)
            //move bullet down
            setPos(x(),y()+2);
        else
            //or else move bullet up
            setPos(x(),y()-2);
    }

    //make sure that bullet is within bounds of the game graphic view that is 400 x 400 pix
    if(x()>400||x()<0||y()<0||y()>400)
    {
        //if it is not within bounds, remove the bullet from scene
        scene()->removeItem(this);
        //clear heap memory
        delete this;
    }

}

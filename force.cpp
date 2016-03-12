/** @file bullet.cpp
       @brief Contains the class definitions for the bullet class
       @author Sneha Belkhale
       @date January 26, 2016

      Contains the definitions of the initial constructor for the bullet that is fired by an alien at periodic intervals.
      Also contains a move() slot connected to a timer so the bullet moves smoothly.

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
#include "mainwindow.h"
#include "kylo.h"
#include <QDebug>


int force::numberOfKilledTroopers=0;


/** Constructor for bullet pixmap item. Sets pixmap, direction, and connects the bullet to a timer for smooth movement.

    @param x - the x location of the alien at the time of fire
    @param y - the y location of the alien at the time of fire
    @param theWindow - is a pointer to the game window so that we have access to its funtions
    @param thePlayer - is a pointer to the player so that we can have access to its functions
    @param direction- string that lets us know which direction the force is moving in

*/
force::force(qreal x, qreal y,NewWindow* theWindow, emoji* thePlayer, std::string direction)
{
    //give force pixmap item the force image
    QPixmap force_pix=QPixmap(":/image/force.png");
    setPixmap(force_pix);
    //set position of force to be close to where the player fired
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
    is automatically called every 30 milliseconds.

*/
void force::move()
{
    //if the force was instantiated by pressing A
    if(direction=="left")
        //move position of force to the left
        setPos(x()-4,y());

    //if the force was instantiated by pressing S
    if(direction=="right")
        //move position of force to the right
        setPos(x()+4,y());

    //if the force was instantiated by pressing W
    if(direction=="up")
        //move position of force to the left
        setPos(x(),y()-4);

    //if the force was instantiated by pressing Z
    if(direction=="down")
        //move position of force to the left
        setPos(x(),y()+4);

    //retrieve the list of colliding items
    QList<QGraphicsItem*> colliding_items=collidingItems();
    //iterate through the list to check the type of item
    for(int i=0; i<colliding_items.size();i++)
    {
       //if the item is a bullet, or alien
        if(typeid(*colliding_items[i])==typeid(alien)||typeid(*colliding_items[i])==typeid(bullet))
        {
            //remove item from scene
            scene()->removeItem(colliding_items[i]);
            //delete heap memory
            delete colliding_items[i];
            return;
        }
        //if the item was a trooper
        if(typeid(*colliding_items[i])==typeid(trooper))
        {
            //increase number of killed troopers
            numberOfKilledTroopers++;
            //if we have killed x troopers (number depends on skill level), we move on to the next level and create kylo ren
            if(numberOfKilledTroopers>(11-2*MainWindow::level_int)&&numberOfKilledTroopers<(13-2*MainWindow::level_int))
            {
                //create the kylo ren
                kylo* b=new kylo(theWindow,thePlayer);
                //add kylo to the scene
                scene()->addItem(b);
                //send a message to the screen
                theWindow->showKyloLevel();
                //let the player know that it is now the kylo level
                thePlayer->kyloLevel=true;
            }
           //remove item from scene
           scene()->removeItem(colliding_items[i]);
           //delete heap memory
           delete colliding_items[i];
           return;
        }
    }
    //make sure that bullet is within bounds of the game graphic view that is 400 x400 pix
    if(x()>400||x()<0||y()<0||y()>400)
    {
        //if it is not within bounds, remove the bullet from scene
        scene()->removeItem(this);
        //clear heap memory
        delete this;
    }

}

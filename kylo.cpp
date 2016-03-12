/** @file kylo.cpp
       @brief Contains the class definitions for the final Kylo Ren enemy
       @author Sneha Belkhale
       @date January 26, 2016

      Contains the definitions of the initial constructor for the final enemy Kylo Ren. Kylo Ren will be instantiated once during the
      game (when player kills the set number of troopers). This file also contains definition of
      the slots that allow kylo ren to move.

*/
#include "emoji.h"
#include "mainwindow.h"
#include "trooper.h"
#include "newwindow.h"
#include "kylo.h"
#include "kyloforce.h"
#include "force.h"
#include <QPainter>
#include <QPixmap>
#include <QKeyEvent>
#include <QCoreApplication>
#include <QGraphicsScene>
#include <QTimer>
#include <QList>
#include <QDebug>
#include "spark.h"


/** Constructor for kylo ren enemy, sets the pixmap item to an image of kylo ren, also determines
    randomly whether the trooper will be entering from the top or side of window, and sets initial position accordingly.
    Also connects the kylo ren's move slots with a timer.
    @param theWindow - is a pointer to the game window so that we have access to its functions
    @param thePlayer - is a pointer to the player so that we have access to its functions

*/
kylo::kylo(NewWindow*theWindow, emoji* thePlayer)
{
    //set pixmap of kylo ren
    QPixmap enemy=QPixmap(":/image/kylo.png");
    setPixmap(enemy);
    //set initial position
    setPos(0,0);

    //set the pointer to the main player
    this->thePlayer=thePlayer;

    //set the pointer to the main player
    this->theWindow=theWindow;

    //connect kylo move() SLOT to a timer for automated movement
    QTimer*moveKylo=new QTimer(this);
    connect(moveKylo,SIGNAL(timeout()),this,SLOT(move()));
    //move kylo every 100 milliseconds
    moveKylo->start(100);

    //fill up the positions with 9 initial points so we have initial capacity of 9
    positions.push_back(points(0,0));
    positions.push_back(points(0,0));
    positions.push_back(points(0,0));
    positions.push_back(points(0,0));
    positions.push_back(points(0,0));
    positions.push_back(points(0,0));
    positions.push_back(points(0,0));
    positions.push_back(points(0,0));
    positions.push_back(points(0,0));

    //connect the alien's fire function to a timer so that the kylo periodically fires
    QTimer*forceTimer=new QTimer(this);
    connect(forceTimer,SIGNAL(timeout()),this,SLOT(fire()));
    forceTimer->start(MainWindow::level_int*500+3500); //fire ever x seconds depending on skill level chosen


}

/** The move() function is connected to a timer, and is called on kylo ren every 100 milliseconds.
    the move function essentially draws a line from kylo ren's position to the main player, and moves kylo ren
    one step in that direction. To create a small delay, we use the positions deque to add the current position of the player
    to the end of the queue, and then draw a line to the first element in the deque, then popping off the first element so we
    can make our way through the queue next time the move() function is called

    the move() function also checks for colliding items so that if it collides with the players force, kylo loses a life.

*/
void kylo::move()
{
    //retrieve the list of colliding items
    QList<QGraphicsItem*> colliding_items=collidingItems();
    //iterate through the list to check the type of item
    for(int i=0; i<colliding_items.size();i++)
    {
        //if the item is the players force
        if(typeid(*colliding_items[i])==typeid(force))
        {
            //decrease kylo's lives
            --kyloLives;
            //show player that kylo is dying
            theWindow->showKyloHarmed(kyloLives);
            //remove the force item from scene
            scene()->removeItem(colliding_items[i]);\
            //delete heap memory
            delete colliding_items[i];

            //create a spark and add it to the scene to signify kylo's lost life
            spark* sparky=new spark(x(),y());
            scene()->addItem(sparky);

            //if kylo has no lives left
            if(kyloLives==0)
            {
                //remove kylo from the scene
                scene()->removeItem(this);
                //tell the main game window that the player has won
                theWindow->warningGameOver(1);
                //delete heap memory
                delete this;
                return;
            }
        }
    }

    //add the current position of the player (twice for some delay) to the positions deque
    positions.push_back(points(thePlayer->x(),thePlayer->y()));
    positions.push_back(points(thePlayer->x(),thePlayer->y()));
    //access first element in deque
    int x1=positions[0].x;
    int y1=positions[0].y;
    //calculate slope of connecting line to (from kylo to player)
    int slope=(y1-y())/(x1-x());

    //if player is to the right, move kylo to the right
    if(x1>x())
        //set new position to the corresponding y value
        setPos(x()+1,slope*(x()+1-x1)+y1);
    //if player is to the left, move kylo to the left
    if(x1<x())
        //set new position to the corresponding y value
        setPos(x()-1,slope*(x()-1-x1)+y1);
    //pop off the first element because we are done using it
    positions.pop_front();

}

/** The fire() function is connected to a timer, and is called on kylo every x seconds (based on skill level).
    it essentially creates 4 kylo force items moving up, down, left, and right from kylo's current position.
*/
void kylo::fire()
{
    //create a new kylo force item moving up, down, left, and right
    kyloforce* a=new kyloforce(x(),y(),theWindow, thePlayer,"up");
    kyloforce* b=new kyloforce(x(),y(),theWindow, thePlayer,"down");
    kyloforce* c=new kyloforce(x(),y(),theWindow, thePlayer,"left");
    kyloforce* d=new kyloforce(x(),y(),theWindow, thePlayer,"right");
    //add all kylo force items to the scene
    scene()->addItem(a);
    scene()->addItem(b);
    scene()->addItem(c);
    scene()->addItem(d);

}

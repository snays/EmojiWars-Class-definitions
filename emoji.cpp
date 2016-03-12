/** @file emoji.cpp
       @brief Contains the class definitions for the player's emoji pixmap item.
       @author Sneha Belkhale
       @date January 26, 2016

      Contains the definitions of the initial constructor for the players emoji, keyboard functionality, and
      a function that generates enemy aliens and troopers.

*/
#include "emoji.h"
#include "alien.h"
#include "bullet.h"
#include "kyloforce.h"
#include "trooper.h"
#include "force.h"
#include "spark.h"
#include <QPainter>
#include <QPixmap>
#include <QKeyEvent>
#include <QCoreApplication>
#include <QGraphicsScene>
#include <QTimer>
#include <QMetaMethod>
#include "newwindow.h"
#include "mainwindow.h"
#include <QMediaPlayer>
/** Constructor for player's emoji, sets players icon according to which radiobox was chosen on the mainwindow.

  @param i- when we create the player, we specify an integer according to the radiobox that was chosen in the mainwindow,
  to determine which emoji icon is desired by the user.
  @param theWindow- is a pointer to the game window so that we have access to its funtions

*/
emoji::emoji(int i,NewWindow* theWindow)
{
    //create the pixmap for the player's icon
    QPixmap emoji_pix;

    //determine if the player chose to play as a diva, police, or pizza
    if(i==1)
        emoji_pix=QPixmap(":/image/diva.png");
    if(i==2)
        emoji_pix=QPixmap(":/image/popo_copy.png");
    if(i==3)
        emoji_pix=QPixmap(":/image/pizza_copy.png");

    //scale emoji
    emoji_pix.scaledToWidth(40);
    //set the pixmap of the emoji
    setPixmap(emoji_pix);

    //connect a timer to the check() slot so that we can check for any collisions automatically
    QTimer*checkTimer=new QTimer(this);
    connect(checkTimer,SIGNAL(timeout()),this,SLOT(check()));
    //check for collisions every 30 milliseconds
    checkTimer->start(30);

    //initialize force to false
    has_force=false;
    //initialize the pointer to the game window
    this->theWindow=theWindow;

//    //play ignition sound of lightsaber
//    QMediaPlayer* sound=new QMediaPlayer();
//    sound->setMedia(QUrl(":/sounds/SaberOn.wav"));
//    sound->setVolume(50);
//    sound->play();


}

/** This function is to move the emoji Right, Left, Up, and Down on the board when the user presses the corresponding
  keyboard keys. The function is called whenever the user presses the keyboard, as we have set the player to be the
  focus of the keyboard.
  @param pointer to the event that is generated when a key is pressed
*/

void emoji::keyPressEvent(QKeyEvent *event)
{

    //set speed of emoji based on their expert status (jedi's move fastest)
    int speed=17-3*MainWindow::level_int;
    //set new position of the emoji according to the key that is pressed.
    if(event->key()==Qt::Key_Right)
        //check bounds so emoji cannot move off of screen, then set new position
        if((x()+5)<350)
            setPos(x()+speed,y());
    if(event->key()==Qt::Key_Left)
        //check bounds so emoji cannot move off of screen, then set new position
        if((x()-5)>0)
            setPos(x()-speed,y());
    if(event->key()==Qt::Key_Up)
        //check bounds so emoji cannot move off of screen, then set new position
        if((y()-5)>0)
            setPos(x(),y()-speed);
    if(event->key()==Qt::Key_Down)
        //check bounds so emoji cannot move off of screen, then set new position
        if((y()+5)<350)
            setPos(x(),y()+speed);

    //if the user presses the key A
     if(event->key()==Qt::Key_A)
         //they can only create a force item if they currently have the force
         if(has_force)
         {
             //create new force item moving left
             force* b=new force(x(),y(),theWindow,this,"left");
             //add force item to the scene
             scene()->addItem(b);
             //send signal to decrease the force bar
             emit force_used();
         }

     //if the user presses the key D
     if(event->key()==Qt::Key_D)
         //they can only create a force item if they currently have the force
         if(has_force)
         {
             //create new force item moving right
             force* b=new force(x(),y(),theWindow,this,"right");
             //add force item to the scene
             scene()->addItem(b);
             //send signal to decrease the force bar
             emit force_used();
         }

     //if the user presses the key W
     if(event->key()==Qt::Key_W)
         //they can only create a force item if they currently have the force
         if(has_force)
         {
             //create new force item moving UP
             force* b=new force(x(),y(),theWindow,this,"up");
             //add force item to the scene
             scene()->addItem(b);
             //send signal to decrease the force bar
             emit force_used();
         }

     //if the user presses the key S
     if(event->key()==Qt::Key_S)
         //they can only create a force item if they currently have the force
         if(has_force)
         {
             //create new force item moving down
             force* b=new force(x(),y(),theWindow,this,"down");
             //add force item to the scene
             scene()->addItem(b);
             //send signal to decrease the force bar
             emit force_used();
         }

}

/** This function is to set the bounding box of the emoji to be the size of t screen so that it does not leave the screen.
*/

QRectF emoji::boundingRect() const
{
    return QRectF(0,0,400,400);
}

/** This function is to generate an enemey alien, and add it to the screen. This function is
    linked to a timer in newwindow.cpp, and is called at periodic intervals within the duration of the game.
*/
void emoji::generateAliens()
{
    //if we have reached level 3, generate aliens that don't fire
    if(kyloLevel)
    {
        //create alien pixmap item that does not fire
        alien* a=new alien(false);
        //add the item to the parent scene
        scene()->addItem(a);
    }
    //if we have not reached level 3, generate aliens that do fire
    else
    {
        //create alien pixmap item that fires
        alien* a=new alien(true);
        //add the item to the parent scene
        scene()->addItem(a);
    }
}

/** This function is to generate an enemey trooper, and add it to the screen. This function is
    linked to a timer in emoji::startTroopers(), and is called at periodic intervals within the duration of the game.
*/
void emoji::generateTroopers()
{
    //create trooper pixmap item
    trooper* a=new trooper();
    //add the item to the parent scene
    scene()->addItem(a);
}

/** This function is to set up the timer to start generating troopers on the board. It is called when we destroy a certian number of
 * enemy aliens (moving up to the next level)
*/
void emoji::startTroopers()
{
    //connect the timer to a function that generates troopers on the board, less frequently
    QTimer* timer2=new QTimer();
    QObject::connect(timer2, SIGNAL(timeout()),this,SLOT(generateTroopers()));
    //generate an enemy trooper every x seconds depending on the skill level chosen
    timer2->start(1000+MainWindow::level_int*2000);
}

/** This function is to constantly check if the emoji has collided with any other items.
    if there are collisions, we continue with the appropriate responses.
*/
void emoji::check()
{
    //retrieve the list of colliding items
    QList<QGraphicsItem*> colliding_items=collidingItems();
    //iterate through the list to check the type of item
    for(int i=0; i<colliding_items.size();i++)
    {
        //if the item is a bullet or a kylo force
        if(typeid(*colliding_items[i])==typeid(bullet)||typeid(*colliding_items[i])==typeid(kyloforce))
        {
            //emit a signal to remove a life
            emit lostlife();

            //create a spark and add it to the scene to signify the lost life
            spark* sparky=new spark(x(),y());
            scene()->addItem(sparky);

            //remove bullet from scene
            scene()->removeItem(colliding_items[i]);
            //delete heap memory
            delete colliding_items[i];
            return;
        }
        //if the item is an enemy alien
        if(typeid(*colliding_items[i])==typeid(alien))
        {
            //increment the number of killed aliens
            numberOfKilledAliens++;
            //if we have killed 11 aliens, we move on to the next level and start the troopers
            if(numberOfKilledAliens>10&&numberOfKilledAliens<12)
            {
                //start generating troopers
                this->startTroopers();
                //show a message to the player saying they have moved up a level
                theWindow->showTrooperLevel();
            }
            //emit a signal to raise the force bar
            if(has_force==false)
                emit hit();
            //remove the alien from the scene
            scene()->removeItem(colliding_items[i]);
            //delete heap memory
            delete colliding_items[i];
            return;
        }
        //if the item is an enemy trooper
        if(typeid(*colliding_items[i])==typeid(trooper))
        {
            //emit a signal to remove a life
            emit lostlife();
            //remove the trooper from the scene
            scene()->removeItem(colliding_items[i]);
            //delete heap memory
            delete colliding_items[i];

            //create a spark and add it to the scene to signify the lost life
            spark* sparky=new spark(x(),y());
            scene()->addItem(sparky);
            return;
        }
    }
}

/** This function a slot that is connected to two signals. It is called when the forcebar has reached capacity,
    and consequently changes the has_force variable to true. It is also called when the forcebar has depleted, and
    consequently changes the has_force variable to false.
*/
void emoji::hasForce()
{
    //create a QMetaMethod object so that we can detect who was the caller of the method
    QMetaMethod metaMethod = sender()->metaObject()->method(senderSignalIndex());
    //if the slot was called by the force obtained method
    if(metaMethod.methodSignature()=="forceObtained()")
        //set has_force to true
        has_force=true;
    //if the slot was called by the force depleted method
    if(metaMethod.methodSignature()=="forceDepleted()")
        //set has force to false
        has_force=false;
}



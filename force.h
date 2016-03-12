/** @class force
       @brief Contains the class declarations for the force pixmap item.
       @author Sneha Belkhale
       @date January 26, 2016

      A new instance of this class is generated when the player has the force, and presses A,S,W,or Z. The force is used to kill
      higher order enemies.
*/
#ifndef FORCE_H
#define FORCE_H

#include<QGraphicsItem>
#include<QObject>
#include "newwindow.h"
#include "emoji.h"

class force:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    //constructor
    force(qreal x, qreal y,NewWindow* theWindow,emoji* thePlayer,std::string direction);
    //static integer to keep track of how many troopers killed by all force objects
    static int numberOfKilledTroopers;

public slots:
    //slot to move the force
    void move();

private:
    //pointer to the game window
    NewWindow* theWindow;
    //pointer to the player
    emoji* thePlayer;
    //direction the force was selected to move in
    std::string direction;


};


#endif // FORCE_H

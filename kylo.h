#include<QGraphicsItem>
#include<QObject>
/** @class kylo
       @brief Contains the class declarations for the final enemy, kylo ren, pixmap item
       @author Sneha Belkhale
       @date January 26, 2016

      An instance of this class, the final enemy Kylo Ren, is generated once the emoji player kills a pre-determined number of enemy troopers.
      The kylo ren has an initial constructor, and slots that are linked to timers that help Kylo Ren move and shoot out his own force.


*/
#ifndef KYLO_H
#define KYLO_H


#include "emoji.h"
#include "newwindow.h"
#include <deque>

class kylo:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    //constructor
    kylo(NewWindow*theWindow, emoji* thePlayer);
    //nested class of simple 2D points to hold previous coordinates of player to follow
    class points{
    public:
        //constructor
        points(int x, int y):x(x),y(y){};
        //integer variables to hold x coordinate
        int x;
        //integer variable to hold y coordinate
        int y;
    };
    //integer to keep track of kylo's lives remaninging
    int kyloLives=3;
public slots:
    //slot to move the kylo
    void move();
    //slot to have kylo fire his force in all directions
    void fire();
private:
    //pointer to the main player
    emoji* thePlayer;
    //pointer to the main player
    NewWindow* theWindow;
    //deque to hold the previous coordinates of the player
    std::deque<points> positions;


};
#endif // KYLO_H

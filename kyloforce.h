#ifndef KYLOFORCE_H
#define KYLOFORCE_H
/** @class kyloforce
       @brief Contains the class declarations for the kylo force pixmap item.
       @author Sneha Belkhale
       @date January 26, 2016

      A new instance of this class is generated when kylo generates the force. This force is a red beam that will cause the player
      to lose a life if contact is made.
*/

#include<QGraphicsItem>
#include<QObject>
#include "newwindow.h"
#include "emoji.h"
#include "kylo.h"


class kyloforce:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    //constructor
    kyloforce(qreal x, qreal y,NewWindow* theWindow,emoji* thePlayer,std::string direction);
public slots:
    //slot to move the force
    void move();
private:
    //pointer to the game window
    NewWindow* theWindow;
    //pointer to the player
    emoji* thePlayer;
    //direction this force was intended to move
    std::string direction;



};


#endif // KYLOFORCE_H


/** @class bullet
       @brief Contains the class declarations for the bullet pixmap item.
       @author Sneha Belkhale
       @date January 26, 2016

      A new instance of this class is generated every two seconds by a caller alien. This file contains the constructor of the
      bullet item, and move() slot connected to a timer for smooth movement.

*/
#ifndef BULLET_H
#define BULLET_H

#include<QGraphicsItem>
#include<QObject>

class bullet:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    //constructor
    bullet(qreal x, qreal y, bool right);
public slots:
    //slot to move the bullet
    void move();

private:
    //to determine if bullet will be moving horizontally or vertically
    bool direction;
    //to determine if the individual bullet will be moving to right/left, or up/down (independed of caller alien)
    bool up;
};

#endif // BULLET_H

/** @class trooper
       @brief Contains the class declarations for the enemy trooper pixmap items
       @author Sneha Belkhale
       @date January 26, 2016

      A new instance of this class generates a trooper on the scene, at a random location. The trooper class has an
      initial constructor, and slots that are linked to timers that help the alien move in random directions.


*/
#ifndef TROOPER_H
#define TROOPER_H

#include<QGraphicsItem>
#include<QObject>

class trooper:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    //constructor
    trooper();

public slots:
    //slot to move the trooper
    void move();

private:
    //integer to help with movement
    int stepSize;
    //string to tell us what direction trooper is moving in
    std::string direction;

};

#endif // TROOPER_H

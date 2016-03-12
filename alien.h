/** @class alien
       @brief Contains the class declarations for the enemy alien pixmap items
       @author Sneha Belkhale
       @date January 26, 2016

      A new instance of this class generates an alien on the scene, at a random location. The alien class has an
      initial constructor, and slots that are linked to timers that help the alien move smoothly in one direction
      and fire bullets in intervals.

*/
#ifndef ALIEN_H
#define ALIEN_H

#include<QGraphicsItem>
#include<QObject>

class alien:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    //constructor
    alien(bool firing);
public slots:
    //slot to move the alien
    void move();
    //slot to have alien fire a bullet
    void fire();
private:
    //variable to let us know if the specific instance of alien is moving vertically
    bool down;
    //variable to let us know if the specific instance of alien is moving horizontally
    bool right;
};

#endif // ALIEN_H

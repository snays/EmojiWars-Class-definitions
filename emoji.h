/** @class emoji
       @brief Contains the class declarations for the player pixmap item on our main graphics scene.
       @author Sneha Belkhale
       @date January 26, 2016

      There will only be one item of this class when we play the game, as there can only be one player.
      Contains the constructor for the player pixmap item, a key event so that the emoji player can be moved with
      arrow keys. There is also a public slot called spawn, to generate aliens (this slot is connected to a timer
      that starts when the new window is created).
*/
#ifndef EMOJI_H
#define EMOJI_H

#include <QGraphicsItem>
#include <QObject>
#include <newwindow.h>

class emoji:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    //constructor
    emoji(int i,NewWindow* theWindow);
    //keyboard functionality
    void keyPressEvent(QKeyEvent*);
    QRectF boundingRect() const;
    void startTroopers();
    bool kyloLevel=false;
signals:
    //signal sent when player kills an alien
    void hit();
    //signal sent when player shoots the force
    void force_used();
    //signal sent when player is hit by bullet
    void lostlife();


public slots:

    //generates enemy aliens
    void generateAliens();
    //generates enemy troopers
    void generateTroopers();
    //checks for collisions
    void check();
    //turns on the force
    void hasForce();

private:
    //to determine whether player has the force or not
    bool has_force;
    NewWindow* theWindow;
    int numberOfKilledAliens=0;

};

#endif // EMOJI_H

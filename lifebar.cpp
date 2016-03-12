/** @file lifebar.cpp
       @brief Contains the class definitions for the lifebar widget
       @author Sneha Belkhale
       @date January 26, 2016

      Contains the definitions of the initial constructor for the forcebar, a paintevent that paints the current lives remaining,
      and a slot that is called when the user is hit by a bullet

*/
#include "lifebar.h"
#include <QPainter>
#include <QPaintEvent>

/** Standard Constructor for a QWidget. Also sets initial number of lives to 4.

*/
lifebar::lifebar(QWidget *parent) : QWidget(parent)
{
    //set number of lives
    numberOfLives=4;
}

/** paint event to display the number of lives on the widget. This function is called
    whenever the player loses a life so that we can repaint the new decreased number of lives.

*/
void lifebar::paintEvent(QPaintEvent*){

    QPainter painter(this);
    //set green brush
    painter.setBrush(Qt::green);
    //repeat this numberOfLives times
    for(int i=0;i<numberOfLives;i++)
    {
    //draw the numberOfLives number of circles spaced apart
    painter.drawEllipse(15*i,0,10,10);
    }
}

/** Slot that is called whenever the player is hit by a bullet. It decreases the number of lives and calls repaint on the
    Lifebar. Also when the player runs out of lives then this function closes the game.

*/
void lifebar::loselife()
{
    //decrease number of lives
    numberOfLives--;
    //repaint lifebar if we have atleast one life left
    if(numberOfLives>0)
         update();
    //if we have no lives left
    else
    {
        //emit the signal that tells the game window that the game is over
        emit gameOver(0);
        numberOfLives=4;
        //delete the lifebar so it doesnt constantly send this signal
        delete(this);

    }
}

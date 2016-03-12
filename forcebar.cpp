/** @file forecebar.cpp
       @brief Contains the class definitions for the forcebar widget
       @author Sneha Belkhale
       @date January 26, 2016

      Contains the definitions of the initial constructor for the forcebar, a paintevent that paints the level of force,
      and a slot that is called when the user kills an alien

*/
#include "forcebar.h"
#include "ui_forcebar.h"
#include <QPainter>

/** Standard Constructor for a QWidget. Also sets initial level value to be 190, which draws a very small rectangle to
    create the vision of a nearly empty forcebar.

*/
ForceBar::ForceBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ForceBar)
{
    ui->setupUi(this);
    level=190;
}

/** Standard QWidget Destructor
*/
ForceBar::~ForceBar()
{
    delete ui;
}

/** paintEvent function for the forcebar which essentially draws a rectangle in the forcebar to indicate the level of force
    currently obtained by the player. We update the paintEvent every time the player kills an alien.
*/
void ForceBar::paintEvent(QPaintEvent*){

    QPainter painter(this);
    //draw rect at current force level
    painter.fillRect(0,level,40,400,Qt::green);
}

/** This function is connected to a slot that is called whenever the player kills an alien. It essentially changes the level
    of force and calls repaint on the forcebar.
*/
void ForceBar::gainForce()
{
    //if we have reached forcebar capacity
    if(level<10)
    {
        //send a signal to the player so the player can start shooting out the force
        emit forceObtained();

     }
    //if we have not reached capacity
    else
        //grow the force bar
        level=level-20;

    //repaint forceBar
    repaint();


}

/** This function is connected to a slot that is called whenever the player shoots out the force, and decreases
 * the remaining force displayed on the force bar
*/
void ForceBar::decreaseForce()
{
    //decrease the force bar level
    level=level+30;
    //if we have depleted the force completely
    if(level>180)
    {
        //send a signal to the player letting the player know they can no longer send force
        emit forceDepleted();
    }

    //repaint forcebar
    repaint();

}

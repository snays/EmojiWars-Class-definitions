/** @class forcebar
       @brief Contains the class declarations for the forcebar widget
       @author Sneha Belkhale
       @date January 26, 2016

      The forcebar is on the right side of the game window interface, and increases every time the player destroys an alien. Once the
      forcebar reaches maximum capacity, it resets, and allows the user to shoot out the force for a period of time by pressing a.

*/
#ifndef FORCEBAR_H
#define FORCEBAR_H

#include <QWidget>

namespace Ui {
class ForceBar;
}

class ForceBar : public QWidget
{
    Q_OBJECT

public:
    //constructor
    explicit ForceBar(QWidget *parent = 0);
    //destructor
    ~ForceBar();
    //paintEvent to repaint the forcebar
    void paintEvent(QPaintEvent*);
    //integer to hold current level of force
    int level;
public slots:
    //called whenever the player destroys an alien
    void gainForce();
    void decreaseForce();
signals:
    //signal sent to player when forcebar is at capacity
    void forceObtained();
    //signal sent to player when forcebar is empty
    void forceDepleted();

private:
    Ui::ForceBar *ui;
};

#endif // FORCEBAR_H

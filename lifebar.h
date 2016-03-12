/** @class lifebar
       @brief Contains the class declarations for the lifebar widget
       @author Sneha Belkhale
       @date January 26, 2016

      the lifebar is on the top left of the game window, and keeps track of how many lives the player has left
      before the game is over (starting with 4).
*/
#ifndef LIFEBAR_H
#define LIFEBAR_H

#include <QObject>
#include <QWidget>

class lifebar : public QWidget
{
    Q_OBJECT
public:
    //constructor
    explicit lifebar(QWidget *parent = 0);
    //paintevent that changes #of lives displayed on lifebar
    void paintEvent(QPaintEvent*);

signals:
    //signal sent when lives are out
    void gameOver(int);

public slots:
    //called when the player is hit by an alien
    void loselife();

private:
    //variable to keep track of number of lives remaining
    int numberOfLives;

};

#endif // LIFEBAR_H

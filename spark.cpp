/** @file spark.cpp
       @brief Contains the class definitions for the spark class
       @author Sneha Belkhale
       @date January 26, 2016

      Contains the definitions of the initial constructor for the spark that is shown when the player is hit by a bullet.
      Also contains a removeSpark() slot connected to a timer so the spark is removed from the scene after .5 seconds

*/
#include "bullet.h"
#include "spark.h"
#include "emoji.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QList>

/**
 * The constructor of a spark pixmap item, sets the position to exactly where the player was
 * when the wound ocurred.
 * @param x the x position of the player at the time of bullet wound
 * @param y the y position of the player at the time of bullet wound
 */
spark::spark(qreal x, qreal y)
{
    //link pixmap item to the spark pixmap
    QPixmap spark_pix=QPixmap(":/image/spark.png");
    setPixmap(spark_pix);
    //set position
    setPos(x,y);

    //connect spark to a timer so that it is deleted in half a second
    QTimer*deleteSpark=new QTimer(this);
    connect(deleteSpark,SIGNAL(timeout()),this,SLOT(removeSpark()));
    //delete after half a second
    deleteSpark->start(500);

}

/**
 * This function is called by a timer, 30 seconds after the spark is created, and removes the spark from the scene.
 */
void spark::removeSpark()
{
    //remove spark from scene
    scene()->removeItem(this);
    //delete heap memory
    delete this;

}

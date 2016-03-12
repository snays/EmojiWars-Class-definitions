/** @class spark
       @brief Contains the class declarations for the spark pixmap item.
       @author Sneha Belkhale
       @date January 26, 2016

      A new instance of this class is generated whenever the player is hit by an enemy bullet. It's only purpose is to make clear
      that the player was hit by showing a *spark*

*/
#ifndef SPARK_H
#define SPARK_H

#include<QGraphicsItem>
#include<QObject>

class spark:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    //constructor
    spark(qreal x, qreal y);
public slots:
    //slot to remove the spark after half a second of creation
    void removeSpark();
};

#endif // SPARK_H

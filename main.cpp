/** @file main.cpp
       @brief Creates a MainWindow object and makes it visible
       @author Sneha Belkhale
       @date January 26, 2016

      The MainWindow object will display the initial game settings window for emoji-wars.
*/
#include "mainwindow.h"
#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //create and show initial game settings window
    MainWindow w;
    w.show();


    return a.exec();
}

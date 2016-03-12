/** @class mainwindow
       @brief Contains the class declarations for the initial emoji-wars game settings window.
       @author Sneha Belkhale
       @date January 26, 2016

      Contains the standard constructors, and destructors. The main window also has a button that when clicked,
      opens a new window to begin the game.
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //constructor
    explicit MainWindow(QWidget *parent = 0);
    //destructor
    ~MainWindow();
    static int emoji_int;
    static int level_int;

private slots:
    //the button action to begin the game
    void on_pushButton_clicked();

    //the button action to pop up instructions
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

};


#endif // MAINWINDOW_H

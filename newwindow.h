/** @class newwindow
       @brief Contains the class declarations for the main emoji-wars game window.
       @author Sneha Belkhale
       @date January 26, 2016

      Contains the constructor and destructor for the main game window. The constructor for the game window
      takes care of displaying the main components of the game.
*/
#ifndef NEWWINDOW_H
#define NEWWINDOW_H

#include <QMainWindow>
#include <QString>


namespace Ui {
class NewWindow;
}

class NewWindow : public QMainWindow
{
    Q_OBJECT

public:
    //constructor
    explicit NewWindow(QWidget *parent = 0);
    //destructor
    ~NewWindow();
    //create emoji
    void setEmoji(int i);
    //show trooper level message to player
    void showTrooperLevel();
    //show kylo level message to player
    void showKyloLevel();
    //show kylo enemy life status
    void showKyloHarmed(int status);
    //close event
    void closeEvent (QCloseEvent *event);
    //timer for generating aliens
    QTimer* timer;


public slots:
    //slot to end game
    void warningGameOver(int);
    //slot to show force bar is enabled
    void show_force_message();
    //slot to say force bar is disabled
    void revert_force_message();


private:
    Ui::NewWindow *ui;

};

#endif // NEWWINDOW_H

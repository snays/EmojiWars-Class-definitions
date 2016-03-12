/** @file newwindow.cpp
       @brief Contains the class definitions for the emoji-wars main game window.
       @author Sneha Belkhale
       @date January 26, 2016

      Contains an initial constructor for the graphics on the main game window, and destructors.

*/
#include "newwindow.h"
#include "mainwindow.h"
#include "emoji.h"
#include "force.h"
#include "trooper.h"
#include "ui_newwindow.h"
#include <QLabel>
#include <QWidget>
#include <QPixmap>
#include <iostream>
#include <QGraphicsScene>
#include <QTimer>
#include <QMessageBox>
#include <string>
/** Constructor for the main emoji-wars game window.
    this constructor sets up the initial components of the game window, such as the grid
    label battleground, lifeline labels, inspirational messages, and initial empty force bar. More importantly,
    the constructor sets up the Graphics View with a QGraphicsScene where the players can operate.
*/
NewWindow::NewWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewWindow)
{
    ui->setupUi(this);
    //create a font for the labels
    QFont f( "PT Mono", 11);

    //set background color of new window
    this->setStyleSheet("background-color: black");

    //create an empty force bar
    ui->force->setStyleSheet("border-width: 2px; border-color: green;border-style:outset;");

    //set label text to be white so it shows up on the black background
    ui->label->setStyleSheet("QLabel { color : white; }");
    ui->label_7->setStyleSheet("QLabel { color : white; }");
    ui->label_2->setStyleSheet("color: white; background: solid green;");
    ui->kyloStatus->setStyleSheet("QLabel { color : white; }");
    ui->kyloStatus->hide();

    //set all label fonts to PT Mono
    ui->label->setFont(f);
    ui->label_7->setFont(f);
    ui->label_2->setFont(f);
    ui->kyloStatus->setFont(QFont( "PT Mono", 13,QFont::Bold));

    //create a new QGraphicsScene for main contents of game
    QGraphicsScene* scene=new QGraphicsScene();

    //Create a pixmap with the space background and add to Graphics scene
    QPixmap p=QPixmap(":/image/space.jpg");
    scene->setBackgroundBrush(p);

    //generate a new player (of desired icon) to add to the Graphics scene
    emoji* player=new emoji(MainWindow::emoji_int,this);
    scene->addItem(player);

    //put the player in focus so that it can respond to keyboard inputs later
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    //set scene of our graphics view
    ui->graphicsView->setScene(scene);

    //connect the timer to a function that generates enemy aliens on the board
    timer=new QTimer();
    QObject::connect(timer, SIGNAL(timeout()),player,SLOT(generateAliens()));
    //generate an enemy alien every x seconds
    timer->start(2000);


    //connect so that when the player destroys an alien, the force bar increases
    QObject::connect(player,SIGNAL(hit()),ui->force_bar,SLOT(gainForce()));
    //connect so that when player is hit by a bullet, the life bar displays one less life
    QObject::connect(player,SIGNAL(lostlife()),ui->lifeline,SLOT(loselife()));
    //connect so that when the player has no lives left, the game window sends a message to the user that the game is over
    QObject::connect(ui->lifeline,SIGNAL(gameOver(int)),this,SLOT(warningGameOver(int)));
    //connect so that when forcebar reaches capacity, the player is allowed to shoot out the force
    QObject::connect(ui->force_bar,SIGNAL(forceObtained()),player,SLOT(hasForce()));
    //connect so that when forcebar is empty, the player can no longer have ability to shoot force
    QObject::connect(ui->force_bar,SIGNAL(forceDepleted()),player,SLOT(hasForce()));
    //connect so that when the player shoots out the force, the force bar decreases
    QObject::connect(player,SIGNAL(force_used()),ui->force_bar,SLOT(decreaseForce()));


    //connect so that when forcebar reaches capacity, the player is allowed to shoot out the force
    QObject::connect(ui->force_bar,SIGNAL(forceObtained()),this,SLOT(show_force_message()));

    //connect so that when forcebar is empty, the player can no longer have ability to shoot force
    QObject::connect(ui->force_bar,SIGNAL(forceDepleted()),this,SLOT(revert_force_message()));
}


/** Standard destructor for our main emoji-wars game window
*/
NewWindow::~NewWindow()
{
    delete ui;
}
/** Function that is called when the player has killed enough troopers to advance to the kylo level.
 * it essentialy changes the level label to inform user of current level.
*/
void NewWindow::showKyloLevel()
{
    //set text coloring
    ui->label_2->setStyleSheet("color: white; background: solid blue;");
    //set text
    ui->label_2->setText("YOU HAVE ADVANCED TO THE KYLO LEVEL. kill him with the force");
}


/** Function that is called when kylo loses a life. It displays a message to the screen informing the player of Kylo's life status.
    @param status - integer value that corresponds to kylo's lives remaining
*/
void NewWindow::showKyloHarmed(int status)
{
    //show kylo status message
    ui->kyloStatus->show();
    //if kylo has 2 lives remaining
    if(status==2)
        ui->kyloStatus->setText("kylo is stronger than you think");
    //if kylo has 1 life remaining
    if(status==1)
        ui->kyloStatus->setText("kylo is weaker now, but still alive");
    //if kylo is dead
    if(status==0)
        ui->kyloStatus->setText("YOU WIN");

}

/** Function that is called when the player has killed enough alien levels to advance to the trooper level.
 * it essentialy changes the level label to inform user of current level.
*/
void NewWindow::showTrooperLevel()
{
    //set text color
    ui->label_2->setStyleSheet("color: white; background: solid red;");
    //set color
    ui->label_2->setText("YOU HAVE ADVANCED TO THE TROOPER LEVEL. KILL TROOPERS WITH YOUR FORCE (use A,D,S,W to shoot right,left,down,up ).");
}

/** Function that is called when the player closes the main window. It essentially just resets the emoji integer, level integer
 * and number of killed troopers to 0.
*/
#include <QCloseEvent>
void NewWindow::closeEvent (QCloseEvent *event)
{
    //reset all variables upon close of main window
    MainWindow::level_int=0;
    MainWindow::emoji_int=0;
    force::numberOfKilledTroopers=0;

}


/** Function that is called when the player has run out of lives, or when kylo dies. It displays a new pop-up message box and hides the
    graphicsview so that the user can no longer see the game window.

    @param i - integer that is 0 if the player lost and 1 if the player one
*/

void NewWindow::warningGameOver(int i)
{
    //create new message box
    QMessageBox* gameOver= new QMessageBox();
    //make visible
    gameOver->show();

    //set text of message box to let player know the game is over

    //if the player lost set text accordingly
    if(i==0)
        gameOver->setText("Much to learn, you still have.");

    //if the player won set text accordingly
    if(i==1)
        gameOver->setText("Congratulations, the resistance prevails! The force is strong with this one.");

    //reset level and emoji cosen
    MainWindow::level_int=0;
    MainWindow::emoji_int=0;

    this->close();
}
/** Function that is called when the player has killed enough aliens and reached force-bar capacity. It displays text above the force bar to let the
 * user know that they now have the force.
*/
void NewWindow::show_force_message()
{
    ui->label_7->setText("USE YOUR FORCE");
}
/** Function that is called when the player has used up all of its force. It displays text above the force bar to let the
 * user know that they must now replenish their force bar.
*/
void NewWindow::revert_force_message()
{
    ui->label_7->setText("powerful you are becoming");
}




/** @file mainwindow.cpp
       @brief Contains the class definitions for the initial emoji-wars game settings window.
       @author Sneha Belkhale
       @date December 20, 2016

      Contains the standard constructors, and destructors. The main window also has a button that when clicked,
      opens a new window to begin the game.
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newwindow.h"
#include <QMessageBox>
#include <QPixMap>


/** Standard constructor for a window
*/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //link up the pixmaps to the correct labels
    QPixmap pizza_pix(":/image/pizza.png");
    ui->pizza->setPixmap(pizza_pix);

    QPixmap diva_pix(":/image/diva.png");
    ui->diva->setPixmap(diva_pix);

    QPixmap popo_pix(":/image/popo.png");
    ui->popo->setPixmap(popo_pix);
    ui->popo->setScaledContents(true);

}

/** Standard destructor for a window
 * to prevent memory leaks
*/

MainWindow::~MainWindow()
{
    delete ui;
}

/** This function is called whenever the begin button on the initial window is clicked, and starts the game. It essentially
    creates a new NewWindow window (which is the emoji-wars game window), and shows it to the screen so the user can start
    playing emoji-wars
*/
void MainWindow::on_pushButton_clicked()
{
    bool playerChosen=false;
    bool levelChosen=false;
    //increment the static variable emoji_int to help us determine in the new window
    //which emoji icon the user has selected
        if(ui->radioButton->isChecked())
        {
            emoji_int++;
            playerChosen=true;
        }

        if(ui->radioButton_2->isChecked())
        {
            emoji_int+=2;
            playerChosen=true;
        }

        if(ui->radioButton_3->isChecked())
        {
            emoji_int+=3;
            playerChosen=true;
        }


    //increment the static variable emoji_int to help us determine in the new window
    //which emoji icon the user has selected
        if(ui->radioButton_4->isChecked())\
        {
            level_int+=3;
            levelChosen=true;
        }

        if(ui->radioButton_5->isChecked())
        {
            level_int+=2;
            levelChosen=true;
        }

        if(ui->radioButton_6->isChecked())
        {
            level_int++;
            levelChosen=true;
        }

    if(levelChosen&&playerChosen)
    {
        //create new NewWindow
        NewWindow* nw=new NewWindow();
        //show window to screen
        nw->show();
    }
    else
    {
        //create and show new message box
        QMessageBox* error= new QMessageBox();
        error->show();


        //set text of message box with instructions

        error->setText("please select your player and level!");
        MainWindow::emoji_int=0;
        MainWindow::level_int=0;


    }


}

/** This function is called whenever the instructions button on the initial window is clicked, and pops up a message box
 * with instructions on how to play the emoji wars game
*/
void MainWindow::on_pushButton_2_clicked()
{
    //create and show new message box
    QMessageBox* inst= new QMessageBox();
    inst->show();


    //set text of message box with instructions

    inst->setText("Instructions: \n \nFirst chose your desired player emoji, and skill level. Note that chosing a higher skill level will"
                  " give you faster movement but also more difficult enemies to face! \n \n First Round: \n Destroy the aliens by piercing them with your lightsaber. Watch out for their bullets as they will"
                  " damage you. As you defeat aliens, your force bar will increase and when you have reached maximum force, you will be able to emit the force"
                  " in any direction (by pressing A,S,D, or W).\n \n"
                  "Second Round:\n Here come the troopers, slightly more dangerous as you will die if they touch you. The only way to kill them is with the force."
                  "Keep killing aliens to replenish your force bar!\n"
                  "\n \n Third Round: \n Destroy Kylo Ren, but one can only do so if you have the force.Be careful because Kylo Ren shoots out his own force in all "
                  " directions which will destroy you. Kylo Ren is also stronger than you think, and will not die by just one force attack.  \n "

                  "\n KEY: \n arrows - move emoji in corresponding direction \n A - shoot force left \n D-shoot force right \n W - shoot force up \n S - shoot force down"
                  "\n \n do or do not there is no try.");
}


//initialize the static emoji_int variable to 0
int MainWindow::emoji_int=0;
//initialize the static emoji_int variable to 0
int MainWindow::level_int=0;

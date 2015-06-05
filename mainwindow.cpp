#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_gameboard.h"
//#inlude "instruction.h"
#include "ui_instruction.h"
#include <QWidget>
#include <QMessageBox>

/**
 * Mainwindow constructor
 **/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    charlie = grumpy = nyancat = mouse = dog = human = false;
    connect(ui->button_charlie, SIGNAL(clicked()), this, SLOT(charlie_clicked()));
    connect(ui->button_grumpy, SIGNAL(clicked()), this, SLOT(grumpy_clicked()));
    connect(ui->button_nyancat, SIGNAL(clicked()), this, SLOT(nyancat_clicked()));
    connect(ui->buttonmouse, SIGNAL(clicked()), this, SLOT(mouse_clicked()));
    connect(ui->buttondog, SIGNAL(clicked()), this, SLOT(dog_clicked()));
    connect(ui->buttonhuman, SIGNAL(clicked()), this, SLOT(human_clicked()));
}

/**
 * Mainwindow destructor
 **/
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * The pushbutton start changes mainwindow to gameboard
 */
void MainWindow::on_startbutton_clicked()
{
       //check what kind of cat/enemy the player chooses to initialize the right gameboard
       if(charlie == true && mouse ==true)
           board = new gameboard(this, "charlie","mouse");
       if(grumpy == true && mouse ==true)
           board = new gameboard(this, "grumpy","mouse");
       if(nyancat == true && mouse ==true)
           board = new gameboard(this, "nyancat","mouse");
       if(charlie == true && dog ==true)
           board = new gameboard(this, "charlie","dog");
       if(grumpy == true && dog ==true)
           board = new gameboard(this, "grumpy","dog");
       if(nyancat == true && dog ==true)
           board = new gameboard(this, "nyancat","dog");
       if(charlie == true && human ==true)
           board = new gameboard(this, "charlie","human");
       if(grumpy == true && human ==true)
           board = new gameboard(this, "grumpy","human");
       if(nyancat == true && human ==true)
           board = new gameboard(this, "nyancat","human");


       this->setCentralWidget(board);
}


/**
 * @brief MainWindow::charlie_clicked check if player picked charlie
 */
void MainWindow::charlie_clicked()
{
    charlie = true;
}

/**
 * @brief MainWindow::grumpy_clicked check if player picked grumpy cat
 */
void MainWindow::grumpy_clicked()
{
    grumpy = true;
}

/**
 * @brief MainWindow::nyancat_clicked check if player picked nyancat
 */
void MainWindow::nyancat_clicked()
{
    nyancat = true;
}

/**
 * @brief MainWindow::mouse_clicked check if player picked mouse dog as enemy
 */
void MainWindow::mouse_clicked()
{
    mouse = true;
}

/**
 * @brief MainWindow::dog_clicked check if player picked dog as enemy
 */
void MainWindow::dog_clicked()
{
    dog = true;
}

/**
 * @brief MainWindow::human_clicked check if player picked human as enemy
 */
void MainWindow::human_clicked()
{
    human = true;
}

/**
 * @brief MainWindow::game_over changes window screen when game is over
 */
void MainWindow::game_over() {
    // Take the current board game out of the central widget of MainWindow
    QWidget* wid = this->centralWidget();
    wid->setParent(NULL);

    // Reset the MainWindow with the initial startup screen
    ui->setupUi(this);

    // Reset the cat/enemy conditions
    charlie = grumpy = nyancat = mouse = dog = human = false;
    connect(ui->button_charlie, SIGNAL(clicked()), this, SLOT(charlie_clicked()));
    connect(ui->button_grumpy, SIGNAL(clicked()), this, SLOT(grumpy_clicked()));
    connect(ui->button_nyancat, SIGNAL(clicked()), this, SLOT(nyancat_clicked()));
    connect(ui->buttonmouse, SIGNAL(clicked()), this, SLOT(mouse_clicked()));
    connect(ui->buttondog, SIGNAL(clicked()), this, SLOT(dog_clicked()));
    connect(ui->buttonhuman, SIGNAL(clicked()), this, SLOT(human_clicked()));

    repaint();
    //QCoreApplication::processEvents();
}


/**
 * @brief MainWindow::on_instruction_button_clicked opens instruction window
 */
void MainWindow::on_instruction_button_clicked()
{
    iwindow = new instruction();
    iwindow->show();

}

#include "gameboard.h"
#include "ui_gameboard.h"
#include <QLabel>
#include <QGridLayout>
#include <QString>
#include <QPoint>
#include <QKeyEvent>
#include <QTime>
#include <QTimer>
#include <QWidget>
#include <QPushButton>
#include <mainwindow.h>
#include <QMessageBox>
#include <vector>
#include <algorithm>
//#include <random>


/**
  Gameboard constructor that sets the board with the cat and enemy that the player chooses
**/
gameboard::gameboard(QWidget *parent, QString cat, QString enemy) :
    QWidget(parent),
    ui(new Ui::gameboard), cat_name(cat), enemy_name(enemy)
{

        //**CODE BELOW SETS THE TOP BAR WITH CAT LIVES AND LEVEL NUMBER**//
        Top = new QWidget;
        Top->setStyleSheet("QLabel { background-color: white; color: black; }");
        top_bar = new QHBoxLayout(Top);

        //set cat lives image and item image according to the type of cat player chooses
        if(cat=="charlie"){
            cat_lives_image = new QPixmap(":/image/charlielife.jpg");
            item_image = new QPixmap(":/image/yarns.jpg");
        }
        if(cat=="grumpy"){
            cat_lives_image = new QPixmap(":/image/grumpylife.jpg");
            item_image = new QPixmap(":/image/scatfood.jpg");
        }
        if(cat=="nyancat"){
            cat_lives_image = new QPixmap(":/image/nyancatlife.jpg");
            item_image = new QPixmap(":/image/poptart2s.jpg");
        }

        // Player has a totla of 4 lives: 3 lives listed and 1 life is currently playing
        lives_remaining = 4;
        lives = new QLabel*[lives_remaining-1];

        // Set the labels to have the cat image, add to the top bar layout.
        for(size_t i=0;i<lives_remaining-1;i++) {
            lives[i] = new QLabel;
            lives[i]->setPixmap(*cat_lives_image);
            //lives[i]->setMinimumSize(40,40);
            //lives[i]->setMaximumSize(40,40);
            lives[i]->setScaledContents(true);
            top_bar->addWidget(lives[i]);
        }

        //add horizontal space
        QSpacerItem* horizontal_space = new QSpacerItem(10,10);
        top_bar->addSpacerItem(horizontal_space);

        //set level number
        QLabel* level_text = new QLabel("Level: ");
        level_int = 1; //start with level 1
        level_value = new QLabel(QString::number(level_int));

        //add horizontal space before next label
        QSpacerItem* horizontal_space_2 = new QSpacerItem(*horizontal_space);
        top_bar->addSpacerItem(horizontal_space_2);
        top_bar->addWidget(level_text);
        top_bar->addWidget(level_value);


    /**CODE BELOW SETS THE GAMEBOARD**/

    //sets the cat image according to player choice
    if(cat=="charlie"){
        cat_image = new QPixmap(":/image/scharlie.jpg");
    }
    if(cat=="grumpy"){
        cat_image = new QPixmap(":/image/grumpys.jpg");
    }
    if(cat=="nyancat"){
        cat_image = new QPixmap(":/image/snyan.jpg");
    }
    if(enemy=="mouse"){
        enemy_image = new QPixmap(":/image/smouse.jpg");
    }

    if(enemy=="dog"){
        enemy_image = new QPixmap(":/image/sdog.jpg");
    }
    if(enemy=="human"){
        enemy_image = new QPixmap(":/image/sdeedee.gif");
    }

        //constructs the gameboard properties
        Board = new QWidget;
        square_size = 50;
        board_size = 10;
        Board->setFixedSize(500,500);
        labels = new QLabel*[board_size*board_size]; //initialize board with 10 by 10 labels

        QGridLayout *SquareGrid = new QGridLayout(Board);

        SquareGrid->setGeometry(QRect());
        SquareGrid->setSpacing(0);

        //initialize vector with 1s to indicate that the items have not been eaten by the cat
        for(size_t i=0; i<board_size*board_size; ++i){
            food_eaten.push_back(1);
        }

        // Create each label for the board, initialize with item images
        for(size_t i=0;i<board_size;i++) {
            for(size_t j=0;j<board_size;j++) {
                // Create label and set properties.
                labels[i*board_size+j] = new QLabel;
                labels[i*board_size+j]->setStyleSheet("QLabel { background-color : white; color : white; }");
                labels[i*board_size+j]->setPixmap(*item_image);
                labels[i*board_size+j]->setFrameStyle(3);
                labels[i*board_size+j]->setAlignment(Qt::AlignCenter);
                labels[i*board_size+j]->setFixedSize(50,50);
                // Add label to the layout
                SquareGrid -> addWidget(labels[i*board_size+j] ,i,j);

            }
        }

        // Initialize cat at the top left corner, coordinate (0,0).
         cat_position = new QPoint(0,0);
         labels[0]->setPixmap(*cat_image);
         labels[0]->setScaledContents(true);

           /**CODE BELOW COMBINES TOP BAR WITH GAMEBOARD**/

           // Create a vertical box layout for the two pieces
           QVBoxLayout *piece_together = new QVBoxLayout;

           piece_together->addWidget(Top,0,Qt::AlignCenter);
           piece_together->addWidget(Board,0,Qt::AlignCenter);

           //add quit button at the bottom of the window
           QPushButton* quit = new QPushButton("Quit");
           quit->setGeometry(QRect(QPoint(100, 100),
                                   QSize(80, 50)));
           QObject::connect(quit, SIGNAL(clicked()), parent, SLOT(game_over()));

           piece_together->addWidget(quit);

           this->setLayout(piece_together);
           this->setStyleSheet("QLabel { background-color : black; color : white; }");


        /**CODE BELOW SETS THE ENEMY NUMBER AND THEIR RANDOM LOCATION*/
         //set enemy number to 4 at first level
         enemy_number = 4;
         enemy_positions = new QPoint[enemy_number];

         //initialize each enemy to appear at random locations on the board
         qsrand(QTime::currentTime().msec());

         enemy_positions[0].setX(qrand() % board_size);
         enemy_positions[0].setY(qrand() % board_size);

         enemy_positions[1].setX(qrand() % board_size);
         enemy_positions[1].setY(qrand() % board_size);

         enemy_positions[2].setY(qrand() % board_size);
         enemy_positions[2].setX(qrand() % board_size);

         enemy_positions[3].setY(qrand() % board_size);
         enemy_positions[3].setX(qrand() % board_size);

         QCoreApplication::processEvents();
         repaint();

         //set enemy speed and update their random movements
         QTimer *timer = new QTimer(this);
         connect(timer, SIGNAL(timeout()), this, SLOT(updateEnemy()));
         enemy_speed = 400;
         timer->start(enemy_speed);
}

     /**
     * @brief gameboard::paintEvent paints the cat and enemies on board
     * @param e is the QPaintEvent pointer object
     */
    void gameboard::paintEvent(QPaintEvent* e){
        //get the coordinates of the cat
        int x = cat_position->rx();
        int y = cat_position->ry();

        //set cat image
        labels[y*board_size+x]->setPixmap(*cat_image);
        food_eaten[y*board_size+x] = 0;
        labels[y*board_size+x]->setScaledContents(true);

        //get coordinates of each enemy and set enemy image
        for(size_t i=0;i<enemy_number;i++) {
            int px = enemy_positions[i].rx();
            int py = enemy_positions[i].ry();

            if(px >= 0 && py >= 0 && px < (int)board_size && py < (int)board_size) {
                labels[py*board_size+px]->setPixmap(*enemy_image);
                labels[py*board_size+px]->setScaledContents(true);
            }
        }
    }

    /**
     * @brief gameboard::showEvent shows the gameboard event
     * @param e is the QShowEvent pointer object
     */
    void gameboard::showEvent(QShowEvent *e) {

        this->activateWindow();
        this->setFocus();
        QWidget::showEvent(e);
    }


    /**
     * @brief gameboard::keyPressEvent defines what happens when the player presses certain keys
     * @param event is the QKeyEvent pointer object
     */
    void gameboard::keyPressEvent(QKeyEvent *event) {
        //get the coordinates of the cat
        int x = cat_position->rx();
        int y = cat_position->ry();

        switch (event->key()) {
        case Qt::Key_Left:
            if(cat_position->rx() != 0)
                updateCat(x,y,x-1,y);

            break;
        case Qt::Key_Right:
            if(cat_position->rx() != board_size-1)
                updateCat(x,y,x+1,y);

            break;
        case Qt::Key_Up:
            if(cat_position->ry() != 0)
                updateCat(x,y,x,y-1);

            break;
        case Qt::Key_Down:
            if(cat_position->ry() != board_size-1)
                updateCat(x,y,x,y+1);

            break;


        default:
            QWidget::keyPressEvent(event);
        }

        //check if cat is caught by any enemy
        for(size_t i=0; i<enemy_number; ++i){
            int ex = enemy_positions[i].rx();
            int ey = enemy_positions[i].ry();
            if(x == ex && y == ey)
                catCaught();
        }

        //if all items have been eaten, advance to the next level
        auto found = std::find(food_eaten.begin(), food_eaten.end(),1);
        if (found==food_eaten.end()){
            advanceLevel();
        }

        repaint();
        QCoreApplication::processEvents();

        return;
    }

    /**
     * @brief gameboard::updateCat updates the cat position
     * @param px is the current x coordinate of cat
     * @param py is the current y coordinate of cat
     * @param nx is new x coordinate of cat
     * @param ny is new y coordinate of cat
     */
    void gameboard::updateCat(int px, int py, int nx, int ny) {
        labels[py*board_size+px]->clear();
        food_eaten[py*board_size+px] = 0;

        cat_position->setX(nx);
        cat_position->setY(ny);

        repaint();
    }

    /**
     * @brief gameboard::advanceLevel advances to the next level
     */
    void gameboard::advanceLevel() {
        //reset remaining lives
        lives_remaining = 4;

        //reset remaining lives images
        for(size_t i=0;i<lives_remaining-1;i++) {
            //lives[i] = new QLabel;
            lives[i]->setPixmap(*cat_lives_image);
            //lives[i]->setMinimumSize(40,40);
            //lives[i]->setMaximumSize(40,40);
            lives[i]->setScaledContents(true);
            //top_bar->addWidget(lives[i]);
        }

        //increase level number
        level_int++;
        level_value->setText(QString::number(level_int));

        //increase number of enemies and reset their locations on board
        enemy_number++;
        enemy_positions = new QPoint[enemy_number];

        enemy_positions[0].setX(qrand() % board_size);
        enemy_positions[0].setY(qrand() % board_size);

        enemy_positions[1].setX(qrand() % board_size);
        enemy_positions[1].setY(qrand() % board_size);

        enemy_positions[2].setY(qrand() % board_size);
        enemy_positions[2].setX(qrand() % board_size);

        enemy_positions[3].setY(qrand() % board_size);
        enemy_positions[3].setX(qrand() % board_size);

        //redraw enemies
        for(size_t i=0;i<enemy_number;++i) {
            int px = enemy_positions[i].rx();
            int py = enemy_positions[i].ry();

            if(px >= 0 && py >= 0 && px < (int)board_size && py < (int)board_size) {
                labels[py*board_size+px]->setPixmap(*enemy_image);
                labels[py*board_size+px]->setScaledContents(true);
            }
        }

        QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(updateEnemy()));

        //increase speed of enemies
        enemy_speed -=100;
        //std::cout<<"enemy speed="<<enemy_speed<<std::endl;
        timer->start(enemy_speed);

        //reset labels for the board
        for(size_t i=0;i<board_size;i++) {
            for(size_t j=0;j<board_size;j++) {
                // Create label and set properties.
                //labels[i*board_size+j] = new QLabel;
                labels[i*board_size+j]->setStyleSheet("QLabel { background-color : white; color : white; }");
                labels[i*board_size+j]->setPixmap(*item_image);
                labels[i*board_size+j]->setFrameStyle(3);
                labels[i*board_size+j]->setAlignment(Qt::AlignCenter);
                labels[i*board_size+j]->setFixedSize(50,50);
                //food_eaten[i].pushback(1);
            }
        }

        //re-initialize vector with 1s
        std::fill(food_eaten.begin(),food_eaten.end(),1);

        repaint();
        QCoreApplication::processEvents();

    }

    /**
     * @brief gameboard::updateEnemy updates the movement of the enemies
     */
    void gameboard::updateEnemy() {

       qsrand(QTime::currentTime().msec());
       int low = 0;
       int high = 1;
       double p = qrand() % ((high + 1) - low) + low;
       int x_or_y = qrand() % ((high + 1) - low) + low;

       for(size_t i=0;i<enemy_number;i++) {
              int px = enemy_positions[i].rx();
              int py = enemy_positions[i].ry();
              //std::cout<<px<<","<<py<<std::endl;

              //check if item is eaten by cat or not to determine what image to update
              if(px>=0 && py >= 0 && px<(int)board_size && py<(int)board_size) {
                  if(food_eaten[py*board_size+px] == 0){ //if label is empty, keep it empty
                      labels[py*board_size+px]->clear();
                  }
                  else{
                      labels[py*board_size+px]->setPixmap(*item_image); //reset label with item if still not eaten by cat
                  }
              }

              int nx = px;
              int ny = py;

              //move enemies randomly on board
              if(p < 0.1) {
                  int increment = qrand() % ((high + 1) - low) + low;
                  if(x_or_y == 0) {
                      nx = px + 2*increment-1;
                      if(nx >= 0 && nx < (int)board_size)
                          enemy_positions[i].setX(nx);
                  }
                  else {
                      ny = py + 2*increment-1;
                      if(ny >= 0 && ny < (int)board_size)
                          enemy_positions[i].setY(ny);

                  }

              }

          }

          repaint();
          QCoreApplication::processEvents();


}

 /**
 * @brief gameboard::catCaught if cat is caught by an enemy
 */
void gameboard::catCaught() {
    //if still have lives, subtract one life
    if(lives_remaining > 1) {
          lives_remaining--;
          lives[lives_remaining-1]->clear();
          //std::cout<<lives_remaining<< "cleared"<<std::endl;
            }
    //if not more lives, game over!
    else{
        //std::cout<<"game over!"<<std::endl;
        QMessageBox* notice = new QMessageBox;
        notice->setText("You Got Caught! Game Over!");
        notice->show();
        //std::cout<<"game over!"<<std::endl;
        game_over();
        repaint();
        QCoreApplication::processEvents();
        //QObject::connect(quit, SIGNAL(clicked()), parent, SLOT(game_over()));
   }
}

/**
 * @brief gameboard::~gameboard destructor
 */
gameboard::~gameboard()
{
    delete ui;
}

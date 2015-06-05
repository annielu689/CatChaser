#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <QLabel>
#include <QWidget>
#include <QPixmap>
#include <QPoint>
#include <iostream>
#include <QMap>
#include <vector>
#include <QHBoxLayout>

namespace Ui {
class gameboard;
}

class gameboard : public QWidget
{
    Q_OBJECT

public:
    explicit gameboard(QWidget *parent = 0, QString cat = "charlie", QString enemy = "mouse");
    ~gameboard();
    void paintEvent(QPaintEvent* e);
    void keyPressEvent(QKeyEvent *event);
    void showEvent(QShowEvent *e);
    void updateCat(int px, int py, int nx, int ny);

public slots:
    void updateEnemy();
    void catCaught();
    void advanceLevel();

signals:
    void game_over();

private:
    Ui::gameboard *ui;

    QPixmap* cat_lives_image;

    QPixmap* enemy_image;
    QPixmap* cat_image;
    QPixmap* item_image;

    QString cat_name;
    QString enemy_name;

    QPoint* cat_position;
    QPoint* enemy_positions;
    int enemy_number;
    int enemy_speed;

    std::vector<int> food_eaten; //vector to check if item is acquired by cat


    // Top bar variables
    QHBoxLayout *top_bar;
    QLabel* level_value;
    int level_int;
    QWidget* Top;
    unsigned int lives_remaining;
    QLabel** lives;

    //board variables
    QWidget *Board;
    int board_size;
    int square_size;
    QLabel** labels;

};

#endif // GAMEBOARD_H

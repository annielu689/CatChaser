#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <gameboard.h>
#include <instruction.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void on_startbutton_clicked();

    void charlie_clicked();
    void grumpy_clicked();
    void nyancat_clicked();
    void mouse_clicked();
    void dog_clicked();
    void human_clicked();

    void game_over();

private slots:

    void on_instruction_button_clicked();

private:
    Ui::MainWindow *ui;
    gameboard* board;
    instruction* iwindow;
    bool charlie, grumpy, nyancat, mouse, dog, human;
};

#endif // MAINWINDOW_H

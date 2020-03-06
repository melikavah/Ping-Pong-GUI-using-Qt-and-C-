#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class Gameplay;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void addScore(int count);



private:
    Ui::MainWindow *ui;
    Gameplay *iLoop;
    int iScore;
    int iScoreYellow;
    int iScoreRed;
    int a;


};

#endif // MAINWINDOW_H

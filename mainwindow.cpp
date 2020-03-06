#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include "gameplay.h"
#include <QPen>
#include <QResizeEvent>
#include <QDebug>
#include<iostream>
#include<QMessageBox>
#include<QProcess>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    iScore(0),
    a(0),iScoreRed(0), iScoreYellow(-1)
{
    ui->setupUi(this);
    QGraphicsScene *scene = new QGraphicsScene(this);

    QGraphicsRectItem *p1 = new QGraphicsRectItem(0, 0, 80, 20);
    p1->setBrush(QBrush(Qt::red));
    QGraphicsRectItem *p2 = new QGraphicsRectItem(0, 0, 80, 20);
    p2->setBrush(QBrush(Qt::yellow));

    QGraphicsEllipseItem *ball = new QGraphicsEllipseItem(0, 0, 15, 15);
    ball->setBrush(QBrush(Qt::magenta));
    QGraphicsLineItem*line = new QGraphicsLineItem();
    scene->addItem(line);
    line->setLine(0, 160, 400, 160);

    ui->boardView->setScene(scene);

    iLoop = new Gameplay(*scene, p1, p2, ball, this);
    QSize m(scene->sceneRect().size().width() + 10, scene->sceneRect().size().height() + 10);
    ui->boardView->setMinimumSize(m);

    resize(minimumSize());
    ui->boardView->installEventFilter(iLoop);

    QObject::connect(iLoop, SIGNAL(goal(int)),
                     this, SLOT(addScore(int)));
    if(true)
    {
        QMessageBox::information(this, tr("Start Game"), tr("You are the red player\n"
                                                            "You can move your racket by pressing right and left arrow"
                                                            "\nPress OK to start Game\nYou will win the game "
                                                            "when your score is 10"));
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::addScore(int count)
{
     iScore += count;

     if(iScore == 0)
     {

        ui->lcdNumber->display(iScoreYellow);
        ui->lcdNumber_2->display(iScoreRed);

    }

    //Scoring Red player
    if(iScore > a)
    {
        iScore += count;
        iScoreRed++;
        ui->lcdNumber_2->display(iScoreRed);
        if (iScoreRed == 10)
        {
            QMessageBox::information(this,tr("Congratulations"),tr("You won the game\npress OK to go to the NEXT LEVEL") );
            qApp->quit();
            QProcess::startDetached(qApp->arguments()[0], qApp->arguments());

        }
    }

    //Scoring Yellow player
    if(iScore < a)
    {
         count *= -1;
         iScore += count;
         iScoreYellow++;

         ui->lcdNumber->display(iScoreYellow);
         if(iScoreYellow == 10)
         {
             QMessageBox::critical(this,"Oobpss","GAME OVER");
             qApp->exit();
         }
    }
    a = iScore;

}





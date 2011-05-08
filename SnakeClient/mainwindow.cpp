#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include <QTimer>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralWidget->setFocus();

}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::keyPressEvent(QKeyEvent *key)
//{
//    switch(key->key())
//    {
//    case Qt::Key_Up:
////        ui->centralWidget->turn(JSnake::ED_UP,0);
//        break;
//    case Qt::Key_Down:
////        ui->centralWidget->turn(JSnake::ED_DOWN,0);
//        break;
//    case Qt::Key_Left:
////        ui->centralWidget->turn(JSnake::ED_LEFT,0);
//        break;
//    case Qt::Key_Right:
////        ui->centralWidget->turn(JSnake::ED_RIGHT,0);
//        break;
//    }
//}

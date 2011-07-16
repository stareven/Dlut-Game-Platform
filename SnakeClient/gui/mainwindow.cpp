#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QKeyEvent>

#include "jhallwidget.h"
#include "jsnakewidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    ui->centralWidget->setFocus();
//	JHallWidget *hall=new JHallWidget(ui->centralWidget);
//	JSnakeWidget *snake=new JSnakeWidget(ui->centralWidget);
//	ui->centralWidget->addWidget(hall);
//	ui->centralWidget->addWidget(snake);
	connect(ui->widget_hall,SIGNAL(enterGame(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));
	connect(ui->widget_snake,SIGNAL(escape(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));
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

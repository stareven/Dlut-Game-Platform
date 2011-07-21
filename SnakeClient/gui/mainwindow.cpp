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
	connect(ui->widget_hall,SIGNAL(enterGame(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));
	connect(ui->widget_snake,SIGNAL(escape(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


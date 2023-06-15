#include "mainwindow.h"
#include "./ui_mainwindow.h"
// constructor of mainwindow class (called when application starts)
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) // creates new instance of MainWindow class
{
    ui->setupUi(this);

    // center the widgets in vertical layout
    ui->centralwidget->
    ui->verticalLayout->setAlignment(ui->volumeSlider, Qt::AlignCenter);
}

MainWindow::~MainWindow()
{
    delete ui;
}


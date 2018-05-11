#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mStartStop = ui->mainToolBar->addAction("Start/Stop");
    mExportCSV = ui->mainToolBar->addAction("Export to CSV");
    mPortSetup = ui->mainToolBar->addAction("Port setup");
}

MainWindow::~MainWindow()
{
    delete ui;
}

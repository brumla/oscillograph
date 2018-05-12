#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCloseEvent>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mStartStop = ui->mainToolBar->addAction("Start/Stop");
    mExportCSV = ui->mainToolBar->addAction("Export to CSV");
    mPortSetup = ui->mainToolBar->addAction("Port setup");

    connect(mPortSetup, &QAction::triggered, [=](){
        DlgPortSetup dlg;
        mSerialPortSetup.portName = "COM3";
        dlg.setPortSetup(mSerialPortSetup);
        if(dlg.exec() == QDialog::Accepted) {
            mSerialPortSetup = dlg.portSetup();
            qDebug() << "Port setup changed: " << mSerialPortSetup;
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_Quit_triggered()
{
    close();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    int result = QMessageBox::question(this,
                                       tr("Quit"),
                                       tr("Do you want to quit the application?"),
                                       QMessageBox::Yes | QMessageBox::No);
    if(result == QMessageBox::Yes) {
        event->accept();
    }
    else {
        event->ignore();
    }
}

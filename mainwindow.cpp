#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCloseEvent>
#include <QMessageBox>

#include "src/dlgportsetup.h"

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
        dlg.exec();
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

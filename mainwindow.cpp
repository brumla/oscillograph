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

    statusBar()->showMessage(tr("Please set up the port first."));

    connect(&mSerialPort, SIGNAL(aboutToClose()), this, SLOT(on_serial_port_closing()));
    connect(&mSerialPort, SIGNAL(readChannelFinished()), this, SLOT(on_serial_port_channel_finished()));

    connect(mPortSetup, &QAction::triggered, [=](){
        // TODO Move from lambda to normal method to avoid unreadable code
        DlgPortSetup dlg;
        mSerialPortSetup.portName = "COM3";
        dlg.setPortSetup(mSerialPortSetup);
        if(dlg.exec() == QDialog::Accepted) {
            mSerialPortSetup = dlg.portSetup();
            qDebug() << "Port setup changed: " << mSerialPortSetup;

            // set up serial port
            mSerialPort.setDataBits(static_cast<QSerialPort::DataBits>(mSerialPortSetup.dataBit));
            mSerialPort.setFlowControl(static_cast<QSerialPort::FlowControl>(mSerialPortSetup.flowControl));
            mSerialPort.setParity(static_cast<QSerialPort::Parity>(mSerialPortSetup.parity));
            mSerialPort.setPortName(mSerialPortSetup.portName);
            mSerialPort.setBaudRate(static_cast<QSerialPort::BaudRate>(mSerialPortSetup.speed));
            mSerialPort.setStopBits(static_cast<QSerialPort::StopBits>(mSerialPortSetup.stopBit));

            statusBar()->showMessage(tr("Serial port setup complete"));
        }
    });

    connect(mStartStop, &QAction::triggered, [=](){
        // TODO Move from lambda to normal method to avoid unreadable code

        if(mSerialPort.isOpen()) {
            qDebug() << "Closing port";
            mSerialPort.close();
        }

        bool result = mSerialPort.open(QSerialPort::ReadWrite);
        qDebug() << "The serial port open() returns: " << result;

        if(!result) {
            QMessageBox::critical(this,
                                  tr("I/O Error"),
                                  tr("Cannot open serial port %1").arg(mSerialPort.errorString()),
                                  QMessageBox::Close);
            return;
        }

        statusBar()->showMessage(tr("Serial port opened for read-write"));
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

void MainWindow::on_serial_port_closing()
{
    statusBar()->showMessage(tr("Closing port, please wait..."));
}

void MainWindow::on_serial_port_channel_finished()
{
    statusBar()->showMessage(tr("Serial channel closed."));
}

void MainWindow::on_serial_port_readyRead()
{
    // read all the content from serial port buffer and store into the deque
    QByteArray buffer = mSerialPort.readAll();
    QByteArray::const_iterator itBuffer = buffer.constBegin();

    // and push back the received bytes intro deque
    while(itBuffer != buffer.end()) {
        dataBuffer.push_back(*itBuffer);
        itBuffer ++;
    }

    // check the deque size, if too big then remove oldest data
    int difference = dataBuffer.size() - maximumSize();
    if(difference > 0) {
        // remove the old data
        std::deque<unsigned char>::const_iterator it = dataBuffer.cbegin();

        while(it != dataBuffer.cend() && difference > 0) {
            dataBuffer.pop_front();
            difference --;
        }
    }

    // TODO: Redraw
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    int result = QMessageBox::question(this,
                                       tr("Quit"),
                                       tr("Do you want to quit the application?"),
                                       QMessageBox::Yes | QMessageBox::No);
    if(result == QMessageBox::Yes) {
        // close serial port if open
        if(mSerialPort.isOpen()) {
            statusBar()->showMessage(tr("Closing port %1").arg(mSerialPort.portName()));
            mSerialPort.close();
        }

        event->accept();
    }
    else {
        event->ignore();
    }
}

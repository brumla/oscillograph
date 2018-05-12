#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>

#include "src/dlgportsetup.h"

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
    void on_action_Quit_triggered();
    void on_serial_port_closing();
    void on_serial_port_channel_finished();

private:
    Ui::MainWindow *ui;

    QAction* mStartStop;
    QAction* mExportCSV;
    QAction* mPortSetup;

    SerialPortSetup mSerialPortSetup;
    QSerialPort mSerialPort;

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);       
};

#endif // MAINWINDOW_H

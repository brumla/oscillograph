#include "dlgportsetup.h"
#include "ui_dlgportsetup.h"

#include <QSerialPortInfo>
#include <QSerialPort>

DlgPortSetup::DlgPortSetup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgPortSetup)
{
    ui->setupUi(this);

    initializeDialogData();
}

DlgPortSetup::~DlgPortSetup()
{
    delete ui;
}

void DlgPortSetup::initializeDialogData()
{
    // setup list of ports, the name+description is shown, data contains port name only
    QSerialPortInfo portInfo;

    QList<QSerialPortInfo> ports = portInfo.availablePorts();

    ui->cbPort->clear();
    ui->cbPort->addItem(QString(), QVariant());
    for(QSerialPortInfo port : ports) {
        ui->cbPort->addItem(QString("%1 (%2)").arg(port.portName()).arg(port.description()), port.portName());
    }
}

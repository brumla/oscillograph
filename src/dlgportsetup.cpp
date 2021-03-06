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

    ui->cbSpeed->clear();
    ui->cbSpeed->addItem(QString(), QVariant());
    ui->cbSpeed->addItem(tr("115200 *"), QSerialPort::Baud115200);
    ui->cbSpeed->addItem(tr("1200"), QSerialPort::Baud1200);
    ui->cbSpeed->addItem(tr("2400"), QSerialPort::Baud2400);
    ui->cbSpeed->addItem(tr("4800"), QSerialPort::Baud4800);
    ui->cbSpeed->addItem(tr("9600"), QSerialPort::Baud9600);
    ui->cbSpeed->addItem(tr("19200"), QSerialPort::Baud19200);
    ui->cbSpeed->addItem(tr("38400"), QSerialPort::Baud38400);
    ui->cbSpeed->addItem(tr("57600"), QSerialPort::Baud57600);

    ui->cbParity->clear();
    ui->cbParity->addItem(QString(), QVariant());
    ui->cbParity->addItem(tr("None *"), QSerialPort::NoParity);
    ui->cbParity->addItem(tr("Even"), QSerialPort::EvenParity);
    ui->cbParity->addItem(tr("Odd"), QSerialPort::OddParity);
    ui->cbParity->addItem(tr("Space"), QSerialPort::SpaceParity);
    ui->cbParity->addItem(tr("Mark"), QSerialPort::MarkParity);

    ui->cbDataBit->clear();
    ui->cbDataBit->addItem(QString(), QVariant());
    ui->cbDataBit->addItem(tr("8 *"), QSerialPort::Data8);
    ui->cbDataBit->addItem(tr("5"), QSerialPort::Data5);
    ui->cbDataBit->addItem(tr("6"), QSerialPort::Data6);
    ui->cbDataBit->addItem(tr("7"), QSerialPort::Data7);

    ui->cbStopBit->clear();
    ui->cbStopBit->addItem(QString(), QVariant());
    ui->cbStopBit->addItem(tr("One *"), QSerialPort::OneStop);
    ui->cbStopBit->addItem(tr("One and half"), QSerialPort::OneAndHalfStop);
    ui->cbStopBit->addItem(tr("Two"), QSerialPort::TwoStop);

    ui->cbFlowControl->clear();
    ui->cbFlowControl->addItem(QString(), QVariant());
    ui->cbFlowControl->addItem(tr("None *"), QSerialPort::NoFlowControl);
    ui->cbFlowControl->addItem(tr("Hardware"), QSerialPort::HardwareControl);
    ui->cbFlowControl->addItem(tr("Software"), QSerialPort::SoftwareControl);

    qDebug() << mPortSetup;
}

SerialPortSetup DlgPortSetup::portSetup() const
{
    return mPortSetup;
}

void DlgPortSetup::setPortSetup(const SerialPortSetup &portSetup)
{
    mPortSetup = portSetup;

    // set the combos properly, if the value is not found
    // then the position -1 is used and the combo value is just
    // invalid QVariant
    int index = ui->cbDataBit->findData(mPortSetup.dataBit);
    ui->cbDataBit->setCurrentIndex(index);

    index = ui->cbFlowControl->findData(mPortSetup.flowControl);
    ui->cbFlowControl->setCurrentIndex(index);

    index = ui->cbParity->findData(mPortSetup.parity);
    ui->cbParity->setCurrentIndex(index);

    index = ui->cbPort->findData(mPortSetup.portName);
    ui->cbPort->setCurrentIndex(index);

    index = ui->cbSpeed->findData(mPortSetup.speed);
    ui->cbSpeed->setCurrentIndex(index);

    index = ui->cbStopBit->findData(mPortSetup.stopBit);
    ui->cbStopBit->setCurrentIndex(index);
}

void DlgPortSetup::on_buttonBox_accepted()
{
    // store all the combobox values into port setup structure
    // if some value was not set, the default is stored (zero, empty string)
    mPortSetup.dataBit = ui->cbDataBit->currentData().toInt();
    mPortSetup.flowControl = ui->cbFlowControl->currentData().toInt();
    mPortSetup.parity = ui->cbParity->currentData().toInt();
    mPortSetup.portName = ui->cbPort->currentData().toString();
    mPortSetup.speed = ui->cbSpeed->currentData().toInt();
    mPortSetup.stopBit = ui->cbStopBit->currentData().toInt();
}

QDebug operator <<(QDebug debug, const SerialPortSetup& portSetup) {
    debug << "SerialPortSetup(portName=" << portSetup.portName
          << ", speed=" << portSetup.speed
          << ", parity=" << portSetup.parity
          << ", dataBit=" << portSetup.dataBit
          << ", stopBit=" << portSetup.stopBit
          << ", flowControl=" << portSetup.flowControl
          << ")";
    return debug;
}

void DlgPortSetup::on_btnUseRecomended_clicked()
{
    int index = ui->cbDataBit->findText("*", Qt::MatchContains);
    if(index >= 0) ui->cbDataBit->setCurrentIndex(index);

    index = ui->cbFlowControl->findText("*", Qt::MatchContains);
    if(index >= 0) ui->cbFlowControl->setCurrentIndex(index);

    index = ui->cbParity->findText("*", Qt::MatchContains);
    if(index >= 0) ui->cbParity->setCurrentIndex(index);

    index = ui->cbSpeed->findText("*", Qt::MatchContains);
    if(index >= 0) ui->cbSpeed->setCurrentIndex(index);

    index = ui->cbStopBit->findText("*", Qt::MatchContains);
    if(index >= 0) ui->cbStopBit->setCurrentIndex(index);
}

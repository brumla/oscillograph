#ifndef DLGPORTSETUP_H
#define DLGPORTSETUP_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class DlgPortSetup;
}

///
/// \brief Current serial port setup
///
struct SerialPortSetup {
    QString portName;
    int speed = -1;
    int parity = -1;
    int dataBit = -1;
    int stopBit = -1;
    int flowControl = -1;
};

///
/// \brief Serial port setup dialog.
///
class DlgPortSetup : public QDialog
{
    Q_OBJECT

    Q_PROPERTY(SerialPortSetup mPortSetup READ portSetup WRITE setPortSetup)
public:
    explicit DlgPortSetup(QWidget *parent = 0);
    ~DlgPortSetup();

    SerialPortSetup portSetup() const;
    void setPortSetup(const SerialPortSetup &portSetup);

private slots:
    ///
    /// \brief   collects the serial port setup and store it to portSetup property
    /// \details if the call to exec() returns \code rejected, the property value is
    ///          unchanged
    ///
    void on_buttonBox_accepted();

private:
    Ui::DlgPortSetup *ui;

    void initializeDialogData();
    SerialPortSetup mPortSetup;
};

// -------------------------- helper utils --------------------------

///
/// \brief operator << for debugging messages
/// \param debug debugger
/// \param portSetup port setup structure
/// \return debugger instance
///
QDebug operator <<(QDebug debug, const SerialPortSetup& portSetup);

#endif // DLGPORTSETUP_H

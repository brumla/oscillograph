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

    ///
    /// \brief port setup property getter
    /// \return current port setup, if the dialog was accepted, the new setup is returned
    ///
    SerialPortSetup portSetup() const;

    ///
    /// \brief sets the dialog entries according to port setup, if the port setup is invalid or unitialized,
    ///        empty values are shown in all the entries
    /// \param portSetup
    ///
    void setPortSetup(const SerialPortSetup &portSetup);

private slots:
    ///
    /// \brief   collects the serial port setup and store it to portSetup property
    /// \details if the call to exec() returns \code rejected, the property value is
    ///          unchanged
    ///
    void on_buttonBox_accepted();

    void on_btnUseRecomended_clicked();

private:
    Ui::DlgPortSetup *ui;

    ///
    /// \brief initializes all the comboboxes in the dialog with the values lists
    ///
    void initializeDialogData();

    ///
    /// \brief current port setup, use property getter/setter for value access
    ///
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

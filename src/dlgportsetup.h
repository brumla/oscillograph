#ifndef DLGPORTSETUP_H
#define DLGPORTSETUP_H

#include <QDialog>

namespace Ui {
class DlgPortSetup;
}

class DlgPortSetup : public QDialog
{
    Q_OBJECT

public:
    explicit DlgPortSetup(QWidget *parent = 0);
    ~DlgPortSetup();

private:
    Ui::DlgPortSetup *ui;

    void initializeDialogData();
};

#endif // DLGPORTSETUP_H

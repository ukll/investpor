#ifndef GOLDDIALOG_H
#define GOLDDIALOG_H

#include <QDialog>

namespace Ui {
    class GoldDialog;
}

class GoldDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GoldDialog(QWidget *parent = 0);
    ~GoldDialog();

private:
    Ui::GoldDialog *ui;

    void rearrangeDialog(int index);
};

#endif // GOLDDIALOG_H

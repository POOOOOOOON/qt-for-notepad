#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include <QSysInfo>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QFrame>
#include <QDebug>

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    QString getsystemversion();
    explicit AboutDialog(QWidget *parent = 0);
    ~AboutDialog();

private:
    QLabel *headlable;
    QLabel *iconlable;
    QLabel *contentonelable;
    QLabel *contenttwolable;
    QLabel *contentthreelable;
    QLabel *contentfourlable;
    QLabel *contentfivelable;
    QLabel *contentsixlable;
    QLabel *contentsevenlable;
    QLabel *icon1lable;

    QFrame *splitterline;

    QPushButton *okbutton;

    QString version;
    Ui::AboutDialog *ui;
};

#endif // ABOUTDIALOG_H

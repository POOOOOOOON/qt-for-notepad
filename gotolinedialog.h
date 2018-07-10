#ifndef GOTOLINEDIALOG_H
#define GOTOLINEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QBoxLayout>
#include <QSpacerItem>
#include <QKeyEvent>
#include <QValidator>
#include <QRegExp>
#include <QMessageBox>
#include <QDebug>

namespace Ui {
class GotolineDialog;
}


class GotolineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GotolineDialog(QWidget *parent = 0);
    ~GotolineDialog();

signals:
    void gotosignal(QString);

private slots:
    void change();
    void gotoslot();

private:
    QLabel *linelable;
    QLineEdit *lineedit;
    QPushButton *gotobutton;
    QPushButton *canclebutton;
    Ui::GotolineDialog *ui;
};

#endif // GOTOLINEDIALOG_H

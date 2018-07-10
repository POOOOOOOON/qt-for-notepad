#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QCheckBox>
#include <QGroupBox>
#include <QBoxLayout>
#include <QSpacerItem>

namespace Ui {
class FindDialog;
}

class FindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindDialog(QWidget *parent = 0);
    ~FindDialog();

signals:
    void findsignal(QString,bool,bool);

private slots:
    void find();
    void change();

private:
    QLabel *findlable;
    QLineEdit *findedit;
    QPushButton *findbutton;
    QPushButton *canclebutton;
    QRadioButton *upbutton;
    QRadioButton *downbutton;
    QCheckBox *casesenbox;
    QGroupBox *directionbox;
    QSpacerItem *Vspacer;

    Ui::FindDialog *ui;


};

#endif // FINDDIALOG_H

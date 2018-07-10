#ifndef REPLACEDIALOG_H
#define REPLACEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QBoxLayout>
#include <QSpacerItem>

namespace Ui {
class ReplaceDialog;
}

class ReplaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReplaceDialog(QWidget *parent = 0);
    ~ReplaceDialog();

signals:
    void findsignal(QString,bool,bool);
    void replacesignal(QString,QString,bool);
    void allreplacesignal(QString,QString,bool);

private slots:
    void find();
    void replace();
    void allreplace();
    void change();

private:
    QLabel *findlable;
    QLabel *replacelable;
    QLineEdit *findedit;
    QLineEdit *replaceedit;
    QPushButton *findbutton;
    QPushButton *replacebutton;
    QPushButton *allreplacebutton;
    QPushButton *canclebutton;
    QCheckBox *casesenbox;
    QSpacerItem *Vspace;

    Ui::ReplaceDialog *ui;
};

#endif // REPLACEDIALOG_H

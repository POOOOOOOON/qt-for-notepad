#include "gotolinedialog.h"
#include "ui_gotolinedialog.h"
#include "mainwindow.h"


GotolineDialog::GotolineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GotolineDialog)
{
    ui->setupUi(this);

    linelable = new QLabel(tr("行号(L):"),this);
    lineedit = new QLineEdit();
    gotobutton = new QPushButton(tr("转到"),this);
    canclebutton = new QPushButton(tr("取消"),this);

    QVBoxLayout *mainlayout = new QVBoxLayout;
    QHBoxLayout *buttonlayout = new QHBoxLayout;
    QSpacerItem *Hspacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);


    connect(lineedit,SIGNAL(textChanged(QString)),this,SLOT(change()));
    connect(gotobutton,SIGNAL(clicked(bool)),this,SLOT(gotoslot()));
    connect(canclebutton,SIGNAL(clicked(bool)),this,SLOT(close()));

    buttonlayout->addSpacerItem(Hspacer);
    buttonlayout->addWidget(gotobutton);
    buttonlayout->addWidget(canclebutton);
    mainlayout->addWidget(linelable);
    mainlayout->addWidget(lineedit);
    mainlayout->addLayout(buttonlayout);

    QRegExp regx("[1-9][0-9]+$");
    QValidator *limit = new QRegExpValidator(regx,this->lineedit);
    lineedit->setText("1");
    lineedit->setValidator(limit);

    setLayout(mainlayout);
    setFixedSize(240,90);
    setWindowTitle("转到指定行");
}

void GotolineDialog::change()
{
    //qDebug() << "1111";
}

void GotolineDialog::gotoslot()
{
    MainWindow *notepad = (MainWindow *) parentWidget();
    QString line = lineedit->text();

    if(line.toInt() > notepad->getlinenumbers() || line.isEmpty())
    {
        QMessageBox box(QMessageBox::Question,"记事本 - 跳行","行数超过了总行数     ");
        box.setIcon(QMessageBox::NoIcon);
        box.setStandardButtons(QMessageBox::Ok);
        box.setButtonText(QMessageBox::Ok,QString("确定"));
        box.setWindowFlags(Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
        box.exec();
        return;
    }
    else
        emit gotosignal(line);

}

GotolineDialog::~GotolineDialog()
{
    delete ui;
}

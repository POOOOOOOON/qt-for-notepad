#include "finddialog.h"
#include "ui_finddialog.h"
#include <QDebug>

FindDialog::FindDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindDialog)
{
    ui->setupUi(this);

    //UI
    findlable = new QLabel(tr("查找内容(N): "),this);
    findedit = new QLineEdit(this);
    findbutton = new QPushButton(tr("查找下一个(&F)"),this);
    canclebutton = new QPushButton(tr("取消"),this);
    casesenbox = new QCheckBox(tr("区分大小写(&C)"),this);
    upbutton = new QRadioButton(tr("向上(&U)"),this);
    downbutton = new QRadioButton(tr("向下(&D)"),this);
    directionbox = new QGroupBox(tr("方向"),this);
    Vspacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

    QHBoxLayout *mainlayout = new QHBoxLayout;
    QVBoxLayout *leftlayout = new QVBoxLayout;
    QVBoxLayout *rightlayout = new QVBoxLayout;
    QHBoxLayout *findlayout = new QHBoxLayout;
    QHBoxLayout *chooselayout = new QHBoxLayout;
    QHBoxLayout *radiolayout = new QHBoxLayout;

    findlayout->addWidget(findlable);
    findlayout->addWidget(findedit);
    radiolayout->addWidget(upbutton);
    radiolayout->addWidget(downbutton);
    directionbox->setLayout(radiolayout);
    chooselayout->addWidget(casesenbox,0,Qt::AlignBottom);
    chooselayout->addWidget(directionbox);
    leftlayout->addLayout(findlayout);
    leftlayout->addLayout(chooselayout);
    rightlayout->addWidget(findbutton);
    rightlayout->addWidget(canclebutton);
    rightlayout->addSpacerItem(Vspacer);
    mainlayout->addLayout(leftlayout);
    mainlayout->addLayout(rightlayout);

    //signal
    connect(findbutton,SIGNAL(clicked(bool)),this,SLOT(find()));
    connect(canclebutton,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(findedit,SIGNAL(textChanged(QString)),this,SLOT(change()));

    //init
    findbutton->setEnabled(false);
    downbutton->setChecked(true);
    setLayout(mainlayout);
    setFixedSize(375,100);
    setWindowTitle(tr("查找"));
}

void FindDialog::find()
{
    if(upbutton->isChecked())
        if(casesenbox->isChecked())
            emit findsignal(findedit->text(),true,true);
        else
           emit findsignal(findedit->text(),true,false);
    else
        if(casesenbox->isChecked())
           emit findsignal(findedit->text(),false,true);
        else
            emit findsignal(findedit->text(),false,false);


}

void FindDialog::change()
{
    if(findedit->text().isEmpty())
        findbutton->setEnabled(false);
    else
        findbutton->setEnabled(true);
}

FindDialog::~FindDialog()
{
    delete ui;
}

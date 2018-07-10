#include "replacedialog.h"
#include "ui_replacedialog.h"

ReplaceDialog::ReplaceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReplaceDialog)
{
    ui->setupUi(this);

    //UI
    findlable = new QLabel(tr("查找内容(N): "),this);
    replacelable = new QLabel(tr("替换为(P):   "),this);
    findedit = new QLineEdit(this);
    replaceedit = new QLineEdit(this);
    findbutton = new QPushButton(tr("查找下一个(&F)"),this);
    replacebutton = new QPushButton(tr("替换(&R)"),this);
    allreplacebutton = new QPushButton(tr("全部替换(&A)"),this);
    canclebutton = new QPushButton(tr("取消"),this);
    casesenbox = new QCheckBox(tr("区分大小写(&C)"),this);
    Vspace = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

    QHBoxLayout *mainlayout = new QHBoxLayout;
    QVBoxLayout *leftlayout = new QVBoxLayout;
    QVBoxLayout *rightlayout = new QVBoxLayout;
    QHBoxLayout *findlayout = new QHBoxLayout;
    QHBoxLayout *replacelayout = new QHBoxLayout;
    QHBoxLayout *chooselayout = new QHBoxLayout;

    findlayout->addWidget(findlable);
    findlayout->addWidget(findedit);
    replacelayout->addWidget(replacelable);
    replacelayout->addWidget(replaceedit);
    chooselayout->addWidget(casesenbox,0,Qt::AlignVCenter);
    leftlayout->addLayout(findlayout);
    leftlayout->addLayout(replacelayout);
    leftlayout->addLayout(chooselayout);

    rightlayout->addWidget(findbutton);
    rightlayout->addWidget(replacebutton);
    rightlayout->addWidget(allreplacebutton);
    rightlayout->addWidget(canclebutton);
    rightlayout->addSpacerItem(Vspace);

    mainlayout->addLayout(leftlayout);
    mainlayout->addLayout(rightlayout);

    //signal
    connect(findedit,SIGNAL(textChanged(QString)),this,SLOT(change()));
    connect(canclebutton,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(findbutton,SIGNAL(clicked(bool)),this,SLOT(find()));
    connect(replacebutton,SIGNAL(clicked(bool)),this,SLOT(replace()));
    connect(allreplacebutton,SIGNAL(clicked(bool)),this,SLOT(allreplace()));

    //init
    findbutton->setEnabled(false);
    replacebutton->setEnabled(false);
    allreplacebutton->setEnabled(false);
    setLayout(mainlayout);
    setFixedSize(375,150);
    setWindowTitle(tr("替换"));
}

void ReplaceDialog::change()
{
    if(findedit->text().isEmpty())
    {
        findbutton->setEnabled(false);
        replacebutton->setEnabled(false);
        allreplacebutton->setEnabled(false);
    }
    else
    {
        findbutton->setEnabled(true);
        replacebutton->setEnabled(true);
        allreplacebutton->setEnabled(true);
    }
}

void ReplaceDialog::find()
{
    if(casesenbox->isChecked())
        emit findsignal(findedit->text(),false,true);
    else
        emit findsignal(findedit->text(),false,false);
}

void ReplaceDialog::replace()
{
    if(casesenbox->isChecked())
        emit replacesignal(findedit->text(),replaceedit->text(),true);
    else
        emit replacesignal(findedit->text(),replaceedit->text(),false);
}

void ReplaceDialog::allreplace()
{
    if(casesenbox->isChecked())
        emit allreplacesignal(findedit->text(),replaceedit->text(),true);
    else
        emit allreplacesignal(findedit->text(),replaceedit->text(),false);
}

ReplaceDialog::~ReplaceDialog()
{
    delete ui;
}

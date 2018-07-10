#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    version = getsystemversion();
    headlable = new QLabel(version,this);
    headlable->setFont(QFont("楷体",40));
    headlable->move(this->width()/3,this->height()/15);

    iconlable = new QLabel(this);
    iconlable->setFixedSize(80,80);
    QPixmap pixmap(":/new/prefix1/images/about.png");
    pixmap = pixmap.scaled(iconlable->size(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    iconlable->setScaledContents(true);
    iconlable->setPixmap(pixmap);
    iconlable->move(this->width()/10,this->height()/30);

    splitterline = new QFrame(this);
    splitterline->setFixedSize(420,2);
    splitterline->setFrameShape(QFrame::HLine);
    splitterline->move(this->width()/40,this->height()*7/24);
    splitterline->setStyleSheet("color:gray");

    contentonelable = new QLabel(this);
    contentonelable->setText("版本 1.1");
    contentonelable->setFont(QFont("宋体",10));
    contentonelable->move(this->width()/7,this->height()*18/48);

    contenttwolable = new QLabel(this);
    contenttwolable->setText("版本所有权 潘振鲁/隋慧。保留所有权利");
    contenttwolable->setFont(QFont("宋体",10));
    contenttwolable->move(this->width()/7,this->height()*20/48);

    contentthreelable = new QLabel(this);
    contentthreelable->setText("用户界面受中国和其他国家/地区的商标法和其他待颁布");
    contentthreelable->setFont(QFont("宋体",10));
    contentthreelable->move(this->width()/7,this->height()*22/48);

    contentfourlable = new QLabel(this);
    contentfourlable->setText("或已颁布的知识产权法保护");
    contentfourlable->setFont(QFont("宋体",10));
    contentfourlable->move(this->width()/7,this->height()*24/48);

    contentfivelable = new QLabel(this);
    contentfivelable->setText("本产品使用权属于:");
    contentfivelable->setFont(QFont("宋体",10));
    contentfivelable->move(this->width()/7,this->height()*3/4);

    contentsixlable = new QLabel(this);
    contentsixlable->setText("微软用户");
    contentsixlable->setFont(QFont("宋体",10));
    contentsixlable->move(this->width()/6,this->height()*10/12);

    contentsevenlable = new QLabel(this);
    contentsevenlable->setText("微软中国");
    contentsevenlable->setFont(QFont("宋体",10));
    contentsevenlable->move(this->width()/6,this->height()*21/24);

    icon1lable = new QLabel(this);
    icon1lable->setFixedSize(40,40);
    QPixmap pixmap1(":/new/prefix1/images/app.ico");
    pixmap1 = pixmap1.scaled(icon1lable->size(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    icon1lable->setScaledContents(true);
    icon1lable->setPixmap(pixmap1);
    icon1lable->move(this->width()/30,this->height()/3);


    okbutton = new QPushButton(tr("确定"),this);
    okbutton->setFixedSize(80,25);
    okbutton->move(this->width()*8/9,this->height()*9999/10000);
    connect(okbutton,SIGNAL(clicked(bool)),this,SLOT(close()));

    setWindowTitle("关于\"记事本\"");
    setFixedSize(440,350);
}

QString AboutDialog::getsystemversion()
{
    QString osname;

    switch(QSysInfo::windowsVersion())
    {
        case QSysInfo::WV_32s:
            osname = "Windows 3.1 with Win 32s";
        break;
        case QSysInfo::WV_95:
            osname = "Windows 95";
        break;
        case QSysInfo::WV_98:
            osname = "Windows 98";
        break;
        case QSysInfo::WV_Me:
            osname = "Windows Me";
        break;
        case QSysInfo::WV_NT:
            osname = "Windows NT";
        break;
        case QSysInfo::WV_2000:
            osname = "Windows 2000";
        break;
        case QSysInfo::WV_XP:
            osname = "Windows XP";
        break;
        case QSysInfo::WV_2003:
            osname = "Windows Server 2003";
        break;
        case QSysInfo::WV_VISTA:
            osname = "Windows Vista";
        break;
        case QSysInfo::WV_WINDOWS7:
            osname = "Windows 7";
        break;
        case QSysInfo::WV_WINDOWS8:
            osname = "Windows 8";
        break;
        case QSysInfo::WV_WINDOWS8_1:
            osname = "Windows 8.1";
        break;
        case QSysInfo::WV_WINDOWS10:
            osname = "Windows 10";
        break;
        default:
            osname = "Windows unknow";
        break;
    }

    return osname;
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

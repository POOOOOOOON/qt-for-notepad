#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QClipboard>
#include <QMimeData>
#include <QDateTime>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle(tr("无标题 - 记事本"));
    this->resize(725,515);
    this->setWindowIcon(QIcon(":/new/prefix1/images/app.ico"));

    finddialog = new FindDialog(this);
    replacedialog = new ReplaceDialog(this);
    gotodialog = new GotolineDialog(this);
    aboutdialog = new AboutDialog(this);

    newAt = new QAction(tr("新建(&N)"),this);
    openAt = new QAction(tr("打开(&O)..."),this);
    saAt = new QAction(tr("保存(&S)"),this);
    sasAt = new QAction(tr("另存为(&A)..."),this);
    pageAt = new QAction(tr("页面设置(&U)..."),this);
    printAt = new QAction(tr("打印(&P)..."),this);
    quitAt = new QAction(tr("退出(&X)"),this);

    file = this->menuBar()->addMenu(tr("文件(&F)"));
    file->addAction(newAt);
    file->addAction(openAt);
    file->addAction(saAt);
    file->addAction(sasAt);
    file->addSeparator();
    file->addAction(pageAt);
    file->addAction(printAt);
    file->addSeparator();
    file->addAction(quitAt);

    undoAt = new QAction(tr("撤销(&U)"),this);
    cutAt = new QAction(tr("剪切(&T)"),this);
    copyAt = new QAction(tr("复制(&C)"),this);
    pasteAt = new QAction(tr("粘贴(&P)"),this);
    delAt = new QAction(tr("删除(&L)"),this);
    findAt = new QAction(tr("查找(&F)"),this);
    findnextAt = new QAction(tr("查找下一个(&N)"),this);
    replaceAt = new QAction(tr("替换(&R)..."),this);
    gotoAt = new QAction(tr("转到(&G)..."),this);
    seallAt = new QAction(tr("全选(&A)"),this);
    timeAt = new QAction(tr("时间/日期(&D)"),this);

    edit = this->menuBar()->addMenu(tr("编辑(&E)"));
    edit->addAction(undoAt);
    edit->addSeparator();
    edit->addAction(cutAt);
    edit->addAction(copyAt);
    edit->addAction(pasteAt);
    edit->addAction(delAt);
    edit->addSeparator();
    edit->addAction(findAt);
    edit->addAction(findnextAt);
    edit->addAction(replaceAt);
    edit->addAction(gotoAt);
    edit->addSeparator();
    edit->addAction(seallAt);
    edit->addAction(timeAt);

    autonumAt = new QAction(tr("自动换号(&W)"),this);
    fontAt = new QAction(tr("字体(&F)..."),this);

    format = this->menuBar()->addMenu(tr("格式(&O)"));
    format->addAction(autonumAt);
    format->addAction(fontAt);

    statAt = new QAction(tr("状态栏(&S)"),this);

    check = this->menuBar()->addMenu(tr("查看(&V)"));
    check->addAction(statAt);

    helpAt = new QAction(tr("查看帮助(&H)"),this);
    aboutAt = new QAction(tr("关于记事本(&A)"),this);

    help = this->menuBar()->addMenu(tr("帮助(&H)"));
    help->addAction(helpAt);
    help->addSeparator();
    help->addAction(aboutAt);

    editor = new QTextEdit();
    this->setCentralWidget(editor);
    editor->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    editor->setFont(QFont("楷体",15));

    connect(editor,SIGNAL(textChanged()),this,SLOT(change()));
    connect(editor, SIGNAL(copyAvailable(bool)),cutAt, SLOT(setEnabled(bool)));
    connect(editor, SIGNAL(copyAvailable(bool)), copyAt, SLOT(setEnabled(bool)));
    connect(editor, SIGNAL(copyAvailable(bool)), delAt, SLOT(setEnabled(bool)));
    connect(undoAt,SIGNAL(triggered(bool)),editor,SLOT(undo()));
    connect(cutAt,SIGNAL(triggered(bool)),editor,SLOT(cut()));
    connect(copyAt,SIGNAL(triggered(bool)),editor,SLOT(copy()));
    connect(pasteAt,SIGNAL(triggered(bool)),editor,SLOT(paste()));
    connect(seallAt,SIGNAL(triggered(bool)),editor,SLOT(selectAll()));
    connect(delAt,SIGNAL(triggered(bool)),this,SLOT(del()));
    connect(findAt,SIGNAL(triggered(bool)),this,SLOT(showfinddialog()));
    connect(findnextAt,SIGNAL(triggered(bool)),this,SLOT(findnextresult()));
    connect(replaceAt,SIGNAL(triggered(bool)),this,SLOT(showreplacedialog()));
    connect(gotoAt,SIGNAL(triggered(bool)),this,SLOT(showgotodialog()));
    connect(timeAt,SIGNAL(triggered(bool)),this,SLOT(time()));
    connect(newAt,SIGNAL(triggered(bool)),this,SLOT(newfile()));
    connect(openAt,SIGNAL(triggered(bool)),this,SLOT(openfile()));
    connect(saAt,SIGNAL(triggered(bool)),this,SLOT(savefile()));
    connect(sasAt,SIGNAL(triggered(bool)),this,SLOT(savefileto()));
    connect(printAt,SIGNAL(triggered(bool)),this,SLOT(doprint()));
    connect(quitAt,SIGNAL(triggered(bool)),this,SLOT(quitAPP()));
    connect(fontAt,SIGNAL(triggered(bool)),this,SLOT(font()));
    connect(autonumAt,SIGNAL(triggered(bool)),this,SLOT(autolineslot()));
    connect(statAt,SIGNAL(triggered(bool)),this,SLOT(statuslot()));
    connect(editor,SIGNAL(cursorPositionChanged()),this,SLOT(cursorchangeslot()));
    connect(helpAt,SIGNAL(triggered(bool)),this,SLOT(helpslot()));
    connect(aboutAt,SIGNAL(triggered(bool)),this,SLOT(showaboutdialog()));

    connect(finddialog,SIGNAL(findsignal(QString,bool,bool)),this,SLOT(findresult(QString, bool, bool)));
    connect(replacedialog,SIGNAL(findsignal(QString,bool,bool)),this,SLOT(findresult(QString, bool, bool)));
    connect(replacedialog,SIGNAL(replacesignal(QString,QString,bool)),this,SLOT(replaceresult(QString, QString, bool)));
    connect(replacedialog,SIGNAL(allreplacesignal(QString,QString,bool)),this,SLOT(allreplaceresult(QString, QString, bool)));
    connect(gotodialog,SIGNAL(gotosignal(QString)),this,SLOT(gotolineresult(QString)));

    //init
    changed = 0;
    config();
    setshortcuts();
    undoAt->setEnabled(false);
    cutAt->setEnabled(false);
    copyAt->setEnabled(false);
    delAt->setEnabled(false);
    if (const QMimeData *md = QApplication::clipboard()->mimeData())
        pasteAt->setEnabled(md->hasText());
    if(editor->toPlainText().isEmpty())
    {
        seallAt->setEnabled(false);
        findAt->setEnabled(false);
        findnextAt->setEnabled(false);
        replaceAt->setEnabled(false);
    }

}

void MainWindow::config()
{
    setting = new QSettings("config.ini",QSettings::IniFormat);
    autoline = true;
    statusbar = false;

    editor->setAcceptDrops(false); //设置文本输入框不接受鼠标放下
    this->setAcceptDrops(true);  //设置窗口接受鼠标放下

    autonumAt->setIcon(QIcon(QPixmap(":/new/prefix1/images/auto_line.png")));
    statAt->setIcon(QIcon(QPixmap(":/new/prefix1/images/status.png")));

    setting->beginGroup("config.ini");
    QString family = setting->value("family").toString();
    if(!family.isEmpty())
    {
        QFont font;
        font.setFamily(family);
        font.setPointSize(setting->value("point_size").toInt());
        font.setItalic(setting->value("italic").toBool());
        font.setBold(setting->value("bold").toBool());
        font.setOverline(setting->value("overline").toBool());
        font.setUnderline(setting->value("underline").toBool());
        editor->setFont(font);
    }

    autoline = setting->value("auto_go_line").toInt() == 1?true:false;
    statusbar = setting->value("status_bar").toInt() == 1?true:false;
    setting->endGroup();

    if(!autoline)
    {
        statAt->setEnabled(true);
        gotoAt->setEnabled(true);

        //设置是否显示状态栏
        ui->statusBar->setVisible(statusbar);

        editor->setLineWrapMode(QTextEdit::NoWrap);

        //是否显示状态栏选中图标
        statAt->setIconVisibleInMenu(statusbar);

        //是否显示自动换行选中图标
        autonumAt->setIconVisibleInMenu(false);

    }
    else
    {
        statAt->setEnabled(false);
        gotoAt->setEnabled(false);

        //设置是否显示状态栏
        ui->statusBar->setVisible(false);
        //设置自动换行属性
        editor->setLineWrapMode(QTextEdit::WidgetWidth);
        //是否显示状态栏选中图标
        statAt->setIconVisibleInMenu(false);
        //是否显示自动换行选中图标
        autonumAt->setIconVisibleInMenu(true);
    }

    ui->statusBar->setStyleSheet(QString("QStatusBar::item{border: 0px}"));
    ui->statusBar->setSizeGripEnabled(false);
    statulable = new QLabel("第 1 行，第 1 列   字数 0   ", this);
    ui->statusBar->addPermanentWidget(statulable);
}

void MainWindow::setshortcuts()
{
    newAt->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    openAt->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    saAt->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    sasAt->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));
    printAt->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_P));

    undoAt->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));
    cutAt->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_X));
    copyAt->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    pasteAt->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_V));
    findAt->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F));
    findnextAt->setShortcut(QKeySequence(Qt::Key_F3));
    replaceAt->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_H));
    delAt->setShortcut(QKeySequence(Qt::Key_Delete));
    gotoAt->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_G));
    seallAt->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));
    timeAt->setShortcut(QKeySequence(Qt::Key_F5));
}

void MainWindow::change()
{
    if(editor->toPlainText().isEmpty())
    {
        findAt->setEnabled(false);
        seallAt->setEnabled(false);
        findAt->setEnabled(false);
        findnextAt->setEnabled(false);
        replaceAt->setEnabled(false);
    }
    else
    {
        findAt->setEnabled(true);
        undoAt->setEnabled(true);
        seallAt->setEnabled(true);
        findAt->setEnabled(true);
        replaceAt->setEnabled(true);
        findnextAt->setEnabled(true);
    }

    changed = 1;
}

void MainWindow::savefiletolocal()
{
    QFile file(filename);
    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file);
        out << editor->document()->toPlainText();
        file.close();

        if(filename.lastIndexOf("//") != -1)
            setWindowTitle(filename.mid(filename.lastIndexOf("//")+1)+" - 记事本");
        else
            setWindowTitle(filename.mid(filename.lastIndexOf("/")+1)+" - 记事本");
    }
}

void MainWindow::readfilefromlocal()
{
    if(!filename.isEmpty())
    {
        QFile file(filename);
        if(file.open(QIODevice::ReadOnly))
        {
            editor->clear();
            QTextStream in(&file);
            while(!in.atEnd())
            {
                editor->append(in.readLine());
            }
            editor->moveCursor(QTextCursor::Start);

            if(filename.lastIndexOf("//") != -1)
                setWindowTitle(filename.mid(filename.lastIndexOf("//")+1)+" - 记事本");
            else
                setWindowTitle(filename.mid(filename.lastIndexOf("/")+1)+" - 记事本");

            file.close();
        }
    }
}

int MainWindow::getlinenumbers()
{
    QString text = editor->toPlainText();
    QStringList list = text.split("\n");

    return list.size() ;
}

void MainWindow::newfile()
{
    if(editor->document()->isModified() && !editor->document()->isEmpty())
    {
        QMessageBox box(QMessageBox::Question,"记事本","是否将更改保存到 无标题?");
        box.setIcon(QMessageBox::NoIcon);
        box.setStandardButtons(QMessageBox::Ok|QMessageBox::Ignore|QMessageBox::Cancel);
        box.setButtonText(QMessageBox::Ok,QString("保存"));
        box.setButtonText(QMessageBox::Ignore,QString("不保存"));
        box.setButtonText(QMessageBox::Cancel,QString("取消"));

        int ret = box.exec();
        if(ret == QMessageBox::Ok)
        {
            if(filename.isEmpty())
            {
                filename = QFileDialog::getSaveFileName(this,tr("另存为"),QDir::homePath(),tr("文本文件 (*.txt);;"));
                if(!filename.isEmpty())
                    this->savefiletolocal();
            }
            else
                this->savefiletolocal();

        }
        else if(ret == QMessageBox::Ignore)
        {
            editor->clear();
            setWindowTitle("无标题 - 记事本");
        }

    }
    else
    {
        editor->clear();
        setWindowTitle("无标题 - 记事本");
    }
}

void MainWindow::openfile()
{
    if(editor->document()->isModified() && !editor->document()->isEmpty())
    {
        QMessageBox box(QMessageBox::Question,"记事本","是否将更改保存到 无标题?");
        box.setIcon(QMessageBox::NoIcon);
        box.setStandardButtons(QMessageBox::Ok|QMessageBox::Ignore|QMessageBox::Cancel);
        box.setButtonText(QMessageBox::Ok,QString("保存"));
        box.setButtonText(QMessageBox::Ignore,QString("不保存"));
        box.setButtonText(QMessageBox::Cancel,QString("取消"));

        int ret = box.exec();

        if(ret == QMessageBox::Ok)
            this->savefiletolocal();
        else if(ret == QMessageBox::Cancel)
            return;
    }

    filename = QFileDialog::getOpenFileName(this,tr("打开"),QDir::homePath(),tr("文本文件 (*.txt);;"));
    this->readfilefromlocal();

}

void MainWindow::savefile()
{
    if(filename.isEmpty())
    {
        filename = QFileDialog::getSaveFileName(this,tr("另存为"),QDir::homePath(),tr("文本文件 (*.txt);;"));
        if(!filename.isEmpty())
            this->savefiletolocal();
    }
    else
        this->savefiletolocal();
}

void MainWindow::savefileto()
{
    filename = QFileDialog::getSaveFileName(this,tr("另存为"),QDir::homePath(),tr("文本文件 (*.txt);;"));
    if(!filename.isEmpty())
        this->savefiletolocal();
}

void MainWindow::doprint()
{
    QPrinter printer;
    QPrintDialog dialog(&printer,this);

    if(editor->textCursor().hasSelection())
        dialog.addEnabledOption(QAbstractPrintDialog::PrintSelection);

    if(dialog.exec() == QDialog::Accepted)
        editor->print(&printer);
}

void MainWindow::quitAPP()
{
    if(editor->document()->isModified() && !editor->document()->isEmpty())
    {
        if(filename.isEmpty())
        {
            QMessageBox box(QMessageBox::Question,"记事本","是否将更改保存到 无标题?");
            box.setIcon(QMessageBox::NoIcon);
            box.setStandardButtons(QMessageBox::Ok|QMessageBox::Ignore|QMessageBox::Cancel);
            box.setButtonText(QMessageBox::Ok,QString("保存"));
            box.setButtonText(QMessageBox::Ignore,QString("不保存"));
            box.setButtonText(QMessageBox::Cancel,QString("取消"));

            int ret = box.exec();
            if(ret == QMessageBox::Ok)
            {
                filename = QFileDialog::getSaveFileName(this,tr("另存为"),QDir::homePath(),tr("文本文件 (*.txt);;"));
                if(!filename.isEmpty())
                    this->savefiletolocal();
            }
            else if(ret == QMessageBox::Cancel)
                return;

        }
        else
        {
            QString message;
            message = "是否将更改保存到\n" + filename + "?";
            QMessageBox box(QMessageBox::Question,"记事本",message);
            box.setIcon(QMessageBox::NoIcon);
            box.setStandardButtons(QMessageBox::Ok|QMessageBox::Ignore|QMessageBox::Cancel);
            box.setButtonText(QMessageBox::Ok,QString("保存"));
            box.setButtonText(QMessageBox::Ignore,QString("不保存"));
            box.setButtonText(QMessageBox::Cancel,QString("取消"));

            int ret = box.exec();
            if(ret == QMessageBox::Ok)
                this->savefiletolocal();
            else if(ret == QMessageBox::Cancel)
                return;

        }

    }

    this->close();
}

void MainWindow::del()
{
    if(editor->textCursor().hasSelection())
    {
        editor->textCursor().removeSelectedText();
    }
}

void MainWindow::showfinddialog()
{
    if(replacedialog->isHidden())
    {
        finddialog->show();
    }
}

void MainWindow::showreplacedialog()
{
    if(finddialog->isHidden())
    {
        replacedialog->show();
    }

}

void MainWindow::showgotodialog()
{
    gotodialog->exec();
}

void MainWindow::showaboutdialog()
{
    aboutdialog->exec();
}

void MainWindow::time()
{
    QDateTime curtime = QDateTime::currentDateTime();
    QString tmptime = curtime.toString("hh:mm yyyy/MM/dd");
    editor->textCursor().insertText(tmptime);
}

void MainWindow::findresult(QString text, bool upORdown, bool cs)
{
    bool hasfind;
    QString warninfo;

    findcontent = text;
    findcondition = cs;
    switch (upORdown)
    {
        case true:
            switch (cs)
            {
                case true:
                    hasfind = editor->find(text,QTextDocument::FindCaseSensitively | QTextDocument::FindBackward);
                    break;
                case false:
                    hasfind = editor->find(text,QTextDocument::FindBackward);
                    break;
            }
            break;
        case false:
            switch (cs)
            {
                case true:
                    hasfind = editor->find(text,QTextDocument::FindCaseSensitively);
                    break;
                case false:
                    hasfind = editor->find(text);
                    break;
            }
            break;
        default:
            break;
    }

    if(!hasfind)
    {
        warninfo = "找不到 \""  + findcontent + "\"" ;
        QMessageBox::information(this, "记事本", warninfo, QMessageBox::Yes);
    }
    else
    {
        //设置高亮
        QPalette palette = editor->palette();
        palette.setColor(QPalette::Highlight,palette.color(QPalette::Active,QPalette::Highlight));
        editor->setPalette(palette);
    }

}

void MainWindow::findnextresult()
{
    bool hasfind;
    QString warninfo;

    if(findcontent.isEmpty() && replacedialog->isHidden())
    {
        finddialog->show();
    }
    else
    {
        if(findcondition)
            hasfind = editor->find(findcontent,QTextDocument::FindCaseSensitively );
        else
            hasfind = editor->find(findcontent);

        if(!hasfind)
        {
            warninfo = "找不到 \""  + findcontent + "\"" ;
            QMessageBox::information(this, "记事本", warninfo, QMessageBox::Yes);
        }
        else
        {
            //设置高亮
            QPalette palette = editor->palette();
            palette.setColor(QPalette::Highlight,palette.color(QPalette::Active,QPalette::Highlight));
            editor->setPalette(palette);
        }
    }
}

void MainWindow::replaceresult(QString pretext, QString nowtext,bool cs)
{
    bool hasfind;
    QString warninfo;

    findcontent = pretext;
    if(cs)
        hasfind = editor->find(pretext,QTextDocument::FindCaseSensitively );
    else
        hasfind = editor->find(pretext);

    if(!hasfind)
    {
        warninfo = "找不到 \""  + findcontent + "\"" ;
        QMessageBox::information(this, "记事本", warninfo, QMessageBox::Yes);
    }
    else
    {

        QTextCursor textcur = editor->textCursor();
        textcur.insertText(nowtext);
    }
}

void MainWindow::autolineslot()
{
    if(autoline)
    {
        autoline = false;
        statAt->setEnabled(true);
        gotoAt->setEnabled(true);

        //设置是否显示状态栏
        ui->statusBar->setVisible(statusbar);

        editor->setLineWrapMode(QTextEdit::NoWrap);

        //是否显示状态栏选中图标
        statAt->setIconVisibleInMenu(statusbar);

        //是否显示自动换行选中图标
        autonumAt->setIconVisibleInMenu(false);

    }
    else
    {
        autoline = true;
        statAt->setEnabled(false);
        gotoAt->setEnabled(false);

        //设置是否显示状态栏
        ui->statusBar->setVisible(false);
        //设置自动换行属性
        editor->setLineWrapMode(QTextEdit::WidgetWidth);
        //是否显示状态栏选中图标
        statAt->setIconVisibleInMenu(false);
        //是否显示自动换行选中图标
        autonumAt->setIconVisibleInMenu(true);
    }

    setting->beginGroup("config");//beginGroup与下面endGroup 相对应，“config”是标记
    setting->setValue("auto_go_line",QVariant(autoline?"1":"0"));
    setting->endGroup();
}

void MainWindow::statuslot()
{
    if(statusbar)
        statusbar = false;
    else
        statusbar = true;

    //设置是否显示状态栏
    ui->statusBar->setVisible(statusbar);
    //是否显示状态栏选中图标
    statAt->setIconVisibleInMenu(statusbar);

    setting->beginGroup("config");//beginGroup与下面endGroup 相对应，“config”是标记
    setting->setValue("status_bar",QVariant(statusbar?"1":"0"));
    setting->endGroup();
}

void MainWindow::cursorchangeslot()
{
    QTextCursor cur = editor->textCursor();
    int colnum = cur.columnNumber();
    int block = cur.blockNumber();
    int count = editor->document()->toPlainText().length();
    statulable->setText("第 "+QString::number(block+1)+" 行，第 "+QString::number(colnum+1)+" 列   字数 "+QString::number(count)+"   ");
}

void MainWindow::font()
{
    QFont textfont = editor->font();
    bool ok;
    QFont font = QFontDialog::getFont(&ok,textfont,this,tr("字体选择"));
    if(ok)
    {
        editor->setFont(font);
        setting->beginGroup("config");//beginGroup与下面endGroup 相对应，“config”是标记
        setting->setValue("family",QVariant(font.family()));
        setting->setValue("point_size",QVariant(font.pointSize()));
        setting->setValue("italic",QVariant(font.italic() == true ?"1":"0"));
        setting->setValue("bold",QVariant(font.bold()== true ?"1":"0"));
        setting->setValue("overline",QVariant(font.overline()== true ?"1":"0"));
        setting->setValue("underline",QVariant(font.underline()== true ?"1":"0"));
        setting->endGroup();
    }
}

void MainWindow::gotolineresult(QString line)
{
    gotodialog->close();
    QTextCursor cur = editor->textCursor();
    int position = editor->document()->findBlockByLineNumber(line.toInt()-1).position();
    cur.setPosition(position,QTextCursor::MoveAnchor);
    editor->setTextCursor(cur);
}

void MainWindow::allreplaceresult(QString pretext, QString nowtext,bool cs)
{
    bool hasfind = true;

    findcontent = pretext;
    while(hasfind)
    {
        if(cs)
        {
            hasfind = editor->find(pretext,QTextDocument::FindCaseSensitively);
        }
        else
        {
            hasfind = editor->find(pretext);
        }

        if(!hasfind)
        {
            break;
        }
        else
        {

            QTextCursor textcur = editor->textCursor();
            textcur.insertText(nowtext);
        }
    }
}

void MainWindow::helpslot()
{
    QDesktopServices::openUrl(QUrl("https://go.microsoft.com/fwlink/?LinkId=834783"));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(editor->document()->isModified() && !editor->document()->isEmpty())
    {
        if(filename.isEmpty())
        {
            QMessageBox box(QMessageBox::Question,"记事本","是否将更改保存到 无标题?");
            box.setIcon(QMessageBox::NoIcon);
            box.setStandardButtons(QMessageBox::Ok|QMessageBox::Ignore|QMessageBox::Cancel);
            box.setButtonText(QMessageBox::Ok,QString("保存"));
            box.setButtonText(QMessageBox::Ignore,QString("不保存"));
            box.setButtonText(QMessageBox::Cancel,QString("取消"));

            int ret = box.exec();
            if(ret == QMessageBox::Ok)
            {
                filename = QFileDialog::getSaveFileName(this,tr("另存为"),QDir::homePath(),tr("文本文件 (*.txt);;"));
                if(!filename.isEmpty())
                    this->savefiletolocal();
            }
            else if(ret == QMessageBox::Cancel)
            {
                event->ignore();
                return;
            }

        }
        else
        {
            QString message;
            message = "是否将更改保存到\n" + filename + "?";
            QMessageBox box(QMessageBox::Question,"记事本",message);
            box.setIcon(QMessageBox::NoIcon);
            box.setStandardButtons(QMessageBox::Ok|QMessageBox::Ignore|QMessageBox::Cancel);
            box.setButtonText(QMessageBox::Ok,QString("保存"));
            box.setButtonText(QMessageBox::Ignore,QString("不保存"));
            box.setButtonText(QMessageBox::Cancel,QString("取消"));

            int ret = box.exec();
            if(ret == QMessageBox::Ok)
            {
                this->savefiletolocal();
            }
            else if(ret == QMessageBox::Cancel)
            {
                event->ignore();
                return;
            }

        }
    }

    event->accept();

}

MainWindow::~MainWindow()
{
    delete ui;
}


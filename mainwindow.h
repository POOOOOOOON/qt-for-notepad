#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QAction>
#include <QMenu>
#include <QTextEdit>
#include <QMessageBox>
#include <QTextDocumentWriter>
#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QTextCursor>
#include <QTextBlock>
#include <QFontDialog>
#include <QSettings>
#include <QDesktopServices>

#include "finddialog.h"
#include "replacedialog.h"
#include "gotolinedialog.h"
#include "aboutdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void savefiletolocal();
    void readfilefromlocal();
    int getlinenumbers();

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:


private:
    QMenu *file;
    QMenu *edit;
    QMenu *format;
    QMenu *check;
    QMenu *help;

    QTextEdit *editor;
    QSettings *setting;
    QString filename;
    QString findcontent;

    bool findcondition;
    bool autoline;
    bool statusbar;

    QLabel *statulable;

    QClipboard *broad;

    int changed;

    QAction *newAt;
    QAction *openAt;
    QAction *saAt;
    QAction *sasAt;
    QAction *pageAt;
    QAction *printAt;
    QAction *quitAt;

    QAction *undoAt;
    QAction *cutAt;
    QAction *copyAt;
    QAction *pasteAt;
    QAction *delAt;
    QAction *findAt;
    QAction *findnextAt;
    QAction *replaceAt;
    QAction *gotoAt;
    QAction *seallAt;
    QAction *timeAt;

    QAction *autonumAt;
    QAction *fontAt;

    QAction *statAt;

    QAction *helpAt;
    QAction *aboutAt;

    FindDialog *finddialog;
    ReplaceDialog *replacedialog;
    GotolineDialog *gotodialog;
    AboutDialog *aboutdialog;

    void config();
    void setshortcuts();
    void closeEvent(QCloseEvent *event);
    Ui::MainWindow *ui;

private slots:
    void change();
    void del();
    void showfinddialog();
    void showreplacedialog();
    void showgotodialog();
    void showaboutdialog();
    void time();
    void findresult(QString text,bool upORdown,bool cs);
    void findnextresult();
    void replaceresult(QString pretext,QString nowtext,bool cs);
    void allreplaceresult(QString pretext,QString nowtext,bool cs);
    void gotolineresult(QString line);
    void newfile();
    void openfile();
    void savefile();
    void savefileto();
    void doprint();
    void quitAPP();
    void font();
    void autolineslot();
    void statuslot();
    void cursorchangeslot();
    void helpslot();
};


#endif // MAINWINDOW_H

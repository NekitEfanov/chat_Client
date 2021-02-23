#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDebug>
#include <QInputDialog>
#include <QArrayData>
#include <QMetaObject>
#include <QTextStream>
#include <QFileInfo>
#include <QFile>
#include <QString>
#include <QKeyEvent>
#include <QProcess>
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTcpSocket * socket;
    QByteArray DataSocket;
    QString data;
    QString nameclient;
    void WriteMessage();
    bool eventFilter(QObject *obj, QEvent *event);
    QString Version_this = "0002";
    QByteArray Key = "";
    QString Version_server = "";
    QString ip_server = "";
public slots:
    void connectSuccess();
    void sockReady();
    void sockDisc();

private slots:

    void on_setTextChatButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

#include "mainwindow.h"
#include <iostream>

using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bool bOk;
    QInputDialog Dialog_Name;
    while(true)
    {
        nameclient = Dialog_Name.getText(this,"Authorization","Name:",QLineEdit::Password,0,&bOk);
        if(!bOk){}////////////////////////////////////
        if(nameclient.size()>2&&nameclient.size()<14){break;}
    }
//initialization signal socket
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(connected()), this, SLOT(connectSuccess()));
    connect(socket, SIGNAL(readyRead()),this, SLOT(sockReady()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(sockDisc()));
    socket->connectToHost("95.73.234.62", 60111);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_setTextChatButton_clicked()
{
    data = ui->setTextChatLine->text() + " :: " + nameclient;
    socket->write(data.toUtf8());
    ui->setTextChatLine->clear();
}

void MainWindow::sockDisc()
{
    ui->connected_status->setText("Status - disconnected");
    socket->deleteLater();
}

void MainWindow::connectSuccess()
{
    ui->connected_status->setText("Status - connected");
    
}

void MainWindow::sockReady()
{
    if(socket->waitForConnected(500))
    {
       socket->waitForReadyRead(500);
       DataSocket = socket->readAll();
       ui->chat->setText(DataSocket);
       qDebug() << " -- " << DataSocket;
    }
}
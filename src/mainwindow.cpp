#include "mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Chat");
    //////////////////////////////////////////

    QFile key_file = "Parameters/key.txt";
    if (!key_file.open(QIODevice::ReadOnly)) {
        qWarning("Cannot open file for reading");
    }
    QTextStream in(&key_file);                        //set key
    while (!in.atEnd())
    {
        Key = key_file.readAll();
    }
    key_file.close();
    //////////////////////////////////////////

    QFile ip_file = "Parameters/ip.txt";
    if (!ip_file.open(QIODevice::ReadOnly)) {
        qWarning("Cannot open file for reading");
    }
    QTextStream an(&ip_file);
    while (!an.atEnd())                                //set ip
    {
        ip_server = ip_file.readAll();
    }
    ip_file.close();

    //////////////////////////////////////////

    ui->setTextChatLine->installEventFilter(this);
    ui->chat->setAlignment(Qt::AlignLeft);
    ui->chat->setReadOnly(true);
    ui->connected_status->setStyleSheet("background-color: white;");

    //////////////////////////////////////////

    QInputDialog Dialog_Name;
    bool ok;
    this->setStyleSheet("QInputDialog {background-color: white;}");

    while (true)
    {
        nameclient = Dialog_Name.getText(this,
                                         tr("Authorization"),
                                         tr("Your name:"),
                                         QLineEdit::Normal,
                                         "",
                                         &ok);

        if (!ok)
            exit(0);

        if (nameclient.size() > 2 && nameclient.size() < 13)
            break;

        else
            QMessageBox::critical(this, "Error", "Number of characters 3-12");
    }

    //////////////////////////////////////////

    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(connected()), this, SLOT(connectSuccess()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(sockDisc()));               //initialization signal socket
    socket->connectToHost(ip_server, 60111);
}

    //////////////////////////////////////////

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::WriteMessage()
{
    if (!(ui->setTextChatLine->text().isEmpty()))
    {
    data = nameclient + " :: " + ui->setTextChatLine->text();
    socket->write(data.toUtf8());
    ui->chat->append(data);
    ui->setTextChatLine->clear();
    }
}

void MainWindow::on_setTextChatButton_clicked()
{
   WriteMessage();
}

void MainWindow::sockDisc()
{
    ui->connected_status->setText("Status - disconnected");
    socket->deleteLater();
}

void MainWindow::connectSuccess()
{
    socket->waitForReadyRead(500);
    socket->write(Key);

    if (!(socket->waitForReadyRead(5000))) {
        ui->connected_status->setText("Status - disconnected");
        socket->deleteLater();
    }
    else
    {
        DataSocket = socket->readAll();
        for (size_t i = 0; i < 4; i++) {
            Version_server = Version_server + DataSocket.data()[i];
        }
        if (Version_server.toInt() == Version_this.toInt())
        {
            DataSocket.remove(0, 4);
            ui->chat->append(DataSocket);
            ui->connected_status->setText("Status - connected");
            connect(socket, SIGNAL(readyRead()), this, SLOT(sockReady()));
        }
        else
        {
            ui->connected_status->setText("start update");
            QString program = "Qt5Update.exe";
            QProcess* myProcess = new QProcess(this);
            myProcess->start(program);
            exit(0);
        }
    }
}

void MainWindow::sockReady()
{
    if(socket->waitForConnected(500))
    {
       DataSocket = socket->readAll();
       ui->chat->append(DataSocket);
    }
}
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{

if(event->type() == QEvent::KeyRelease)
{
  QKeyEvent *key = static_cast<QKeyEvent*>(event);

  if(key->key() ==  Qt::Key_Return)
         WriteMessage();
}

return QWidget::eventFilter(obj, event);
}
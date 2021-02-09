#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QBrush br(Qt::TexturePattern);
    br.setTextureImage(QImage("back_graund/1.jpg"));
    QPalette plt = a.palette();
    plt.setBrush(QPalette::Background, br);
    a.setPalette(plt);
    MainWindow w;
    w.show();
    return a.exec();
}

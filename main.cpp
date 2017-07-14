#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowIcon(QIcon(":/huen-icon.svg"));
    w.setFixedSize(678,578);
    w.show();

    return a.exec();
}

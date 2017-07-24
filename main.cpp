#include "mainwindow.h"
#include "oneclick.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    int retVal = 0;

    if (argc > 1) {
        oneClick q;
    } else {
        QApplication a(argc, argv);
        MainWindow w;
        w.setWindowIcon(QIcon(":/huen-icon.svg"));
        w.setFixedSize(678,578);
        w.show();
        retVal = a.exec();
    }

    return retVal;
}

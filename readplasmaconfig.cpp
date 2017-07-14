#include <QFile>
#include <QString>
#include <QStandardPaths>
#include <QDebug>
#include "readplasmaconfig.h"

ReadPlasmaConfig::ReadPlasmaConfig()
{
}

QString ReadPlasmaConfig::getWallpaper()
{
    QString localConfig = QStandardPaths::locate(QStandardPaths::HomeLocation,
                                              "", QStandardPaths::LocateDirectory);
    localConfig += ".config/plasma-org.kde.plasma.desktop-appletsrc";

    QString gotcha;

    QFile file(localConfig);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Unable to open local Plasma config.";
        exit(1);
    }

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.contains("[org.kde.image]", Qt::CaseSensitive)) {
            break;
        }
    }

    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.contains("Image=", Qt::CaseSensitive)) {
            gotcha = line;
            file.close();
            break;
        }
    }

    if (in.atEnd()) {
        qDebug() << "Reached end of Plasma config without finding what I wanted.";
        exit(1);
    }

    return gotcha.mid(13);
    exit(0);
}

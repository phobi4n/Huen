#include <QFile>
#include <QString>
#include <QStandardPaths>
#include <QTextStream>
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

    qDebug() << "02. Plasma config file: " << localConfig;

    QString gotcha;

    QFile file(localConfig);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qFatal("Unable to open local Plasma config.");
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
        qFatal("Reached end of Plasma config without finding what I wanted.");
    }

    return gotcha.mid(13);
}

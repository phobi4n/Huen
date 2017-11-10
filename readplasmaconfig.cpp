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
    QString userHome = QStandardPaths::locate(QStandardPaths::HomeLocation,
                                              "", QStandardPaths::LocateDirectory);
    QString plasmaRc = userHome + ".config/plasma-org.kde.plasma.desktop-appletsrc";
    QString activRc  = userHome + ".config/kactivitymanagerdrc";
    QString gotcha;
    QString curAct;
    QString line;


    QFile activ(activRc);

    if (activ.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream ina(&activ);
        QString holder;

        while (!ina.atEnd()) {
            holder = ina.readLine();

            if (holder.contains("currentActivity"))
                    curAct = holder.mid(16);
        }
        activ.close();
    }


    QFile plas(plasmaRc);

    if (!plas.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qFatal("Unable to open Plasma config.");
    }

    QTextStream in(&plas);

    if (!curAct.isEmpty()) {
        while (!in.atEnd()) {
            line = in.readLine();
            if (line.contains(curAct, Qt::CaseSensitive)) {
                qDebug() << "02. Found: " << line;
                break;
            }
        }
        if (in.atEnd())
            in.seek(0);
    }

    while (!in.atEnd()) {
        line = in.readLine();
        if (line.contains("[org.kde.image]", Qt::CaseSensitive)) {
            break;
        }
    }

    while (!in.atEnd()) {
        line = in.readLine();
        if (line.contains("Image=", Qt::CaseSensitive)) {
            gotcha = line;
            break;
        }
    }

    plas.close();

    if (in.atEnd()) {
        qFatal("Reached end of Plasma config without finding what I wanted.");
    }

    gotcha = gotcha.mid(6);

    if (gotcha.startsWith("file:/"))
        gotcha = gotcha.mid(7);

    return gotcha;
}

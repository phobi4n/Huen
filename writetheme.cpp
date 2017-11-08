#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <stdlib.h>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>
#include "writetheme.h"
#include "template.h"
#include "colourops.h"
#include "defs.h"

extern int luminance(int, int, int);


WriteTheme::WriteTheme()
{
    darkText = false;
}

void WriteTheme::generate(int rr, int gg, int bb)
{
    if (luminance(rr, gg, bb) > DARK_THRESHOLD)
        darkText = true;

    QString replacement =
            QString::number(rr) + ',' +
            QString::number(gg) + ',' +
            QString::number(bb);

    QString plasmaTemplate = QString::fromStdString(pt);
    QString textColour = NORMAL_TEXT;
    QString dialogColour = NORMAL_DIALOG;
    QString buttonText = NORMAL_TEXT;

    if (darkText) {
        textColour = DARK_TEXT;
        dialogColour = LIGHT_DIALOG;
    }

    plasmaTemplate.replace("xxx,xxx,xxx", replacement);
    plasmaTemplate.replace("bbb,bbb,bbb", replacement);
    plasmaTemplate.replace("yyy,yyy,yyy", textColour);
    plasmaTemplate.replace("zzz,zzz,zzz", dialogColour);
    plasmaTemplate.replace("aaa,aaa,aaa", textColour);

    QString destDir= QStandardPaths::locate(QStandardPaths::HomeLocation,
                                              "", QStandardPaths::LocateDirectory);
    destDir += ".local/share/plasma/desktoptheme/Huen";

    QDir dir(destDir);

    if (!dir.exists()) {
        if (!dir.mkpath(destDir)) {
            qFatal("Unable to create local theme directory.");
        }

        QString sourceDir = QDir::homePath() + "/.local/share/huen/* ";
        QString command = "cp -r ";
        command += sourceDir;
        command += destDir;

        int result = system(command.toStdString().c_str());

        if (result != 0) {
                qFatal("Couldn't create local copy of theme.");
            }
    }

    QFile outFile(destDir + "/colors");

    if (outFile.open(QIODevice::WriteOnly)) {
        QTextStream outFileStream(&outFile);
        outFileStream << plasmaTemplate;
        outFile.close();
    } else {
        qFatal("Unable to write colors.");
    }

    system("kwriteconfig5 --file=plasmarc --group=Theme --key=name Default; \
            sleep 0.6; \
            kwriteconfig5 --file=plasmarc --group=Theme --key=name Huen");
}

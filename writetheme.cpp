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

void WriteTheme::setDarkText()
{
    darkText = true;
}


void WriteTheme::generate(int rr, int gg, int bb)
{
    if (luminance(rr, gg, bb) > DARK_TEXT)
        darkText = true;

    QString replacement =
            QString::number(rr) + ',' +
            QString::number(gg) + ',' +
            QString::number(bb);

    QString plasmaTemplate = QString::fromStdString(pt);
    QString textColour = "252,252,252";
    QString dialogColour = "10,10,10";
    QString buttonText = "252,252,252";

    if (darkText) {
        textColour = "34,34,34";
        dialogColour = "228,228,228";
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
        qDebug() << "Making theme directory";
        if (!dir.mkpath(destDir)) {
            qDebug() << "Unable to create local theme directory.";
            exit(EXIT_FAILURE);
        }

        QString sourceDir = "/usr/share/huen/* ";
        QString command = "cp -r ";
        command += sourceDir;
        command += destDir;
        qDebug() << command;

        int result = system(command.toStdString().c_str());

        if (result != 0) {
                qDebug() << "Couldn't create local copy of theme.";
                exit(EXIT_FAILURE);
            }
    }

    QFile outFile(destDir + "/colors");

    if (outFile.open(QIODevice::WriteOnly)) {
        QTextStream outFileStream(&outFile);
        outFileStream << plasmaTemplate;
        outFile.close();
    } else {
        qDebug() << "Unable to write colors.";
        exit(EXIT_FAILURE);
    }

    system("kwriteconfig5 --file=plasmarc --group=Theme --key=name Default; \
            sleep 0.4; \
            kwriteconfig5 --file=plasmarc --group=Theme --key=name Huen");
}

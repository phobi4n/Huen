#include <Magick++.h>
#include <QString>
#include <QDebug>
#include <QProcess>
#include "imagergb.h"

#define SATURATION_MULTIPLIER 1.4

ImageRGB::ImageRGB(QObject *parent)
    :QObject(parent)
{
}

void ImageRGB::processHistogram(QString currentWallpaper)
{
    red = 0;
    green = 0;
    blue = 0;
    
    Magick::Image image(currentWallpaper.toLatin1().data());
    unsigned long counter3 = 0;
    
    std::vector<std::pair<Magick::Color, unsigned long>> histogram;
    Magick::colorHistogram(&histogram, image);
    std::vector<std::pair<Magick::Color, unsigned long>>::const_iterator p = histogram.begin();
    
    while (p != histogram.end()) {
        red = red + static_cast < unsigned long >(p->first.redQuantum());
        green = green + static_cast < unsigned long >(p->first.greenQuantum());
        blue = blue + static_cast < unsigned long >(p->first.blueQuantum());
        ++p;
        ++counter3;
    }

    float fRed = (float)red;
    float fGreen = (float)green;
    float fBlue = (float)blue;

    ImageRGB::changeSaturation(&fRed, &fGreen, &fBlue, SATURATION_MULTIPLIER);

    red = fRed / counter3 * 255 / 65535;
    green = fGreen / counter3 * 255 / 65535;
    blue = fBlue / counter3 * 255 / 65535;

    red = (red > 255) ? 255 : red;
    green = (red > 255) ? 255 : green;
    blue = (red > 255) ? 255 : blue;
}

void ImageRGB::changeSaturation(float *R, float *G, float *B, float change)
{
    float Pr = 0.299;
    float Pg = 0.587;
    float Pb = 0.114;

    float  P=sqrt(
                 (*R)*(*R)*Pr+
                 (*G)*(*G)*Pg+
                 (*B)*(*B)*Pb ) ;

    *R=P+((*R)-P)*change;
    *G=P+((*G)-P)*change;
    *B=P+((*B)-P)*change;
}

void ImageRGB::processHistogramPeak(QString currentWallpaper)
{
    Magick::Image image(currentWallpaper.toLatin1().data());
    red = 0;
    green = 0;
    blue = 0;
    unsigned long tmp = 0;
    unsigned long counter = 0;
    
    std::vector<std::pair<Magick::Color,unsigned long>> histogram;
    Magick::colorHistogram( &histogram, image );
    std::vector<std::pair<Magick::Color,unsigned long>>::const_iterator p=histogram.begin();
    
    while (p != histogram.end())
    {
        tmp = static_cast < unsigned long >(p->second);
        if (tmp>counter) {
            red = static_cast < unsigned long >(p->first.redQuantum());
            green = static_cast < unsigned long >(p->first.greenQuantum());
            blue = static_cast < unsigned long >(p->first.blueQuantum());
            counter = tmp;
        }
       
       p++;
    }
    
    red = red  / 65535 * 255;
    green = green  / 65535 * 255;
    blue = blue  / 65535 * 255;
}

void ImageRGB::processResize(QString currentWallpaper)
{
    QProcess *magickProcess = new QProcess(this);
    QString program = "convert";
    QStringList args;
    args << currentWallpaper << "-resize" << "1x1" << "\"" << "!" << "-format"
         << "%[fx:int(255*r+.5)],%[fx:int(255*g+.5)],%[fx:int(255*b+.5)]" << "info:-";

    magickProcess->start(program, args);
    magickProcess->waitForFinished();

    QString buff(magickProcess->readAllStandardOutput());
    QStringList holder = buff.split(",");

    red =   holder[0].toInt();
    green = holder[1].toInt();
    blue =  holder[2].toInt();
}


float ImageRGB::getRed()
{
    return red;
}

float ImageRGB::getGreen()
{
    return green;
}

float ImageRGB::getBlue()
{
    return blue;
}

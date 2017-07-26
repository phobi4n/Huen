#include <Magick++.h>
#include <QString>
#include <QDebug>
#include <QProcess>
#include "imagergb.h"


ImageRGB::ImageRGB()
{
}

void ImageRGB::processHistogram(QString currentWallpaper)
{
    red = 0;
    green = 0;
    blue = 0;
    
    Magick::Image image(currentWallpaper.toStdString());
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
    Magick::Image image(currentWallpaper.toStdString());
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
    red = 0;
    green = 0;
    blue = 0;

    Magick::Image image(currentWallpaper.toStdString());
    image.resize("1x1");
    Magick::Color val = image.pixelColor(1,1);

    red = val.redQuantum() / 65535 * 256;
    green = val.greenQuantum() / 65535 * 256;
    blue = val.blueQuantum() / 65535 * 256;
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

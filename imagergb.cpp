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
    long counter3 = 0;
    
    std::vector<std::pair<Magick::Color, long>> histogram;
    Magick::colorHistogram(&histogram, image);
    std::vector<std::pair<Magick::Color, long>>::const_iterator p = histogram.begin();
    
    while (p != histogram.end()) {
        red = red + static_cast<long>(p->first.redQuantum());
        green = green + static_cast<long>(p->first.greenQuantum());
        blue = blue + static_cast <long>(p->first.blueQuantum());
        ++p;
        ++counter3;
    }

    red = red / counter3 * 255 / 65535;
    green = green / counter3 * 255 / 65535;
    blue = blue / counter3 * 255 / 65535;
}



void ImageRGB::processHistogramPeak(QString currentWallpaper)
{
    Magick::Image image(currentWallpaper.toStdString());
    red = 0;
    green = 0;
    blue = 0;
    long tmp = 0;
    long counter = 0;
    
    std::vector<std::pair<Magick::Color, long>> histogram;
    Magick::colorHistogram( &histogram, image );
    std::vector<std::pair<Magick::Color, long>>::const_iterator p=histogram.begin();
    
    while (p != histogram.end())
    {
        tmp = static_cast<long>(p->second);

        if (tmp>counter) {
            red = static_cast<long>(p->first.redQuantum());
            green = static_cast<long>(p->first.greenQuantum());
            blue = static_cast<long>(p->first.blueQuantum());
            counter = tmp;
        }
       
       p++;
    }

    red = red * 255/ 65535;
    green = green * 255 / 65535;
    blue = blue * 255 / 65535;
}

void ImageRGB::processResize(QString currentWallpaper)
{
    Magick::Image image(currentWallpaper.toStdString());
    image.resize("1x1");
    Magick::Color val = image.pixelColor(1,1);

    red = static_cast<long>(val.redQuantum()) * 256 / 65535 ;
    green = static_cast<long>(val.greenQuantum()) * 256 / 65535;
    blue = static_cast<long>(val.blueQuantum()) * 256 / 65535;
}



int ImageRGB::getRed()
{
    return red;
}

int ImageRGB::getGreen()
{
    return green;
}

int ImageRGB::getBlue()
{
    return blue;
}

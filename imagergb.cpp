#include <QString>
#include <iostream>
#include <string>
#include "imagergb.h"


ImageRGB::ImageRGB(QString currentWallpaper)
{
    thiswall = currentWallpaper;
    Magick::Image image(thiswall.toStdString());
    Magick::colorHistogram(&histogram, image);
}

void ImageRGB::processHistogram()
{
    red = 0;
    green = 0;
    blue = 0;
    long counter3 = 0;

    std::vector<std::pair<Magick::Color, long>>::const_iterator p = histogram.begin();
    
    while (p != histogram.end()) {
        red = red + p->first.redQuantum();
        green = green + p->first.greenQuantum();
        blue = blue + p->first.blueQuantum();
        ++p;
        ++counter3;
    }

    red = red / counter3 * 255 / 65535;
    green = green / counter3 * 255 / 65535;
    blue = blue / counter3 * 255 / 65535;

}

void ImageRGB::processHistogramPeak()
{
    red = 0;
    green = 0;
    blue = 0;
    long counter = 0;

    std::vector<std::pair<Magick::Color, long>>::const_iterator p=histogram.begin();

    while (p != histogram.end())
    {
        if (p->second > counter) {
            red = p->first.redQuantum();
            green = p->first.greenQuantum();
            blue = p->first.blueQuantum();
            counter = p->second;
        }
       p++;
    }

    red = red * 255/ 65535;
    green = green * 255 / 65535;
    blue = blue * 255 / 65535;
}

int ImageRGB::getRed()
{
    return static_cast<int>(red);
}

int ImageRGB::getGreen()
{
    return static_cast<int>(green);
}

int ImageRGB::getBlue()
{
    return static_cast<int>(blue);
}

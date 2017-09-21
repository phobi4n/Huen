#ifndef IMAGERGB_H
#define IMAGERGB_H

#include <QString>
#include <Magick++.h>


class ImageRGB
{
public:
    explicit ImageRGB(QString);

    int getRed(void);
    int getGreen(void);
    int getBlue(void);

    void processHistogram();
    void processHistogramPeak();
    void processResize();
    void processResizeSTL(QString);
    
private:
    long red;
    long green;
    long blue;
    std::vector<std::pair<Magick::Color, long>> histogram;
//    std::vector<std::pair<Magick::Color, long>> histogram;
    QString thiswall;
};

#endif

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
    
private:
    unsigned long red;
    unsigned long green;
    unsigned long blue;
    std::vector<std::pair<Magick::Color, long>> histogram;
    QString thiswall;
};

#endif

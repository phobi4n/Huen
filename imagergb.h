#ifndef IMAGERGB_H
#define IMAGERGB_H

#include <QString>


class ImageRGB
{
public:
    explicit ImageRGB();

    int getRed(void);
    int getGreen(void);
    int getBlue(void);

    void processHistogram(QString);
    void processHistogramPeak(QString);
    void processResize(QString);
    void processResizeSTL(QString);
    
private:
    long red;
    long green;
    long blue;
};

#endif

#ifndef IMAGERGB_H
#define IMAGERGB_H

#include <QString>


class ImageRGB
{
public:
    explicit ImageRGB();

    float getRed(void);
    float getGreen(void);
    float getBlue(void);

    void processHistogram(QString);
    void processHistogramPeak(QString);
    void processResize(QString);
    void processResizeSTL(QString);
    
private:
    void changeSaturation(float *, float *, float *, float);

    float red;
    float green;
    float blue;
};

#endif

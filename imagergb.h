#ifndef IMAGERGB_H
#define IMAGERGB_H

#include <QObject>
#include <QString>


class ImageRGB : public QObject
{
    Q_OBJECT
public:
    explicit ImageRGB(QObject *parent = 0);

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

#include "colourops.h"
#include <QDebug>

int colourOps1(void)
{
    qDebug() << "IN COLOROPS";
    return 2;
}


int luminance(int r, int g, int b)
{
    int min = (r <= g) ? r : g;
    min = (min <= b) ? min : b;

    int max = (r >= g) ? r : g;
    max = (max >= b) ? max : b;

    int lightness = ((min + max) / 2);
    qDebug() << "Lightness" << lightness;
    return lightness;
}


int saturation(int r, int g, int b)
{
    int min = (r <= g) ? r : g;
    min = (min <= b) ? min : b;

    int max = (r >= g) ? r : g;
    max = (max >= b) ? max : b;

    float saturation = 0.0;

    if (min != max) {
        float minF = min / 255.0;
        float maxF = max / 255.0;

        float lightness = ((minF + maxF) / 2);

        if (lightness < 0.5)
            saturation = (maxF - minF) / (maxF + minF);
        else
            saturation = (maxF - minF) / (2.0 - maxF - minF);
    }

    return static_cast<int>(saturation * 255.0);
}

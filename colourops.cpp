#include "colourops.h"
#include <math.h>
#include <QDebug>


int luminance(int r, int g, int b)
{
    int min = (r <= g) ? r : g;
    min = (min <= b) ? min : b;

    int max = (r >= g) ? r : g;
    max = (max >= b) ? max : b;

    int lightness = ((min + max) / 2);
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

void changeSaturation(float *R, float *G, float *B, float change)
{
    float Pr = 0.299;
    float Pg = 0.587;
    float Pb = 0.114;

    qDebug() << *R << *G << *B;
    float  P=sqrt(
                 (*R)*(*R)*Pr+
                 (*G)*(*G)*Pg+
                 (*B)*(*B)*Pb ) ;

    *R=P+((*R)-P)*change;
    *G=P+((*G)-P)*change;
    *B=P+((*B)-P)*change;
    qDebug() << *R << *G << *B;
}

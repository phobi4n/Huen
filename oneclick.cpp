#include "oneclick.h"
#include "readplasmaconfig.h"
#include "imagergb.h"
#include "mainwindow.h"
#include "writetheme.h"
#include <QDebug>

oneClick::oneClick()
{
    ReadPlasmaConfig plasma;
    QString wall = QString(plasma.getWallpaper());

    ImageRGB wallpaperImage;
    wallpaperImage.processResize(wall);
    rR = static_cast<int>(wallpaperImage.getRed());
    gR = static_cast<int>(wallpaperImage.getGreen());
    bR = static_cast<int>(wallpaperImage.getBlue());

    wallpaperImage.processHistogramPeak(wall);
    rP = static_cast<int>(wallpaperImage.getRed());
    gP = static_cast<int>(wallpaperImage.getGreen());
    bP = static_cast<int>(wallpaperImage.getBlue());

    int satPeak = getSaturation(rP, gP, bP);
    int satResize = getSaturation(rR, gR,bR);

    if (satPeak > satResize) {
        rr = rP;
        gg = gP;
        bb = bP;
    } else {
        rr = rR;
        gg = gR;
        bb = bR;
    }

    WriteTheme newTheme;

    if (darkText(rr, gg, bb))
            newTheme.setDarkText();

    QString baseColor =
            QString::number(rr) + ',' +
            QString::number(gg) + ',' +
            QString::number(bb);

    newTheme.generate(baseColor);
    exit(0);
}

int oneClick::getSaturation(int r, int g, int b)
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

bool oneClick::darkText(int r, int g, int b)
{
    int min = (r <= g) ? r : g;
        min = (min <= b) ? min : b;

        int max = (r >= g) ? r : g;
        max = (max >= b) ? max : b;

        int lightness = ((min + max) / 2);
        return (lightness > 168) ? true : false;
}

#include "oneclick.h"
#include "readplasmaconfig.h"
#include "imagergb.h"
#include "writetheme.h"
#include "colourops.h"

extern int luminance(int, int, int);
extern int saturation(int, int, int);


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

    int satPeak = saturation(rP, gP, bP);
    int satResize = saturation(rR, gR,bR);

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
    newTheme.generate(rr, gg, bb);
}

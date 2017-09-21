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

    ImageRGB wallpaperImage(wall);
    wallpaperImage.processResize();
    rR = wallpaperImage.getRed();
    gR = wallpaperImage.getGreen();
    bR = wallpaperImage.getBlue();

    wallpaperImage.processHistogramPeak();
    rP = wallpaperImage.getRed();
    gP = wallpaperImage.getGreen();
    bP = wallpaperImage.getBlue();

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

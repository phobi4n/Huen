#include <QDir>
#include <QDebug>
#include "oneclick.h"
#include "readplasmaconfig.h"
#include "imagergb.h"
#include "writetheme.h"
#include "colourops.h"

extern int luminance(int, int, int);
extern int saturation(int, int, int);


oneClick::oneClick()
{
    QString checkData = QDir::homePath() + "/.local/share/huen";
    QDir dir(checkData);

    qDebug() << "01. Huen data directory: " << checkData;

    if (!dir.exists()) {
        qFatal("Data couldn't be found. Exiting.");
    }

    ReadPlasmaConfig plasma;
    QString wall = QString(plasma.getWallpaper());

    qDebug() << "03. Wallpaper path from config file: " << wall;

    ImageRGB wallpaperImage(wall);
    wallpaperImage.processHistogram();
    rA = wallpaperImage.getRed();
    gA = wallpaperImage.getGreen();
    bA = wallpaperImage.getBlue();

    changeSaturation(&rA, &gA, &bA, 1.7);

    rA = (rA > 255.0) ? 255.0 : rA;
    gA = (gA > 255.0) ? 255.0 : gA;
    bA = (bA > 255.0) ? 255.0 : bA;
    rA = (rA < 0.0) ? 0.0 : rA;
    gA = (gA < 0.0) ? 0.0 : gA;
    bA = (bA < 0.0) ? 0.0 : bA;

    wallpaperImage.processHistogramPeak();
    rP = wallpaperImage.getRed();
    gP = wallpaperImage.getGreen();
    bP = wallpaperImage.getBlue();

    lumAvg = luminance((int)rA,(int)gA,(int)bA);
    lumPk  = luminance(rP,gP,bP);

    WriteTheme newTheme;

    r = (int)rA;
    g = (int)gA;
    b = (int)bA;

    if ((lumPk < lumAvg) && (lumPk > 10)) {
        r = rP;
        g = gP;
        b = bP;
    }

    newTheme.generate(r, g, b);
}

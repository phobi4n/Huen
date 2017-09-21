#include "oneclick.h"
#include "readplasmaconfig.h"
#include "imagergb.h"
#include "writetheme.h"
#include "colourops.h"
#include <QDebug>

extern int luminance(int, int, int);
extern int saturation(int, int, int);


oneClick::oneClick()
{
    ReadPlasmaConfig plasma;
    QString wall = QString(plasma.getWallpaper());

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

    qDebug() << "Lum Avg : " << luminance(rA,gA,bA);
    qDebug() << "Lum Peak: " << luminance(rP,gP,bP);

    WriteTheme newTheme;
    newTheme.generate((int)rA, (int)gA, (int)bA);
}

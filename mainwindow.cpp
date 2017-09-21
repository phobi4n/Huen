#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "readplasmaconfig.h"
#include "imagergb.h"
#include "writetheme.h"
#include "colourops.h"
#include "defs.h"
#include <QString>
#include <QPainter>
#include <QDateTime>
#include <QApplication>
#include <QThread>
#include <QtConcurrent/qtconcurrentrun.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    labelWidth = ui->label->width();
    labelHeight = ui->label->height();

    loadPlasmaWallpaper();

}


void MainWindow::loadPlasmaWallpaper()
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
    pixmap.load(wall);

    wallpaperImage.processHistogramPeak();
    rP = wallpaperImage.getRed();
    gP = wallpaperImage.getGreen();
    bP = wallpaperImage.getBlue();

//    wallpaperImage.processResize();
//    rR = wallpaperImage.getRed();
//    gR = wallpaperImage.getGreen();
//    bR = wallpaperImage.getBlue();

    holder = pixmap.scaled(labelWidth, labelHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label->setAlignment(Qt::AlignCenter);

    rr = rA;
    gg = gA;
    bb = bA;

    ui->radioAverage->setChecked(true);
    drawPreview(holder, rr, gg, bb);
}

void MainWindow::drawPreview(QPixmap preview, int r, int g, int b)
{
    bool d = false;

    if (luminance(rr, gg, bb) > DARK_THRESHOLD)
            d = true;

    QPainter paint(&preview);
    QFont font = paint.font();
    font.setBold(true);
    paint.setFont(font);

    int panelHeight = 18;
    const QRect panel = QRect(0, preview.height() - panelHeight, preview.width(), panelHeight);
    paint.fillRect(panel, QColor(r,g,b,255));

    QString tformat = "HH:mm a   ";
    QDateTime now = QDateTime::currentDateTime();
    QString showTime = now.toString(tformat);

    if (d)
        paint.setPen(QColor(34,34,34,255));
    else
        paint.setPen(QColor(252,252,252,255));

    paint.drawText(panel, Qt::AlignRight, showTime);
    paint.drawText(panel, Qt::AlignLeft, "  K");
    ui->label->setPixmap(preview);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_radioAverage_clicked()
{
    rr = rA;
    gg = gA;
    bb = bA;

    drawPreview(holder, rr, gg, bb);
}

void MainWindow::on_radioPeak_clicked()
{
    rr = rP;
    gg = gP;
    bb = bP;

    drawPreview(holder, rr, gg, bb);
}



void MainWindow::on_pushReload_clicked()
{
    loadPlasmaWallpaper();
}

void MainWindow::on_pushApply_clicked()
{
    WriteTheme newTheme;
    newTheme.generate(rr, gg, bb);
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "readplasmaconfig.h"
#include "imagergb.h"
#include "writetheme.h"
#include <QDebug>
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

void workerAverage(QString *wall, int *r, int *g, int *b)
{
    ImageRGB wallpaperImage;
    wallpaperImage.processHistogram(*wall);
    *r = static_cast<int>(wallpaperImage.getRed());
    *g = static_cast<int>(wallpaperImage.getGreen());
    *b = static_cast<int>(wallpaperImage.getBlue());
}

void workerPeak(QString *wall, int *r, int *g, int *b)
{
    ImageRGB wallpaperImage;
    wallpaperImage.processHistogramPeak(*wall);
    *r = static_cast<int>(wallpaperImage.getRed());
    *g = static_cast<int>(wallpaperImage.getGreen());
    *b = static_cast<int>(wallpaperImage.getBlue());
}


void MainWindow::loadPlasmaWallpaper()
{
    ReadPlasmaConfig plasma;
    QString wall = QString(plasma.getWallpaper());

    QFuture<void> t1 = QtConcurrent::run(workerAverage, &wall, &rA, &gA, &bA);
    QFuture<void> t2 = QtConcurrent::run(workerPeak, &wall, &rP, &gP, &bP);

    pixmap.load(wall);

    ImageRGB wallpaperImage;
    wallpaperImage.processResize(wall);
    rR = static_cast<int>(wallpaperImage.getRed());
    gR = static_cast<int>(wallpaperImage.getGreen());
    bR = static_cast<int>(wallpaperImage.getBlue());

    holder = pixmap.scaled(labelWidth, labelHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label->setAlignment(Qt::AlignCenter);

    t1.waitForFinished();
    t2.waitForFinished();

    rr = rA;
    gg = gA;
    bb = bA;

    ui->radioAverage->setChecked(true);
    drawPreview(holder, rr, gg, bb, 0);
}

bool MainWindow::darkText(int r, int g, int b)
{
    int min = (r <= g) ? r : g;
        min = (min <= b) ? min : b;

        int max = (r >= g) ? r : g;
        max = (max >= b) ? max : b;

        int lightness = ((min + max) / 2);
        return (lightness > 168) ? true : false;
}

void MainWindow::drawPreview(QPixmap preview, int r, int g, int b, bool d)
{
    QPainter paint(&preview);
    QFont font = paint.font();
    font.setBold(true);
    paint.setFont(font);

    int panelHeight = 18;
    const QRect panel = QRect(0, preview.height() - panelHeight, preview.width(), panelHeight);
    paint.fillRect(panel, QColor(r,g,b,255));

    QString tformat = "HH:mm   ";
    QDateTime now = QDateTime::currentDateTime();
    QString showTime = now.toString(tformat);

    if (d)
        paint.setPen(QColor(34,34,34,255));
    else
        paint.setPen(QColor(252,252,252,255));

    paint.drawText(panel, Qt::AlignRight, showTime);
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

    bool d = MainWindow::darkText(rr, gg, bb);
    drawPreview(holder, rr, gg, bb, d);
}

void MainWindow::on_radioPeak_clicked()
{
    rr = rP;
    gg = gP;
    bb = bP;

    bool d = MainWindow::darkText(rr, gg, bb);
    drawPreview(holder, rr, gg, bb, d);
}

void MainWindow::on_radioResize_clicked()
{
    rr = rR;
    gg = gR;
    bb = bR;

    bool d = MainWindow::darkText(rr, gg, bb);
    drawPreview(holder, rr, gg, bb, d);
}

void MainWindow::on_pushReload_clicked()
{
    loadPlasmaWallpaper();
}

void MainWindow::on_pushApply_clicked()
{
    qDebug() << rr << gg << bb;
    WriteTheme newTheme;

    if (MainWindow::darkText(rr, gg, bb))
            newTheme.setDarkText();

    QString baseColor =
            QString::number(rr) + ',' +
            QString::number(gg) + ',' +
            QString::number(bb);

    newTheme.generate(baseColor);
}

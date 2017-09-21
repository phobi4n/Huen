#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_radioAverage_clicked();
    void on_radioPeak_clicked();
    void on_pushReload_clicked();
    void on_pushApply_clicked();

private:
    Ui::MainWindow *ui;

    QPixmap pixmap;
    QPixmap holder;
    QPixmap preview;

    int rr;
    int gg;
    int bb;
    float rA;
    float gA;
    float bA;
    int rP;
    int gP;
    int bP;
    int rR;
    int gR;
    int bR;
    int labelWidth;
    int labelHeight;

    void drawPreview(QPixmap, int, int, int);
    void loadPlasmaWallpaper(void);
};

#endif // MAINWINDOW_H

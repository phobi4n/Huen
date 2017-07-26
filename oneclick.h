#ifndef ONECLICK_H
#define ONECLICK_H

#include <QString>

class oneClick
{
public:
    oneClick();

private:
    int rR;
    int gR;
    int bR;
    int rP;
    int gP;
    int bP;
    int rr;
    int gg;
    int bb;

    int getSaturation(int, int, int);
    bool darkText(int, int, int);
};

#endif // ONECLICK_H

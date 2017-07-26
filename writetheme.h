#ifndef WRITETHEME_H
#define WRITETHEME_H

#include <QString>
#include <QFile>
#include <QTextStream>

class WriteTheme
{
public:
    WriteTheme();
    void generate(int, int, int);
    void setDarkText();
    
private:
    bool darkText;
};


#endif

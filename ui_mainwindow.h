/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *cancelButton;
    QGroupBox *groupBox;
    QRadioButton *radioAverage;
    QRadioButton *radioPeak;
    QLabel *label;
    QPushButton *pushApply;
    QPushButton *pushReload;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(643, 525);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        cancelButton = new QPushButton(centralWidget);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setGeometry(QRect(528, 480, 88, 34));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 420, 191, 91));
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        radioAverage = new QRadioButton(groupBox);
        radioAverage->setObjectName(QStringLiteral("radioAverage"));
        radioAverage->setGeometry(QRect(20, 30, 151, 22));
        radioPeak = new QRadioButton(groupBox);
        radioPeak->setObjectName(QStringLiteral("radioPeak"));
        radioPeak->setGeometry(QRect(20, 60, 105, 22));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 600, 375));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setLineWidth(1);
        label->setMidLineWidth(0);
        pushApply = new QPushButton(centralWidget);
        pushApply->setObjectName(QStringLiteral("pushApply"));
        pushApply->setGeometry(QRect(420, 480, 88, 34));
        pushReload = new QPushButton(centralWidget);
        pushReload->setObjectName(QStringLiteral("pushReload"));
        pushReload->setGeometry(QRect(530, 420, 88, 34));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);
        QObject::connect(cancelButton, SIGNAL(clicked()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Huen", Q_NULLPTR));
        cancelButton->setText(QApplication::translate("MainWindow", "&Close", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "Color Sample &Method", Q_NULLPTR));
        radioAverage->setText(QApplication::translate("MainWindow", "A&verage Saturated", Q_NULLPTR));
        radioPeak->setText(QApplication::translate("MainWindow", "Pea&k Count", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        pushApply->setText(QApplication::translate("MainWindow", "&Apply", Q_NULLPTR));
        pushReload->setText(QApplication::translate("MainWindow", "Re&load", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

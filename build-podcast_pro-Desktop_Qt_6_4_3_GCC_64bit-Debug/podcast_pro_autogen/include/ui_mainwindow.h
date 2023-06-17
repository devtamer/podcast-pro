/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QSlider *progressBar;
    QListWidget *PodcastList;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QSlider *volumeSlider;
    QLabel *volumeLabel;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QPushButton *backButton;
    QPushButton *playButton;
    QPushButton *skipButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(400, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        progressBar = new QSlider(centralwidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(50, 350, 300, 25));
        progressBar->setOrientation(Qt::Horizontal);
        PodcastList = new QListWidget(centralwidget);
        PodcastList->setObjectName(QString::fromUtf8("PodcastList"));
        PodcastList->setGeometry(QRect(0, 0, 400, 192));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(330, 210, 54, 114));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        volumeSlider = new QSlider(layoutWidget);
        volumeSlider->setObjectName(QString::fromUtf8("volumeSlider"));
        volumeSlider->setOrientation(Qt::Vertical);

        verticalLayout->addWidget(volumeSlider);

        volumeLabel = new QLabel(layoutWidget);
        volumeLabel->setObjectName(QString::fromUtf8("volumeLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(volumeLabel->sizePolicy().hasHeightForWidth());
        volumeLabel->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(volumeLabel);

        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(120, 380, 254, 32));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        backButton = new QPushButton(layoutWidget1);
        backButton->setObjectName(QString::fromUtf8("backButton"));

        horizontalLayout->addWidget(backButton);

        playButton = new QPushButton(layoutWidget1);
        playButton->setObjectName(QString::fromUtf8("playButton"));

        horizontalLayout->addWidget(playButton);

        skipButton = new QPushButton(layoutWidget1);
        skipButton->setObjectName(QString::fromUtf8("skipButton"));

        horizontalLayout->addWidget(skipButton);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 400, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        volumeLabel->setText(QCoreApplication::translate("MainWindow", "Volume", nullptr));
        backButton->setText(QCoreApplication::translate("MainWindow", "<", nullptr));
        playButton->setText(QCoreApplication::translate("MainWindow", "Pause", nullptr));
        skipButton->setText(QCoreApplication::translate("MainWindow", ">", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

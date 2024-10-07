#include "mainwindow.h"

#include <QApplication>
#include <QDir>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("://logo.png"));
    a.setApplicationName("Podcast Pro");
    a.setOrganizationName("devtamer");
    a.setOrganizationDomain("https://github.com/devtamer/podcast-pro");
    MainWindow w;
    w.show();
    return a.exec();
}

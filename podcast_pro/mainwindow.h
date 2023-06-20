#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "audioplayer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    AudioPlayer *m_audioPlayer;
    void onUploadFiles();
    void updateTitle(const QString &title);
    void updateArtist(const QString &artist);
    void updateCoverArt(const QImage &coverArt);

};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "audioplayer.h"
#include "audiocontrols.h"
#include <QProgressBar>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

private:
    Ui::MainWindow *ui;
    AudioPlayer *m_audioPlayer;
    QString formatTime(qint64 timeInMs);
    std::map<int, const QString> playList;
    AudioControls* audio_control;
    QAction* uploadFile;
    void onUploadFiles();
    void updateTitle(const QString &title);
    void updateArtist(const QString &artist);
    void updateCoverArt(const QImage &coverArt);
    void showContextMenu(const QPoint &pos);
    void deleteItem();
    void updatePlayButton(QMediaPlayer::PlaybackState state);
    void updateProgressBarPosition(qint64 position);
    void updateProgressBarMaximum(qint64 duration);
    void updatePositionDurationDisplay(qint64 position, qint64 duration);
    void addFileToList(const QString &fileName);
    void showAudioPosition(qint64 position);
    void changePlayerPosition(int position);
    void itemDoubleClicked(QListWidgetItem* item);

};
#endif // MAINWINDOW_H

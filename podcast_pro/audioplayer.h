#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QMediaMetaData>


class AudioPlayer : public QObject
{
    // enables signals and slots
    Q_OBJECT
public:
    // constructor prevents compiler from using this for implicit conversions
    explicit AudioPlayer(QObject *parent = nullptr);
    void loadFile(const QString &filePath);
    void play();
    void pause();
    void setVolume(int volume);
    void loadFiles(const QStringList &filePaths);
    void skip();
    void previous();
    QMediaPlayer::State state() const;
    QMediaPlayer::MediaStatus mediaStatus() const;
    QString getTitle() const;
    QImage getCoverImage() const;
    qint64 getPosition() const;
    qint64 getDuration() const;
private:
    QMediaPlayer *m_player;
    std::vector<QString> m_files;
    int m_currentIndex=0;

};

#endif // AUDIOPLAYER_H

#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QAudioOutput>
#include <QListWidget>
#include <QPicture>
#include <QString>



class AudioPlayer : public QObject
{
    // enables signals and slots
    Q_OBJECT
public:
    // constructor prevents compiler from using this for implicit conversions
    explicit AudioPlayer(QObject *parent = nullptr);
    ~AudioPlayer();
    void loadFile(const QString &filePath);
    void play();
    void pause();
    void setVolume(float volume);
    void loadFiles(const QStringList &filePaths, QListWidget *list);
    void skip();
    void playSelected(int index);
    void setAudioPosition(qint64 position);
    void previous();
    void getCoverImage(const std::string &path);
    QMediaPlayer::PlaybackState state() const;
    QMediaPlayer::MediaStatus mediaStatus() const;
    QString getTitle() const;
    QString getArtist() const;
    QString getPositionAndDuration() const;
    qint64 getPosition() const;
    qint64 getDuration() const;
signals:
    void titleChanged(const QString &title);
    void coverImageChanged(const QImage &coverImage);
    void artistChanged(const QString &artist);
    void hasAudioChanged(bool available);
    void positionChanged(qint64 position);
    void positionAndDurationChanged(const QString PDchanged);
    void fileLoaded(const QString &fileName);
    void durationChanged(qint64 duration);
    void stateChanged(QMediaPlayer::PlaybackState state);
private:
    QMediaPlayer *m_player;
    // map from file path to images (thumbnails)
    std::map<std::string, QImage> m_coverCache;
    QAudioOutput *m_audioOutput;
    std::vector<QString> m_files;
    int m_currentIndex=-1;
    void setCurrentFile(int current_index);

};

#endif // AUDIOPLAYER_H

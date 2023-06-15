#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QObject>
#include <QMediaPlayer>

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

private:
    QMediaPlayer *m_player;

};

#endif // AUDIOPLAYER_H

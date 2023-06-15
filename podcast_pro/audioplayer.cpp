#include "audioplayer.h"

AudioPlayer::AudioPlayer(QObject *parent)
    : QObject{parent}, m_player(new QMediaPlayer(this))
{
    m_player->setVolume(50);

}

void AudioPlayer::loadFile(const QString &filePath){
    m_player->setMedia(QUrl::fromLocalFile(filePath));

}
void AudioPlayer::play(){
    m_player->play();
}
void AudioPlayer::pause(){
    m_player->pause();
}
void AudioPlayer::setVolume(int volume){
    m_player->setVolume(volume);

}

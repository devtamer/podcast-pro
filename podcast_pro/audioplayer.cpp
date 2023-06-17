#include "audioplayer.h"

AudioPlayer::AudioPlayer(QObject *parent)
    : QObject{parent}, m_player(new QMediaPlayer(this))
{
    m_player->setVolume(50);

}
// not needed right now
//void AudioPlayer::loadFile(const QString &filePath){
//    m_player->setMedia(QUrl::fromLocalFile(filePath));

//}
// add files to qString vector
// skip method: check if vector has anything in it,
// if it does then iterate to next file
void AudioPlayer::loadFiles(const QStringList &filePaths){
    m_files = std::vector<QString>(filePaths.begin(), filePaths.end());
    if(!m_files.empty()){
        m_currentIndex = 0;
        m_player->setMedia(QUrl::fromLocalFile(m_files[m_currentIndex]));

    }
}
void AudioPlayer::skip(){
    if(m_files.empty()){
        return;
    }
    m_currentIndex = (m_currentIndex + 1) % m_files.size();
    m_player->setMedia(QUrl::fromLocalFile(m_files[m_currentIndex]));

}
// previous method: check if vector has anything in it,
// if it does go to previous item (until 0 index)
void AudioPlayer::previous(){
    if(m_files.empty()){
        return;
    }
    m_currentIndex = (m_currentIndex - 1 + m_files.size()) % m_files.size();
    m_player->setMedia(QUrl::fromLocalFile(m_files[m_currentIndex]));
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
QMediaPlayer::State AudioPlayer::state() const {
    return m_player->state();
}
QMediaPlayer::MediaStatus AudioPlayer::mediaStatus() const {
    return m_player->mediaStatus();
}

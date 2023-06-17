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
    QVector<QString> qVecFilePaths = QVector<QString>(filePaths.begin(), filePaths.end());
    m_files = filePaths.toVector().toStdVector();

}
void AudioPlayer::skip(){
    if(m_files.empty()){
        return
    }
    for(int i = m_currentIndex; i <= (m_files.size()-i); i++){

    }
}
// previous method: check if vector has anything in it,
// if it does go to previous item (until 0 index)
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

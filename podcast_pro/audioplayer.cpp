#include "audioplayer.h"
#include "qimage.h"
#include <QFileInfo>
AudioPlayer::AudioPlayer(QObject *parent)
    : QObject{parent}, m_player(new QMediaPlayer(this)),
      m_audioOutput(new QAudioOutput(this))
{
    m_player->setAudioOutput(m_audioOutput);
    connect(m_player, &QMediaPlayer::metaDataChanged, this, [&]() {
        emit titleChanged(getTitle());
        emit coverImageChanged(getCoverImage());
        emit artistChanged(getArtist());
    });
    connect(m_player, &QMediaPlayer::errorOccurred, this, [&](QMediaPlayer::Error error) {
        qDebug() << "Error occurred: " << error;
    });

    // position changed
    connect(m_player, &QMediaPlayer::positionChanged, this, [&](qint64 position) {
        emit positionChanged(position);
    });
    // duration changed signal
    connect(m_player, &QMediaPlayer::durationChanged, this, [&](qint64 duration) {
        emit durationChanged(duration);
    });
    // stateChanged signal (play/pause)
    connect(m_player, &QMediaPlayer::playbackStateChanged, this, [&](QMediaPlayer::PlaybackState state) {
        emit stateChanged(state);
    });
}
AudioPlayer::~AudioPlayer() {
    delete m_player;
    delete m_audioOutput; // new line
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
        m_player->setSource(QUrl::fromLocalFile(m_files[m_currentIndex]));

        // add the file paths to the list widget
        for(const auto &filePath : filePaths){
            QFileInfo fileInfo(filePath);
            emit fileLoaded(fileInfo.fileName());
        }


    }
}
void AudioPlayer::skip(){
    if(m_files.empty()){
        return;
    }
    m_currentIndex = (m_currentIndex + 1) % m_files.size();
    m_player->setSource(QUrl::fromLocalFile(m_files[m_currentIndex]));

}
// previous method: check if vector has anything in it,
// if it does go to previous item (until 0 index)
void AudioPlayer::previous(){
    if(m_files.empty()){
        return;
    }
    m_currentIndex = (m_currentIndex - 1 + m_files.size()) % m_files.size();
    m_player->setSource(QUrl::fromLocalFile(m_files[m_currentIndex]));
}
void AudioPlayer::play(){
    m_player->play();
}
void AudioPlayer::pause(){
    m_player->pause();
}
void AudioPlayer::setVolume(float volume){
    m_audioOutput->setVolume(volume);
}
QMediaPlayer::PlaybackState AudioPlayer::state() const {
    return m_player->playbackState();
}
QMediaPlayer::MediaStatus AudioPlayer::mediaStatus() const {
    return m_player->mediaStatus();
}
QString AudioPlayer::getTitle() const {
    QMediaMetaData metaData = m_player->metaData();
    return metaData.value(QMediaMetaData::Title).toString();
}
QString AudioPlayer::getArtist() const {
    QMediaMetaData metaData = m_player->metaData();
    return metaData.value(QMediaMetaData::AlbumArtist).toString();
}

QImage AudioPlayer::getCoverImage() const {
    QMediaMetaData metaData = m_player->metaData();
    return metaData.value(QMediaMetaData::ThumbnailImage).value<QImage>();
}
qint64 AudioPlayer::getPosition() const {
    return m_player->position();
}
qint64 AudioPlayer::getDuration() const {
    return m_player->duration();
}

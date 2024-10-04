#include "audioplayer.h"
#include "qimage.h"
#include <QFileInfo>
#include <QByteArray>
#include <taglib/mpegfile.h>
#include <taglib/id3v2tag.h>
#include <taglib/id3v2frame.h>
#include <taglib/id3v2header.h>
#include <taglib/attachedpictureframe.h>

AudioPlayer::AudioPlayer(QObject *parent)
    : QObject{parent}, m_player(new QMediaPlayer(this)),
      m_audioOutput(new QAudioOutput(this))
{
    m_player->setAudioOutput(m_audioOutput);
    connect(m_player, &QMediaPlayer::metaDataChanged, this, [&]() {
        emit titleChanged(getTitle());
        emit artistChanged(getArtist());
        emit positionAndDurationChanged(getPositionAndDuration());
    });
    connect(m_player, &QMediaPlayer::errorOccurred, this, [&](QMediaPlayer::Error error) {
        qDebug() << "Error occurred: " << error;
    });

    // position changed
    connect(m_player, &QMediaPlayer::positionChanged, this, [&](qint64 position) {
        emit positionChanged(position);
    });
    connect(m_player, &QMediaPlayer::hasAudioChanged, this, [&](bool available) {
        emit hasAudioChanged(available);
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
void AudioPlayer::loadFiles(const QStringList &filePaths, QListWidget *list){
    for(const auto &filePath: filePaths){
        m_files.push_back(filePath);
    }

    if (!m_files.empty())
    {
        if(m_currentIndex == -1){
            m_currentIndex = 0;
            m_player->setSource(QUrl::fromLocalFile(m_files[m_currentIndex]));
            getCoverImage(m_files[m_currentIndex].toStdString());
        }

        // add the file paths to the list widget
        for(int i = 0; i < filePaths.size(); i++){
            QString filePath = filePaths[i];
            QFileInfo fileInfo(filePath);
            QListWidgetItem *item = new QListWidgetItem(fileInfo.baseName());
            item->setData(Qt::UserRole, m_files.size()-filePaths.size()+i);
            list->addItem(item);
        }
    }
}

void AudioPlayer::setCurrentFile(int m_currentIndex){
    // set source and cover art
    m_player->setSource(QUrl::fromLocalFile(m_files[m_currentIndex]));
    getCoverImage(m_files[m_currentIndex].toStdString());
}
void AudioPlayer::skip(){
    if(m_files.empty()){
        return;
    }
    m_currentIndex = (m_currentIndex + 1) % m_files.size();
    setCurrentFile(m_currentIndex);

}
void AudioPlayer::playSelected(int index){
    setCurrentFile(index);

}
// previous method: check if vector has anything in it,
// if it does go to previous item (until 0 index)
void AudioPlayer::previous(){
    if(m_files.empty()){
        return;
    }
    m_currentIndex = (m_currentIndex - 1 + m_files.size()) % m_files.size();
    setCurrentFile(m_currentIndex);
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
void AudioPlayer::setAudioPosition(qint64 position) {
    m_player->setPosition(position);
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
QString AudioPlayer::getPositionAndDuration() const {
    QString result = (QString::number(m_player->position()) + " / " + QString::number(m_player->duration()));
    return result;
}
QString AudioPlayer::getArtist() const {
    QMediaMetaData metaData = m_player->metaData();
    return metaData.value(QMediaMetaData::AlbumArtist).toString();
}
void AudioPlayer::getCoverImage(const std::string &path) {
    TagLib::MPEG::File file(path.c_str());

    TagLib::ID3v2::Tag* tag = file.ID3v2Tag();
    TagLib::ID3v2::FrameList frameList = tag->frameList("APIC");

    if (!frameList.isEmpty()) {
        TagLib::ID3v2::AttachedPictureFrame* picFrame = static_cast<TagLib::ID3v2::AttachedPictureFrame*>(frameList.front());

        QByteArray imageData(picFrame->picture().data(), picFrame->picture().size());

        emit coverImageChanged(QImage::fromData(imageData));
    }

    return;
}

qint64 AudioPlayer::getPosition() const {
    return m_player->position();
}
qint64 AudioPlayer::getDuration() const {
    return m_player->duration();
}

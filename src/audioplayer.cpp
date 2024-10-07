#include "audioplayer.h"
#include "qimage.h"
#include <QFileInfo>
#include <QByteArray>
#include <QHBoxLayout>
#include <QSettings>
#include <QLabel>
#include <QTimer>
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

    // should trigger every time timer is triggered
    QTimer *saveTimer = new QTimer(this);
    connect(saveTimer, &QTimer::timeout, this, [this](){
        if(state() == QMediaPlayer::PlayingState){
            QSettings settings;
            settings.setValue(getFilePath(m_currentIndex), m_player->position());
        }
    });
    saveTimer->start(10000);

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
    connect(m_player, &QMediaPlayer::mediaStatusChanged, this, [&](QMediaPlayer::MediaStatus status){
        if(status==QMediaPlayer::MediaStatus::BufferedMedia)
        {
            UpdatePosition();
        }

    });

    // stateChanged signal (play/pause)
    connect(m_player, &QMediaPlayer::playbackStateChanged, this, [&](QMediaPlayer::PlaybackState state) {
        if (state == QMediaPlayer::PausedState) {
            // Save the position when playback is paused or stopped
            QSettings settings;
            settings.setValue(getFilePath(m_currentIndex), m_player->position());
        }
        emit stateChanged(state);
    });

}
AudioPlayer::~AudioPlayer() {
    delete m_player;
    delete m_audioOutput; // new line
}

QWidget *getCustomWidget(QLabel *titleLabel, QLabel *durationLabel){
    QWidget *titleDur = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout(titleDur);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(titleLabel);
    layout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    layout->addWidget(durationLabel);
    titleDur->setLayout(layout);
    return titleDur;
}

void AudioPlayer::UpdatePosition(){
    QSettings settings;
    qint64 savedPos = settings.value(m_files[m_currentIndex], 0).toLongLong();
    if(savedPos > 0){
        m_player->setPosition(savedPos);
    }
}

void AudioPlayer::loadFiles(const QStringList &filePaths, QListWidget *list){
    for(const auto &filePath: filePaths){
        m_files.push_back(filePath);
        pos_files.push_back(0);
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
            QString fileDuration = getDurationOfFile(filePath);
            QLabel *fileTitle = new QLabel(fileInfo.baseName());
            QLabel *durationLabel = new QLabel(fileDuration);
            // QListWidgetItem *item = new QListWidgetItem(QString("%1\t%2").arg(fileInfo.baseName()).arg(fileDuration));
            QListWidgetItem *item = new QListWidgetItem();
            item->setData(Qt::UserRole, m_files.size()-filePaths.size()+i);
            list->addItem(item);
            list->setItemWidget(item, getCustomWidget(fileTitle, durationLabel));
        }
    }
}

void AudioPlayer::setCurrentFile(int m_currentIndex){
    // set source and cover art
    m_player->setSource(QUrl::fromLocalFile(m_files[m_currentIndex]));
    getCoverImage(m_files[m_currentIndex].toStdString());
    m_player->play();
}

void AudioPlayer::skip(){
    if(m_files.empty()){
        return;
    }
    m_currentIndex = (m_currentIndex + 1) % m_files.size();
    setCurrentFile(m_currentIndex);

}
void AudioPlayer::playSelected(int index){
    m_currentIndex = index;
    setCurrentFile(index);
    play();

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


void AudioPlayer::deleteFile(QListWidgetItem *item, QListWidget *list){
    int index = item->data(Qt::UserRole).toInt();
    m_files.erase(m_files.begin() + index);
    delete item;

    if(m_files.empty()){
        m_currentIndex = -1;
        m_player->stop();
    } else if (index <= m_currentIndex){
        m_currentIndex = std::max(0, m_currentIndex-1);
        // deleted file was the one playing
        if(index == m_currentIndex+1){
            setCurrentFile(m_currentIndex);
        }
    }

    for(int i = 0; i < list->count(); i++){
        QListWidgetItem *item = list->item(i);
        item->setData(Qt::UserRole, i);
    }


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

QString getSongDurationFromMS(int mslength){
    int seconds = mslength / 1000;
    int hours = (seconds / 3600);
    int minutes = (seconds % 3600) / 60;
    seconds = seconds % 60;
    if(hours > 0){
        return QString("%1:%2:%3")
            .arg(hours, 2, 10, QChar('0'))
        .arg(minutes, 2,10, QChar('0'))
            .arg(seconds,2,10, QChar('0'));

    } else{
        return QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
    }
}

QString AudioPlayer::getDurationOfFile(const QString &path) const {
    TagLib::MPEG::File file(path.toStdString().c_str());
    int duration = file.audioProperties()->lengthInMilliseconds();
    return getSongDurationFromMS(duration);

}

QString AudioPlayer::getFilePath(int index) const{
    return m_files[index];
}

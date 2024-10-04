#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "audioplayer.h"
#include "audiocontrols.h"
#include <QListWidget>
#include <QGridLayout>
#include <QPainter>
#include <QPainterPath>
#include <QSettings>
#include <QIcon>
#include <QDateTime>



// constructor of mainwindow class (called when application starts)
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) // creates new instance of MainWindow class
    , m_audioPlayer(new AudioPlayer(this))
{
    ui->setupUi(this);
    this->setWindowTitle("Podcast Pro");
    this->setFixedSize(QSize(300,550));
    ui->centralwidget->setLayout(new QVBoxLayout);

    // center the widgets in vertical layout
    ui->menubar->setNativeMenuBar(false);
    QAction* uploadFile = new QAction("Upload", this);
    uploadFile->setIcon(QIcon::fromTheme("DocumentNew")); uploadFile->setIconVisibleInMenu(true);
    ui->menubar->insertAction(ui->helpMenu->menuAction(), uploadFile);
    audio_control = new AudioControls(ui->centralwidget);
    audio_control->setEnabled(true);
    //if(!audio_control) return;
    QLayout* centralLayout = ui->centralwidget->layout();
    centralLayout->setContentsMargins(0,0,0,0);
    centralLayout->addWidget(audio_control);
    audio_control->podcastList->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(audio_control->volumeSlider, &QSlider::valueChanged, m_audioPlayer, &AudioPlayer::setVolume);
    connect(audio_control->skipButton, &QPushButton::clicked, m_audioPlayer, &AudioPlayer::skip);
    connect(audio_control->backButton, &QPushButton::clicked, m_audioPlayer, &AudioPlayer::previous);
    connect(uploadFile, &QAction::triggered, this, &MainWindow::onUploadFiles);
    connect(m_audioPlayer, &AudioPlayer::titleChanged, this, &MainWindow::updateTitle);
    connect(m_audioPlayer, &AudioPlayer::artistChanged, this, &MainWindow::updateArtist);
    connect(m_audioPlayer, &AudioPlayer::coverImageChanged, this, &MainWindow::updateCoverArt);
    connect(m_audioPlayer, &AudioPlayer::stateChanged, this, &MainWindow::updatePlayButton);
    connect(m_audioPlayer, &AudioPlayer::positionChanged, this, &MainWindow::updateProgressBarPosition);
    connect(m_audioPlayer, &AudioPlayer::durationChanged, this, &MainWindow::updateProgressBarMaximum);
    connect(audio_control->podcastList, &QListWidget::itemDoubleClicked,this, &MainWindow::itemDoubleClicked);
    connect(audio_control->podcastList, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
    connect(audio_control->playButton, &QPushButton::clicked, this, [&]() {
        if(m_audioPlayer->state()== QMediaPlayer::PlayingState){
            m_audioPlayer->pause();
        }
        else{
            m_audioPlayer->play();
        }
    });
    connect(audio_control->progressBar, &QSlider::sliderMoved, this, &MainWindow::changePlayerPosition);



}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::onUploadFiles(){
    const QString DEFAULT_DIR_KEY("default_dir");
    QSettings MySettings;
    QString filter = "Audio Files (*.mp3 *.wav *.ogg *.flac *.aac)";
    QStringList filePaths = QFileDialog::getOpenFileNames(this, "Select one or more files to open", MySettings.value(DEFAULT_DIR_KEY).toString(), filter);
    if(!filePaths.empty()){
        // set current DIR
        QDir currDir;
        MySettings.setValue(DEFAULT_DIR_KEY,
                            currDir.absoluteFilePath(filePaths.last()));
        // ensure the are audio files
        m_audioPlayer->loadFiles(filePaths, audio_control->podcastList);
    }

}
void MainWindow::updateTitle(const QString &title) {
    audio_control->titleLabel->setText(title);
}
void MainWindow::updateArtist(const QString &artist) {
    audio_control->authorLabel->setText(artist);

}

QPixmap roundCorners(const QImage &source){
    QPixmap target = QPixmap(source.size());
    target.fill(Qt::transparent);
    QPainterPath clipPath;
    clipPath.addRoundedRect(source.rect().adjusted(10, 10, -10, -10), 20, 20);

    QPainter painter (&target);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.setClipPath(clipPath);
    painter.drawImage(0, 0, source);
    return target;
}
void MainWindow::updateCoverArt(const QImage &coverArt) {
    if(coverArt.isNull()){
        audio_control->coverArtLabel->clear();
        return;
    }
    QPixmap final = roundCorners(coverArt);
    int labelWidth = audio_control->coverArtLabel->width(); int labelHeight = audio_control->coverArtLabel->height();
    audio_control->coverArtLabel->setPixmap(final.scaled(labelWidth, labelHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation));

}
void MainWindow::updatePlayButton(QMediaPlayer::PlaybackState state){
    if(state == QMediaPlayer::PlayingState){
        audio_control->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        audio_control->playButton->setText("Pause");
    }
    else{
        audio_control->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        audio_control->playButton->setText("Play");

    }
}

void MainWindow::showContextMenu(const QPoint &pos)
{
    // Handle global position
    QPoint globalPos = audio_control->podcastList->mapToGlobal(pos);

    // Create menu and insert some actions
    QMenu myMenu;
    myMenu.addAction("Delete",  this, SLOT(eraseItem()));

    // Show context menu at handling position
    myMenu.exec(globalPos);
}

void MainWindow::eraseItem()
{
    // If multiple selection is on, we need to erase all selected items
    for (int i = 0; i < audio_control->podcastList->selectedItems().size(); ++i) {
        // Get curent item on selected row
        QListWidgetItem *item = audio_control->podcastList->takeItem(audio_control->podcastList->currentRow());
        // And remove it
        delete item;
    }
}

QString MainWindow::formatTime(qint64 timeInMs) {
    // Convert from ms to seconds
    int totalSeconds = static_cast<int>(timeInMs / 1000);

    int hours = totalSeconds / 3600;
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    // Format as MM:SS
    if(hours > 0){
        return static_cast<QString>(QDateTime::fromSecsSinceEpoch(totalSeconds).toUTC().toString("h:mm:ss"));
    } else{
        return QString("%1:%2").arg(minutes, 2, 10, QLatin1Char('0')).arg(seconds, 2, 10, QLatin1Char('0'));
    }

}
void MainWindow::updatePositionDurationDisplay(qint64 position, qint64 duration) {
    // Convert position and duration to MM:SS format
    QString positionStr = formatTime(position);
    QString durationStr = formatTime(duration);

    // Combine position and duration
    QString display = positionStr + " / " + durationStr;

    // Update the label
    audio_control->durationLabel->setText(display);
}

void MainWindow::itemDoubleClicked(QListWidgetItem* item){
    int index = item->data(Qt::UserRole).toInt();
    m_audioPlayer->playSelected(index);
    m_audioPlayer->play();
}
void MainWindow::addFileToList(const QString &fileName) {
    audio_control->podcastList->addItem(fileName);

}
void MainWindow::changePlayerPosition(int position) {
    m_audioPlayer->setAudioPosition(position);
}

void MainWindow::updateProgressBarPosition(qint64 position) {
    audio_control->progressBar->setValue(static_cast<int>(position));
    updatePositionDurationDisplay(position, m_audioPlayer->getDuration());
}

void MainWindow::updateProgressBarMaximum(qint64 duration) {
    audio_control->progressBar->setMaximum(static_cast<int>(duration));
    updatePositionDurationDisplay(m_audioPlayer->getPosition(), duration);
}


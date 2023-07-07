#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "audioplayer.h"

// constructor of mainwindow class (called when application starts)
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) // creates new instance of MainWindow class
    , m_audioPlayer(new AudioPlayer(this))
{
    ui->setupUi(this);
    this->setWindowTitle("Podcast Pro");

    // center the widgets in vertical layout
    ui->verticalLayout->setAlignment(ui->volumeSlider, Qt::AlignCenter);
    ui->menubar->setNativeMenuBar(false);

    //set up connections
    connect(ui->volumeSlider, &QSlider::valueChanged, m_audioPlayer, &AudioPlayer::setVolume);
    connect(ui->skipButton, &QPushButton::clicked, m_audioPlayer, &AudioPlayer::skip);
    connect(ui->backButton, &QPushButton::clicked, m_audioPlayer, &AudioPlayer::previous);
    connect(ui->uploadFiles, &QAction::triggered, this, &MainWindow::onUploadFiles);
    connect(m_audioPlayer, &AudioPlayer::titleChanged, this, &MainWindow::updateTitle);
    connect(m_audioPlayer, &AudioPlayer::artistChanged, this, &MainWindow::updateArtist);
    connect(m_audioPlayer, &AudioPlayer::coverImageChanged, this, &MainWindow::updateCoverArt);
    connect(m_audioPlayer, &AudioPlayer::stateChanged, this, &MainWindow::updatePlayButton);
    connect(m_audioPlayer, &AudioPlayer::positionChanged, this, &MainWindow::updateProgressBarPosition);
    connect(m_audioPlayer, &AudioPlayer::durationChanged, this, &MainWindow::updateProgressBarMaximum);
    connect(m_audioPlayer, &AudioPlayer::fileLoaded, this, &MainWindow::addFileToList);
    connect(ui->playButton, &QPushButton::clicked, this, [&]() {
        if(m_audioPlayer->state()== QMediaPlayer::PlayingState){
            m_audioPlayer->pause();
        }
        else{
            m_audioPlayer->play();
        }
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::onUploadFiles(){
    QStringList filePaths = QFileDialog::getOpenFileNames(this, "Select one or more files to open");
    m_audioPlayer->loadFiles(filePaths);
}
void MainWindow::updateTitle(const QString &title) {
    ui->titleLabel->setText(title);
}
void MainWindow::updateArtist(const QString &artist) {
    ui->authorLabel->setText(artist);

}
void MainWindow::updateCoverArt(const QImage &coverArt) {
    qDebug() << "updateCoverArt called, Image dimensions: " << coverArt.width() << "x" << coverArt.height();
    QPixmap pixmap = QPixmap::fromImage(coverArt);
    ui->coverArtLabel->setPixmap(pixmap);

}
void MainWindow::updatePlayButton(QMediaPlayer::PlaybackState state){
    if(state == QMediaPlayer::PlayingState){
        ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        ui->playButton->setText("Pause");
    }
    else{
        ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        ui->playButton->setText("Play");

    }
}
void MainWindow::addFileToList(const QString &fileName) {
    ui->podcastList->addItem(fileName);
}

void MainWindow::updateProgressBarPosition(qint64 position) {
    ui->progressBar->setValue(static_cast<int>(position));
}

void MainWindow::updateProgressBarMaximum(qint64 duration) {
    ui->progressBar->setMaximum(static_cast<int>(duration));
}


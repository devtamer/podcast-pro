#ifndef AUDIOCONTROLS_H
#define AUDIOCONTROLS_H


#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <QHBoxLayout>
#include <QSlider>
#include <QResizeEvent>

class AudioControls : public QWidget
{
    Q_OBJECT
    void resizeEvent(QResizeEvent* event) override {
        int width = event->size().width();
        int coverWidth = width * .6;
        int coverHeight = coverWidth;
        coverArtLabel->setFixedSize(coverWidth, coverHeight);
    }
public:
    explicit AudioControls(QWidget *parent = nullptr){
        authorLabel = new QLabel("", this);
        durationLabel = new QLabel("", this);

        backButton = new QPushButton("Back", this);
        playButton = new QPushButton("Play", this);
        skipButton = new QPushButton("Skip", this);

        progressBar = new QSlider(Qt::Horizontal, this);
        titleLabel = new QLabel("", this);
        coverArtLabel = new QLabel( this);

        podcastList = new QListWidget(this);

        QLabel* volumeLabel = new QLabel("Volume", this);
        volumeSlider = new QSlider(Qt::Horizontal, this);

        // Create Layouts
        QHBoxLayout* buttonLayout = new QHBoxLayout();  // Horizontal layout for buttons
        buttonLayout->addWidget(backButton);
        buttonLayout->addWidget(playButton);
        buttonLayout->addWidget(skipButton);
        buttonLayout->setContentsMargins(0,0,0,0);

        QVBoxLayout* volumeLayout = new QVBoxLayout();  // Vertical layout for volume controls
        volumeLayout->addWidget(volumeLabel);
        volumeLayout->addWidget(volumeSlider);
        volumeLayout->setContentsMargins(0,0,0,0);

        QHBoxLayout* titleAuthLayout = new QHBoxLayout();
        titleAuthLayout->addWidget(authorLabel);
        titleAuthLayout->addWidget(durationLabel);
        titleAuthLayout->setContentsMargins(20,0,0,0);

        QVBoxLayout* lowerLayout = new QVBoxLayout();
        titleLabel->setContentsMargins(20,0,0,0);
        lowerLayout->addWidget(titleLabel);
        lowerLayout->addLayout(titleAuthLayout);
        lowerLayout->addWidget(progressBar);
        lowerLayout->addLayout(buttonLayout);
        lowerLayout->addLayout(volumeLayout);
        lowerLayout->setContentsMargins(20,0,20,0);
        lowerLayout->setSpacing(2);

        QVBoxLayout* mainLayout = new QVBoxLayout(this);  // Main vertical layout
        mainLayout->setContentsMargins(0,0,0,0);
        mainLayout->addWidget(podcastList, 0, Qt::AlignTop);
        mainLayout->addWidget(coverArtLabel, 0, Qt::AlignCenter);
        mainLayout->addLayout(lowerLayout);

        setLayout(mainLayout);
    }
    QPushButton* backButton;
    QPushButton* playButton;
    QPushButton* skipButton;
    QSlider* progressBar;
    QSlider* volumeSlider;
    QListWidget* podcastList;
    QLabel* titleLabel;
    QLabel* coverArtLabel;
    QLabel* authorLabel;
    QLabel* durationLabel;
    QLabel* volumeLabel;
signals:
};

#endif // AUDIOCONTROLS_H

# Podcast Pro

Podcast Pro is a free and easy-to-use audio player built using Qt C++ and TagLib, designed specifically for podcast enthusiasts who want to store, organize, and listen to their personal collection of podcasts. Whether you've purchased independent podcasts or want a dedicated app for your audio files, Podcast Pro is the ideal solution.

### Features

- **Supports Multiple Audio Formats**: Upload your podcasts in a variety of formats, including `.mp3`, `.wav`, `.ogg`, `.flac`, and `.aac`.
- **Organize Your Podcasts**: Store your collection in one convenient place and organize them to your liking.
- **Resume Playback**: Podcast Pro will remember where you left off, so you can easily continue listening from where you stopped.
- **Offline Listening**: Since Podcast Pro is locally hosted, you have access to your podcasts even without an internet connection.
- **Perfect for Custom Content**: Great for podcasts purchased from independent sellers, which can't be uploaded to platforms like Spotify or Apple Music.

### Getting Started
 
 Install the binaries here (coming soon):
 
 - Mac OS X
 - Linux
 - Windows

Follow these steps to build locally:

1. **Clone the repository**:
   ```sh
   git clone https://github.com/yourusername/podcast-pro.git
   ```
2. **Install Dependencies**:
   - Make sure you have [Qt](https://www.qt.io/download) installed.
   - Install [TagLib](https://taglib.org/), used for handling metadata of audio files.
3. **Build the Project**:
   - Use Qt Creator or run the following command:
   ```sh
   qmake && make
   ```
4. **Run Podcast Pro**:
   ```sh
   ./podcast-pro
   ```

### How to Use

1. Launch Podcast Pro.
2. Click the **Upload** button to add your podcast files (`*.mp3`, `*.wav`, `*.ogg`, `*.flac`, `*.aac`).
3. Organize your podcasts by title, author, or tags.
4. Click on a podcast to start listening. The app will remember your playback position for each file.

### Requirements

- Qt 6.6 or later
- TagLib library
- C++17 compiler

### Contributions

If you'd like to contribute, please fork the repository, create a feature branch, and submit a pull request.

### License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.


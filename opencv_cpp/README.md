# UbuntuにOpenCVの導入

2021/6/19

[OpenCV: Installation in Linux](https://docs.opencv.org/4.5.0/d7/d9f/tutorial_linux_install.html)

## 環境

Ubuntu環境での設定方法になります。
[公式サイト](https://docs.opencv.org/master/df/d65/tutorial_table_of_content_introduction.html)にはWindows/Macなどでのセットアップ方法も記載されています。

```bash
# Ubuntu version
$ cat /etc/lsb-release 
DISTRIB_ID=Ubuntu
DISTRIB_RELEASE=18.04
DISTRIB_CODENAME=bionic
DISTRIB_DESCRIPTION="Ubuntu 18.04.5 LTS"
```

## OpenCVのインストール

```bash
# Install preparation
$ sudo apt update
$ sudo apt upgrade
$ mkdir ~/ws/lib/opencv && cd ~/ws/lib/opencv

# Install minimal prerequisites (Ubuntu 18.04 as reference)
sudo apt update && sudo apt install -y cmake g++ wget unzip

# Download and unpack sources (latest version)
wget -O opencv.zip https://github.com/opencv/opencv/archive/master.zip
wget -O opencv_contrib.zip https://github.com/opencv/opencv_contrib/archive/master.zip
unzip opencv.zip
unzip opencv_contrib.zip

# Delete unnecessary zip files
$ rm opencv.zip opencv_contrib.zip

# Create build directory and switch into it
mkdir -p build && cd build

# 画像を表示させるために必要なライブラリをインストール(Ubuntuの場合)
sudo apt install libgtk2.0-dev pkg-config

# Configure（Ubuntuの場合：画像表示のため WITH_GTK=ON を指定）
cmake -D WITH_GTK=ON -D OPENCV_EXTRA_MODULES_PATH=../opencv_contrib-master/modules ../opencv-master

# Build
cmake --build .

# Install
sudo make install
```

インストール先

```
/usr/local/bin - executable files
/usr/local/lib - libraries (.so)
/usr/local/cmake/opencv4 - cmake package
/usr/local/include/opencv4 - headers
/usr/local/share/opencv4 - other files (e.g. trained cascades in XML format)
```

CMakeで生成したファイルの一括削除ができるようにエイリアスを作成

```bash
$ vim ~/.bashrc
    #↓以下の内容を書き込む
    # CMake : delete files that created by cmake
    alias cmakeclean='rm CMakeCache.txt cmake_install.cmake && rm -r CMakeFiles && rm Makefile'

# Reflect the configration
$ source ~/.bashrc
```

## サンプル実行

Sample Code

```cpp
include <iostream>
#include <opencv2/opencv.hpp>

int main(){
  cv::Mat image(256, 256, CV_8UC3);

  cv::String text = "Hello OpenCV!";
  cv::putText(image, text, cv::Point(0,100), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0,255, 127));

  cv::namedWindow("Image", cv::WINDOW_AUTOSIZE);
  cv::imshow("Image", image);
  cv::waitKey(0);

  return 0;
}
```

CMakeList

```cmake
cmake_minimum_required(VERSION 2.8)
project( Sample01DisplayImage )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( sample01 sample01.cpp )
target_link_libraries( sample01 ${OpenCV_LIBS} )
```

ビルドし実行

```bash
$ cmake .
$ make
$ ./sample01
```

以下のような画像が出力されれば成功です。
![sample01-image](./sample01_DisplayImage/sample01.png)

## Sample02 : GStreamerを利用したWindow Capture

GStreamerのインストール

[Installing on Linux](https://gstreamer.freedesktop.org/documentation/installing/on-linux.html?gi-language=c)
[Gstreamer ＋ OpenCVの環境構築 - 四畳半テクノポリス](https://toriten1024.hatenablog.com/entry/2018/09/29/012205)

```bash
# Ubuntu18.04
$ sudo apt install libgstreamer1.0-0 gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav gstreamer1.0-doc gstreamer1.0-tools gstreamer1.0-x gstreamer1.0-alsa gstreamer1.0-gl gstreamer1.0-gtk3 gstreamer1.0-qt5 gstreamer1.0-pulseaudio

# 公式には表記されていないがこのライブラリも必要
$ sudo apt install libgstreamer-plugins-base1.0-dev 
```

OpenCVの再コンパイル
```bash
# Configure（Ubuntuの場合：画像表示のため WITH_GTK=ON を指定）
cmake -D WITH_GTK=ON -D WITH_GSTREAMER=ON -D WITH_FFMPEG=OFF -D WITH_1394=OFF -D OPENCV_EXTRA_MODULES_PATH=../opencv_contrib-master/modules ../opencv-master

# Build
cmake --build .

# Install
sudo make install
```



VideoCaptureが反応してくれなくてずっと空が出力になっていたのは、OpenCVのコンパイル時に`WITH_GSTREAMER=ON`の設定が必要だった模様。以下が参考になった。

[[Kinesis Video Streams] OpenCVのビデオソースにGStreamerを使用してみました。 | DevelopersIO](https://dev.classmethod.jp/articles/gstreamer-opencv/)


## エラー対処

## OpenCV GTK+ 2.x Error

ubutnu18.04LTS環境で`cv::namedWindow`を利用しようとしたら発生したエラーです。
どうやらGTKの設定が出来ていなかった模様。GTKとはクロスプラットフォームのGUIツールキットで、元々はGIMP(ペイントソフト)の実装のために開発されたものらしい。

※上記の[opencvのインストール](#opencvのインストール)の記載は本エラーに合わせて修正してあります。

```bash
$ ./sample01 
terminate called after throwing an instance of 'cv::Exception'
  what():  OpenCV(4.5.3-pre) /home/fumihachi/ws/lib/opencv/opencv-master/modules/highgui/src/window.cpp:1223: error: (-2:Unspecified error) The function is not implemented. Rebuild the library with Windows, GTK+ 2.x or Cocoa support. If you are on Ubuntu or Debian, install libgtk2.0-dev and pkg-config, then re-run cmake or configure script in function 'cvNamedWindow'

中止 (コアダンプ)
```

書かれている通りに`libgtk2.0-dev`と`pkg-config`をインストールしても解決しない。

```bash
$ sudo apt install libgtk2.0-dev pkg-config
```

こちらのサイト [c++ — OpenCV GTK + 2.xエラー](https://www.it-swarm-ja.com/ja/c%2B%2B/opencv-gtk-2x%E3%82%A8%E3%83%A9%E3%83%BC/1050858617/) が参考になりました。

1. `libgtk2.0-dev`がただしくインストールされているか確認

```bash
$ sudo apt search libgtk2.0-dev
ソート中... 完了
全文検索... 完了  
libgtk2.0-dev/bionic,now 2.24.32-1ubuntu1 amd64 [インストール済み]
  development files for the GTK+ library
```

2. `WITH_GTK=ON`オプションを設定して再度OpenCVをビルド

```bash
$ cd ws/lib/opencv/build
$ cmake -D WITH_GTK=ON -D OPENCV_EXTRA_MODULES_PATH=../opencv_contrib-master/modules ../opencv-master
$ cmake --build . #<--makeでもよい
$ sudo make install
```

## GTK : "canberra-gtk-module"の読み込みエラー

GTK設定をした場合（`WITH_GTK=ON`）、以下のようなエラーが出る場合があります。

```bash
$ ./sample03 
Gtk-Message: 19:03:06.598: Failed to load module "canberra-gtk-module"
```

このときは、`libcanberra-gtk*`ライブラリが足りていないということなので、apt installしてあげれば解決です。

```bash
sudo apt install libcanberra-gtk* -y
```

参考サイト：[OpenCVを実行するとでてくるFailed to load module "canberra-gtk-module"というエラーの対処法 - Qiita](https://qiita.com/igor-bond16/items/d5641e39ad93ad57826e)
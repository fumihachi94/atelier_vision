#include <iostream>
#include <ext/stdio_filebuf.h>
#include <opencv2/opencv.hpp>

/*-------------------------------------------------*/
/* マウスで選択したWindowの「Window ID」を取得する */
/*-------------------------------------------------*/
std::string getWindowid(){
    std::string windowid;

    // 実行したいコマンド
    std::string cmd = "xwininfo |grep '^xwininfo: Window id:' | awk '{print $4}'";
    
    // コマンド実行
    FILE *fp = popen(cmd.c_str(), "r");

    // コマンド出力を取得
    __gnu_cxx::stdio_filebuf<char> *p_fb = new __gnu_cxx::stdio_filebuf<char>(fp, std::ios_base::in);
	std::istream input(static_cast<std::streambuf *>(p_fb));
	getline(input, windowid);

	// 解放
	delete p_fb;
	pclose(fp);

    return windowid;
}


int main(){

    // Get target window id (mouse click) 
    std::cout << "Please select Window (mouse click!)" << std::endl;
    std::string WINDOW_ID = getWindowid();
    std::cout << "window id > " << WINDOW_ID << std::endl;

    // Capture target window (using GStreamer + cv::VideoCapture) 
    cv::Mat frame;
    
    std::string cmd = "ximagesrc xid=" + WINDOW_ID + " ! videoconvert ! appsink";
    cv::VideoCapture cap = cv::VideoCapture(cmd);

    while( cv::waitKey(1) != 27){
        cap.read(frame);
        if(frame.empty()){
            std::cerr << "Error! blank frame captured\n";
            break;
        }
        cv::imshow("capture", frame);
    }



    return 0;
}


// [X Window SystemのウィンドウIDを知るには](https://www.atmarkit.co.jp/flinux/rensai/linuxtips/284windowid.html)
// [C++で外部コマンド実行結果をストリームとして使う方法 - 個人的なまとめ。](https://shinji611.hatenablog.com/entry/2018/12/05/091548)
// [popenでコマンドの出力を読み込む - C言語入門](https://kaworu.jpn.org/c/popen%E3%81%A7%E3%82%B3%E3%83%9E%E3%83%B3%E3%83%89%E3%81%AE%E5%87%BA%E5%8A%9B%E3%82%92%E8%AA%AD%E3%81%BF%E8%BE%BC%E3%82%80)














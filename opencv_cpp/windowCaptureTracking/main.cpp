#include <iostream>
#include <ext/stdio_filebuf.h>
#include <opencv2/opencv.hpp>

cv::Mat frame, frame_rect, frame_roi;
bool draw_flag = false;
int x_st = 0, y_st = 0;

void mouseCallback(int event, int x, int y, int flags, void *userdata){
    if(event == cv::EVENT_LBUTTONDOWN){
        std::cout << "Let button down : x=" << x << ", y=" << y << std::endl;
        frame_rect = frame.clone();
        x_st = x;
        y_st = y;
        draw_flag = true;
    }else if(event == cv::EVENT_LBUTTONUP){
        std::cout << "Let button up   : x=" << x << ", y=" << y << std::endl;
        draw_flag = false;
        cv::Rect roi(cv::Point(x_st, y_st), cv::Size(x-x_st, y-y_st));
        frame_roi = frame(roi);
        cv::putText(frame_rect, "Press 'Enter' to decide", cv::Point(7,frame_rect.size().height-30), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,255, 127));
    }else if(event == cv::EVENT_MOUSEMOVE){
        if(draw_flag) {
            frame_rect = frame.clone();
            cv::rectangle(frame_rect, cv::Point(x_st, y_st), cv::Point(x,y), cv::Scalar(0,165,255),1);
        }
    }
}

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

    cv::String window_name = "frame";
    double prop_val;

    // Get target window id (mouse click) 
    std::cout << "Please select Window (mouse click!)" << std::endl;
    std::string WINDOW_ID = getWindowid();
    std::cout << "window id > " << WINDOW_ID << std::endl;

    // Capture target window (using GStreamer + cv::VideoCapture)     
    std::string cmd = "ximagesrc xid=" + WINDOW_ID + " ! videoconvert ! appsink";
    cv::VideoCapture cap = cv::VideoCapture(cmd);

    cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);
    cv::setMouseCallback(window_name, mouseCallback);

    cap.read(frame);
    if(frame.empty()){
        std::cerr << "Error! blank frame captured\n";
        return 1;
    }else{
        frame_rect = frame.clone();
    }

    int k = -1;
    while( k != 27 && k != 13 && prop_val != -1){
        // Closeボタン押したときの戻り値が-1となる
        prop_val = cv::getWindowProperty(window_name, cv::WND_PROP_ASPECT_RATIO);
        cv::imshow(window_name, frame_rect);
        k = cv::waitKey(5);
    }

    if(k != 13) return 1;
    cv::destroyWindow(window_name);

    // テンプレートマッチング
    int method = cv::TM_CCOEFF_NORMED;
    cv::Mat dst;
    cv::Rect roi_rect(0, 0, frame_roi.cols, frame_roi.rows);
    cv::namedWindow("dst", cv::WINDOW_AUTOSIZE);

    while( cv::waitKey(5) != 27 && prop_val != -1 && !frame_roi.empty()){
        cap.read(frame);

        for(int i=0; i<5; i++){
            cv::matchTemplate(frame, frame_roi, dst, method);
            // 最大のスコアの場所を探す
            cv::Point max_pt;
            double maxVal;
            cv::minMaxLoc(dst, NULL, &maxVal, NULL, &max_pt);
            
            // 一定スコア以下の場合は処理終了
            if(maxVal < 1.0) {
                std::cout << "見つけられませんでした" << std::endl;
                break;
            }

            roi_rect.x = max_pt.x;
            roi_rect.y = max_pt.y;
            std::cout << "(" << max_pt.x << ", " << max_pt.y << "), score=" << maxVal << std::endl;
            // 探索結果の場所に矩形を描画
            cv::rectangle(frame, roi_rect, cv::Scalar(0,255,255), 3);

            if(maxVal > 0.9) break;
        }

        // Closeボタン押したときの戻り値が-1となる
        prop_val = cv::getWindowProperty("dst", cv::WND_PROP_ASPECT_RATIO);
        cv::imshow("dst", frame);
    }

    return 0;
}













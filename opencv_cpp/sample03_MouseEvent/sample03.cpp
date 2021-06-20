#include <iostream>
#include <opencv2/opencv.hpp>

cv::Mat image, image_rect;
bool draw_flag = false;
int x_st = 0, y_st = 0;

void mouseCallback(int event, int x, int y, int flags, void *userdata){
    if(event == cv::EVENT_LBUTTONDOWN){
        std::cout << "Let button down : x=" << x << ", y=" << y << std::endl;
        image_rect = image.clone();
        x_st = x;
        y_st = y;
        draw_flag = true;
    }else if(event == cv::EVENT_LBUTTONUP){
        std::cout << "Let button up   : x=" << x << ", y=" << y << std::endl;
        draw_flag = false;
        cv::putText(image_rect, "Press 'Enter' to decide", cv::Point(7,image_rect.size().height-30), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,255, 127));
    }else if(event == cv::EVENT_MOUSEMOVE){
        if(draw_flag) {
            image_rect = image.clone();
            cv::rectangle(image_rect, cv::Point(x_st, y_st), cv::Point(x,y), cv::Scalar(0,165,255),1);
        }
    }
}

class areaSelect{
public:
    cv::Mat image_;
    areaSelect(cv::Mat image){image_ = image.clone();}

    void showImage(cv::String window_name){
        cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);
        cv::imshow(window_name, image_);
    }

    void dragSelect(cv::String window_name){
        showImage(window_name);
        cv::setMouseCallback(window_name, mouseCallback);
    }
};


int main(){

    image = cv::Mat(512, 512, CV_8UC3);
    cv::String window_name = "Image";

    // areaSelect aslt(image);
    // aslt.dragSelect("Image");

    cv::String text = "Mouse Event Demo";
    cv::putText(image, text, cv::Point(30,30), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0,255, 127));
    
    image_rect = image.clone();
    cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);
    cv::setMouseCallback(window_name, mouseCallback);

    double prop_val;
    while(cv::waitKey(1) != 27 && prop_val != -1){
        // Closeボタン押したときの戻り値が-1となる
        prop_val = cv::getWindowProperty(window_name, cv::WND_PROP_ASPECT_RATIO);
        cv::imshow(window_name, image_rect);
    }
 
    return 0;
}














#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

using namespace std;

int main()
{
    printf("--Iamge convolution test--\n");

    cv::Mat image = cv::imread("img/aloeL.jpg", 1);

    unsigned int h = image.size().height;
    unsigned int w = image.size().width;

    unsigned int window_sz = 3;

    cv::resize(image, image, cv::Size(int(h*0.5), int(w*0.5)));

    h = image.size().height;
    w = image.size().width;

    cout << "H x W : " << h << " x " << w << endl;


    unsigned int dst_h = h/window_sz;
    unsigned int dst_w = w/window_sz;

    // cout << image.at<cv::Vec3b>(0,0) << endl;

    // cv::Mat kernel = cv::Mat::ones(window_sz, window_sz, CV_32F)/16;

    // cv::Mat kernel = (cv::Mat_<float>(3,3) << 1, 2, 1, 2, 4, 2, 1, 2, 1)/16.0f;
    
    cv::Mat kernel = (cv::Mat_<float>(3,3) << 1, 0, -1, 0, 0, 0, -1, 0, 1);

    cout << kernel << endl;

    cv::Mat dst = cv::Mat::zeros(h,w, CV_8UC1);

    cv::Mat gray = cv::Mat::zeros(h,w, CV_8UC1);
    cv::cvtColor(image, gray, CV_BGR2GRAY);

    cv::filter2D(gray, dst, 8, kernel);

    cout << "H x W : " << dst.size().height << " x " << dst.size().width << endl;

    // cv::Mat dst = cv::Mat::zeros(dst_h,dst_w, CV_8UC1);

    for(int y=0; y<dst_h; y+=window_sz){
        for(int x=0; x<dst_w; x+=window_sz){
            // cv::Mat p = cv::Vec3d(image.at<cv::Vec3b>(y, x));
            // dst.at<uchar>(y,x) = int((a*p[0]+b*p[1]+c*p[2])/(a+b+c));
        }
    }


    cv::imshow("dst image", dst);

    // string savename = "img/dst_";
    // ostringstream ss;
    // ss << int(a*100) << "b" << int(b*100) << "g" << int(c*100) << "r.png";
    // savename = savename + ss.str();

    // cout << savename << endl;

    // cv::imwrite(savename, dst);

    cv::waitKey(0);
    return 0;
}
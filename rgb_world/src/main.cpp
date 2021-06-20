
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main()
{
    printf("--rgb world--\n");

    cv::Mat image = cv::imread("img/aloeL.jpg", 1);

    unsigned int h = image.size().height;
    unsigned int w = image.size().width;

    cv::resize(image, image, cv::Size(int(h*0.5), int(w*0.5)));

    h = image.size().height;
    w = image.size().width;

    cout << "H x W : " << h << " x " << w << endl;

    cout << image.at<cv::Vec3b>(0,0) << endl;

    cv::Mat dst = cv::Mat::zeros(h,w, CV_8UC1);
    double a = 0.0;
    double b = 0.0;
    double c = 1.0;
    for(int y=0; y<h; y++){
        for(int x=0; x<w; x++){
            cv::Vec3d p = cv::Vec3d(image.at<cv::Vec3b>(y, x));
            dst.at<uchar>(y,x) = int((a*p[0]+b*p[1]+c*p[2])/(a+b+c));
            // if ((x+y)%500==1){
            //     cout << p << endl;
            // }
        }
    }


    cv::imshow("dst image", dst);

    string savename = "img/dst_";
    ostringstream ss;
    ss << int(a*100) << "b" << int(b*100) << "g" << int(c*100) << "r.png";
    savename = savename + ss.str();

    cout << savename << endl;

    cv::imwrite(savename, dst);

    cv::waitKey(0);
    return 0;
}
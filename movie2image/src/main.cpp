
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
typedef unsigned int uint;

int movie2images(string movie_path, int save=0, string save_path="./dst", uint start_frame=0, uint end_frame=0, uint step=1)
{
    int ext_num = movie_path.find_last_of(".");
    string extention = movie_path.substr(ext_num, movie_path.size()-ext_num+1);
    if(!extention.compare("mp4")) {
        cout << extention << endl;
        cout << "File extention error: Please select .mp4 movie file path." << endl;
        return 1;
    }

    cv::VideoCapture movie(movie_path);
    if(!movie.isOpened()) {
        cout << "File open error: Can't open movie file." << endl;
        return 1;
    }
    
    uint frame_count = movie.get(cv::CAP_PROP_FRAME_COUNT);
    uint fps = movie.get(cv::CAP_PROP_FPS);
    if(end_frame == 0 || end_frame > frame_count)
        end_frame = frame_count;

    cout << end_frame << endl;
    cout << fps << endl;

    int num = 0;
    cv::Mat frame;
    string save_file_name = save_path + "/img_";
    for(int n=start_frame; n<end_frame; n+=step){
        movie.set(cv::CAP_PROP_POS_FRAMES, n);
        movie >> frame;

        ostringstream oss;
        oss << setfill('0') << setw(6) << num++;
        if(save) cv::imwrite(save_path + "/img_" + oss.str() + ".png", frame);

        cv::imshow("dst image", frame);
        if(cv::waitKey(1)==27) break;

        cout << "frame: #" << n << endl;
    }
    cout << endl;

    return 0;
}


int main()
{
    printf("--Movie to Images--\n");

    movie2images("movie/tomato_youtube.mp4", 1, "./dst", 20000, 20450, 5);

    // cv::VideoCapture movie("movie/tomato_youtube.mp4");

    // int n = 0;
    // vector<cv::Mat> frames;
    // while(movie.isOpened()){
    //     cv::Mat tmp;
    //     movie >> tmp;
    //     // frames.push_back(tmp);
    //     cv::imshow("dst image", tmp);
    //     if(cv::waitKey(1)==27) break;
    //     cout << "\r" << "frame: #" << n++ << string(20, ' ');
    // }
    // cout << endl;

    // cv::Mat frame;
    // movie >> frame;

    // cv::imshow("dst image", frame);
    
    // unsigned int h = image.size().height;
    // unsigned int w = image.size().width;

    // unsigned int window_sz = 3;

    // cv::resize(image, image, cv::Size(int(h*0.5), int(w*0.5)));

    // h = image.size().height;
    // w = image.size().width;

    // cout << "H x W : " << h << " x " << w << endl;


    // unsigned int dst_h = h/window_sz;
    // unsigned int dst_w = w/window_sz;
    
    // cv::Mat kernel = (cv::Mat_<float>(3,3) << 1, 0, -1, 0, 0, 0, -1, 0, 1);

    // cout << kernel << endl;

    // cv::Mat dst = cv::Mat::zeros(h,w, CV_8UC1);

    // cv::Mat gray = cv::Mat::zeros(h,w, CV_8UC1);
    // cv::cvtColor(image, gray, CV_BGR2GRAY);

    // cv::filter2D(gray, dst, 8, kernel);

    // cout << "H x W : " << dst.size().height << " x " << dst.size().width << endl;

    // // cv::Mat dst = cv::Mat::zeros(dst_h,dst_w, CV_8UC1);

    // for(int y=0; y<dst_h; y+=window_sz){
    //     for(int x=0; x<dst_w; x+=window_sz){
    //         // cv::Mat p = cv::Vec3d(image.at<cv::Vec3b>(y, x));
    //         // dst.at<uchar>(y,x) = int((a*p[0]+b*p[1]+c*p[2])/(a+b+c));
    //     }
    // }


    // cv::imshow("dst image", dst);

    // string savename = "img/dst_";
    // ostringstream ss;
    // ss << int(a*100) << "b" << int(b*100) << "g" << int(c*100) << "r.png";
    // savename = savename + ss.str();

    // cout << savename << endl;

    // cv::imwrite(savename, dst);

    cv::waitKey(0);
    return 0;
}

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

    // cout << end_frame << endl;
    // cout << fps << endl;

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

    return 0;
}
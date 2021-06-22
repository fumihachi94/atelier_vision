#include <iostream>
#include <opencv2/opencv.hpp>


int main(){
  cv::Mat image(256, 256, CV_8UC3);

  cv::String text = "Hello OpenCV!";
  cv::putText(image, text, cv::Point(0,100), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0,255, 127));

  // cv::imwrite("sample01.png", image);
  cv::namedWindow("Image", cv::WINDOW_AUTOSIZE);
  cv::imshow("Image", image);
  cv::waitKey(0);

  return 0;
}
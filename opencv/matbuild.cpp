#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;

int main(){
    cv::Mat Me = cv::Mat::eye(4, 4, CV_64F);
    cout << "Me = " << Me << endl;
    cv::Mat Mo = cv::Mat::ones(4, 4, CV_64F);
    cout << "Mo = " << Mo << endl;
    cv::Mat Mz = cv::Mat::zeros(4, 4, CV_64F);
    cout << "Mz = " << Mz << endl;
    cv::Mat m1;
    cv::multiply(Me, Mo, m1);
    cout << "m1 = " << m1 << endl;
    return 0;
}

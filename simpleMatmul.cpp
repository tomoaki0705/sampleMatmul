#include <iostream>
#include <opencv2/opencv.hpp>

cv::String keys = 
    "{size s|1024|size of matrix}"
    "{help h|false|help message}"
    "{@input||\"gpu\" or other}";

int main(int argc, char**argv)
{
    cv::CommandLineParser parser(argc, argv, keys);
    if(parser.get<bool>("help"))
    {
        parser.printMessage();
        return 0;
    }
    int size = parser.get<int>("size");
    cv::Mat mat1(size, size, CV_32FC1);
    cv::Mat mat2(size, size, CV_32FC1);
    cv::RNG rng(0x7777777);
    rng.fill(mat1, cv::RNG::NORMAL, CV_32FC1, 10.0, 5.0);
    rng.fill(mat2, cv::RNG::NORMAL, CV_32FC1, 10.0, 5.0);
    int64 a = cv::getTickCount();
    cv::Mat result = mat1 * mat2;
    int64 b = cv::getTickCount();
    std::cout << (b - a) / cv::getTickFrequency() << std::endl;

    return 0;
}


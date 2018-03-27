#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char**argv)
{
    cv::CommandLineParser parser(argc, argv, "{size s|1024|size of matrix}{@input||\"gpu\" or other}");
    parser.printMessage();
    return 0;
}


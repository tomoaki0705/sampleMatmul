#include <iostream>
#include <opencv2/opencv.hpp>

cv::String keys = 
    "{size s|1024|size of matrix}"
    "{help h|false|help message}"
    "{@input||\"gpu\" or other}";
const unsigned int initialSeed = 0x7777777;

int64 processMatrix(int size)
{
    using namespace cv;
    Mat mat1(size, size, CV_32FC1);
    Mat mat2(size, size, CV_32FC1);
    RNG rng(initialSeed);
    rng.fill(mat1, RNG::NORMAL, CV_32FC1, 10.0, 5.0);
    rng.fill(mat2, RNG::NORMAL, CV_32FC1, 10.0, 5.0);
    int64 start = getTickCount();
    Mat result = mat1 * mat2;
    int64 stop = getTickCount();
    return stop - start;
}

int main(int argc, char**argv)
{
    cv::CommandLineParser parser(argc, argv, keys);
    if(parser.get<bool>("help"))
    {
        parser.printMessage();
        return 0;
    }
    int size = parser.get<int>("size");
    int64 duration = processMatrix(size);
    std::cout << size << '\t' << duration/cv::getTickFrequency() << 's' << std::endl;

    return 0;
}


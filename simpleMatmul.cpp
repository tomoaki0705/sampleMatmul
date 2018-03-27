#include <iostream>
#include <vector>
#include <numeric>
#include <opencv2/opencv.hpp>

cv::String keys = 
    "{size s|1024|max size of matrix}"
    "{help h|false|help message}"
    "{@input||\"gpu\" or other}"
    "{iteration n|10|number of iteration}";
const unsigned int initialSeed = 0x7777777;

void processMatrix(int size, bool useGpu, int64& duration0, int64& duration1)
{
    using namespace cv;
    if(useGpu)
    {
        Mat mat1(size, size, CV_32FC1);
        Mat mat2(size, size, CV_32FC1);
        UMat umat1, umat2;
        RNG rng(initialSeed);
        rng.fill(mat1, RNG::NORMAL, CV_32FC1, 10.0, 5.0);
        rng.fill(mat2, RNG::NORMAL, CV_32FC1, 10.0, 5.0);
        int64 start0 = getTickCount();
        mat1.copyTo(umat1);
        mat2.copyTo(umat2);
        int64 start = getTickCount();
        UMat result;
        gemm(umat1, umat2, 1, noArray(), 0, result);
        int64 stop = getTickCount();
        duration0 = start - start0;
        duration1 = stop - start;
    }
    else
    {
        Mat mat1(size, size, CV_32FC1);
        Mat mat2(size, size, CV_32FC1);
        RNG rng(initialSeed);
        rng.fill(mat1, RNG::NORMAL, CV_32FC1, 10.0, 5.0);
        rng.fill(mat2, RNG::NORMAL, CV_32FC1, 10.0, 5.0);
        int64 start = getTickCount();
        Mat result = mat1 * mat2;
        int64 stop = getTickCount();
        duration0 = 0;
        duration1 = stop - start;
    }
}

void computeMeasurement(std::vector<int64>& result, double& min, double& max, double& average, double& median, double& initial)
{
    int64 stub;
    initial = result[0]/cv::getTickCount();
    stub = (int64)*std::min_element(result.begin(), result.end());min = stub/cv::getTickFrequency();
    stub = (int64)*std::max_element(result.begin(), result.end());max = stub/cv::getTickFrequency();
    average = (double)(std::accumulate(result.begin(), result.end(), (int64)0))/result.size()/cv::getTickFrequency();
    std::sort(result.begin(), result.end());
    median = (double)result[result.size()/2]/cv::getTickFrequency();
}

void doMeasurement(int size, int iteration, bool useGpu)
{
    std::vector<int64> result0, result1;
    for(auto i = 0;i < iteration;i++)
    {
        int64 duration0, duration1;
        processMatrix(size, useGpu, duration0, duration1);
        result0.push_back(duration0);
        result1.push_back(duration1);
    }
    double min, max, average, median, initial;
    computeMeasurement(result0, min, max, average, median, initial);
    std::cout << size << '\t' << median << '\t';
    computeMeasurement(result1, min, max, average, median, initial);
    std::cout << median << std::endl;
}

int main(int argc, char**argv)
{
    cv::CommandLineParser parser(argc, argv, keys);
    if(parser.get<bool>("help"))
    {
        parser.printMessage();
        return 0;
    }
    int size = 4;
    for( ;size <= parser.get<int>("size");size *= 2)
    {
        doMeasurement(size, parser.get<int>("iteration"), parser.get<cv::String>("@input").compare("gpu") == 0);
    }

    return 0;
}


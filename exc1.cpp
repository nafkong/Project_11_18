#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    Mat srcMat = imread("ͼƬ1.png", 1);
    imshow("Source Image", srcMat);
    Mat image,labels,stats,centroids, grayMat;
    cvtColor(srcMat, grayMat, COLOR_BGR2GRAY);
    threshold(grayMat, image, 110, 255, THRESH_BINARY_INV);
 //   imshow("threshold", image);

    int number = 0;
    int num = connectedComponentsWithStats(image, labels, stats, centroids, 8, CV_16U);
    for (int i = 1; i < num; i++)
    {
        if ((stats.at<int>(i, 2) - stats.at<int>(i, 3) < 20) | (stats.at<int>(i, 2) - stats.at<int>(i, 3) > -20))
            if((stats.at<int>(i, 4) > 500)& (stats.at<int>(i, 4) < 10000))
            {
            Rect rect;
            rect.x = stats.at<int>(i, 0);
            rect.y = stats.at<int>(i, 1);
            rect.width = stats.at<int>(i, 2);
            rect.height = stats.at<int>(i, 3);
            rectangle(srcMat, rect, CV_RGB(255, 0, 0), 1, 8, 0);
            }
    }
    imshow("dstMat", srcMat);

    waitKey(0);
}
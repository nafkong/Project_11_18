#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    Mat srcMat = imread("Í¼Æ¬2.jpg", 1);
    Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
    imshow("Source Image", srcMat);
    Mat image, labels, stats, centroids, grayMat;
    cvtColor(srcMat, grayMat, COLOR_BGR2GRAY);
    erode(grayMat, grayMat, element);
    threshold(grayMat, image, 120, 255, THRESH_BINARY);
    imshow("threshold", image);

    int number = 0;
    int num = connectedComponentsWithStats(image, labels, stats, centroids, 8, CV_16U);
    for (int i = 1; i < num; i++)
    {
       if ((stats.at<int>(i, 0)>100) & (stats.at<int>(i, 1) > 100) & (stats.at<int>(i, 0) < 190) & (stats.at<int>(i, 1) < 180) & (stats.at<int>(i, 4) > 20))
       {
            Rect rect;
            rect.x = stats.at<int>(i, 0);
            rect.y = stats.at<int>(i, 1);
            rect.width = stats.at<int>(i, 2);
            rect.height = stats.at<int>(i, 3);
            rectangle(srcMat, rect, CV_RGB(255, 0, 0), 1, 8, 0);
            cout << i << endl;
       }
    }
    imshow("Á¬Í¨Óò", srcMat);
    waitKey(0);
}
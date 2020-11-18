#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    Mat srcMat = imread("Í¼Æ¬4.jpg", 1);
    imshow("Source Image", srcMat);

    Mat image, labels, stats, centroids, grayMat, hsvMat;

    cvtColor(srcMat, hsvMat, COLOR_BGR2HSV);

    for (int i = 0; i < srcMat.rows; i++) {
        for (int j = 0; j < srcMat.cols; j++) {
            if (((hsvMat.at<Vec3b>(i, j)[0] >= 0 && hsvMat.at<Vec3b>(i, j)[0] <= 10) 
                || (hsvMat.at<Vec3b>(i, j)[0] >= 156 && hsvMat.at<Vec3b>(i, j)[0] <= 180))
                && (hsvMat.at<Vec3b>(i, j)[1] >= 43 && hsvMat.at<Vec3b>(i, j)[1] <= 255)
                && (hsvMat.at<Vec3b>(i, j)[2] >= 46 && hsvMat.at<Vec3b>(i, j)[2] <= 255)) {

                hsvMat.at<Vec3b>(i, j)[0] = 0;
                hsvMat.at<Vec3b>(i, j)[1] = 0;
                hsvMat.at<Vec3b>(i, j)[2] = 0;

            }
        }
    }
//    imshow("hsv", hsvMat);
    cvtColor(hsvMat, hsvMat, COLOR_HSV2BGR);
//    imshow("BGR", hsvMat);
    threshold(hsvMat, image, 0, 255, THRESH_BINARY_INV);
//    imshow("threshold", image);
    cvtColor(image, image, COLOR_BGR2GRAY);
    Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
    erode(image, image, element);
//    imshow("threshold_BGR", image);
    int number = 0;
    int num = connectedComponentsWithStats(image, labels, stats, centroids, 8, CV_16U);
    for (int i = 1; i < num; i++)
    {
        if (stats.at<int>(i, 4) > 10000) {
        Rect rect;
        rect.x = stats.at<int>(i, 0);
        rect.y = stats.at<int>(i, 1);
        rect.width = stats.at<int>(i, 2);
        rect.height = stats.at<int>(i, 3);
        rectangle(srcMat, rect, CV_RGB(255, 0, 0), 1, 8, 0);
        cout << i << endl;
        cout << stats.at<int>(i, 4) << endl;
        }
    }
    imshow("Á¬Í¨Óò", srcMat);
    waitKey(0);
}
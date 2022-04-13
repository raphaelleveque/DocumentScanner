#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

Mat preProcessing(Mat originalImg) {
    Mat grayImg, blurImg, cannyImg;
    cvtColor(originalImg, grayImg, COLOR_BGR2GRAY);
    GaussianBlur(grayImg, blurImg, Size(3, 3), 3, 0);
    Canny(blurImg, cannyImg, 25, 75);
    
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    Mat dilateImg;
    dilate(cannyImg, dilateImg, kernel);
    return dilateImg;
}

void getContours() {
    
    
}



int main() {
    string path = "Resources/paper.jpg";
    Mat originalImg = imread(path);
    
    //resize(imgOriginal, imgOriginal, Size(), 0.5, 0.5);
    
    Mat thresholdImg = preProcessing(originalImg);
    imshow("Image Dilation", thresholdImg);
    imshow("Image", originalImg);
    waitKey(0);
    
    
    
    return 0;
}

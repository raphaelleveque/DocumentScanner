#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

// In order to preprocess the image, we must convert it to a Canny image
// We also need to dilate the image, in order to make the contours more visible
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

// This function receives the already preprocessed image
// This will get all contours points, or vertices, and will calculate the object's area with it
// The function returns the points with the maximum area, wich must be the document
vector<Point> getContours(Mat thresholdImg) {
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(thresholdImg, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    
    vector<vector<Point>> contourCount(contours.size());
    vector<Rect> boundRect(contours.size());
    vector<Point> biggest;
    
    int maxArea = 0, area;
    for (int i = 0; i < contours.size(); i++) {
        area = contourArea(contours[i]);
        string objectType;
        if (area > 1000) {
            double perimeter = arcLength(contours[i], true);
            approxPolyDP(contours[i], contourCount[i], 0.02 * perimeter, true);
            
            if (area > maxArea && contourCount[i].size() == 4) {
                biggest = {contourCount[i][0], contourCount[i][1],
                           contourCount[i][2], contourCount[i][3] };
                maxArea = area;
            }
            drawContours(thresholdImg, contourCount, i, Scalar(255, 0, 255), 2);
        }
        
    }
    return biggest;
}


// This function draw the contours inside the original image
void drawPoints (Mat &originalImg, vector<Point> points, Scalar color) {
    for (int i = 0; i < points.size(); i++) {
        circle(originalImg, points[i], 35, color, FILLED);
        putText(originalImg, to_string(i), points[i], FONT_HERSHEY_PLAIN, 10, color, 5);
    }
}



int main() {
    string path = "/Users/raphaelleveque/Desktop/cs/OpenCV/OpenCV/images/original_image.jpeg";
    Mat originalImg = imread(path);

    Mat thresholdImg = preProcessing(originalImg);
    vector<Point> initialPoints = getContours(thresholdImg);
    drawPoints(originalImg, initialPoints, Scalar(255, 255, 0));
    imshow("Image Dilation", thresholdImg);
    imshow("Image", originalImg);
    waitKey(0);

    
    
    return 0;
}

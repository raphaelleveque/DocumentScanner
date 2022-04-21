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


// The README.me image, contours, showed the contours position, which was 0-3-1-2
// We want to reorder it to make it 0-1-2-3
// To do that, we add the coordinates, the highest is the (0,0), and the lowest will be the origin's oposite
vector<Point> reorder(vector<Point> points) {
    vector<Point> newPoints;
    vector<int> summedPoints, subtractedPoints;
    
    for (int i = 0; i < 4; i++) {
        summedPoints.push_back(points[i].x + points[i].y);
        subtractedPoints.push_back(points[i].x - points[i].y);
    }
    
    Point firstPoint = points[min_element(summedPoints.begin(), summedPoints.end()) -           summedPoints.begin()];
    Point secondPoint = points[max_element(subtractedPoints.begin(), subtractedPoints.end()) -           subtractedPoints.begin()];
    Point thirdPoint = points[min_element(subtractedPoints.begin(), subtractedPoints.end()) -           subtractedPoints.begin()];
    Point lastPoint = points[max_element(summedPoints.begin(), summedPoints.end()) -           summedPoints.begin()];
    
    newPoints.push_back(firstPoint);
    newPoints.push_back(secondPoint);
    newPoints.push_back(thirdPoint);
    newPoints.push_back(lastPoint);
    
    return newPoints;
}

// This function get all contours and applies a perspective transformation to the image
// It takes the source points and transform them as if the coordinates are (0,0) to (width, height),
// ignoring if the original image is distorted
void getWarp(Mat img, Mat &warpImg, vector<Point> points, const float width, const float height) {
    Point2f source[4] = {points[0], points[1], points[2], points[3]};
    Point2f destination[4] = { {0, 0}, {width, 0}, {0, height}, {width, height} };
    
    Mat matrix = getPerspectiveTransform(source, destination);
    warpPerspective(img, warpImg, matrix, Point(width, height));
}


int main() {
    // Reading Image
    // type your path:
    string path = NULL;
    Mat originalImg = imread(path);

    // Preprocessing image
    Mat thresholdImg = preProcessing(originalImg);
    
    // Getting contours and drawing them
    vector<Point> initialPoints = getContours(thresholdImg);
    vector<Point> finalPoints = reorder(initialPoints);
    //drawPoints(originalImg, finalPoints, Scalar(0, 255, 255));
    
    // Warp
    const float width = 420, height = 596;  // A4 paper
    Mat warpImg;
    getWarp(originalImg, warpImg, finalPoints, width, height);

    imshow("Image Dilation", thresholdImg);
    imshow("Image", originalImg);
    imshow("Final Result", warpImg);
    waitKey(0);

    
    
    return 0;
}

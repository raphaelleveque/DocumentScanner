// Warp Perspective
#include "C5.hpp"

void denotatingPointsInImage(Mat img, Point2f sourcePoints[4]);

void warpingMethod(Mat img) {
    
    // I need to know the pixel coordinates of the document's edges
    // The pixel coornidates are floating points
    Point2f sourcePoins[4] = {{529,142}, {771, 190}, {405, 395}, {674, 457}};
    
    // width and height of the card
    // 2.5 x 3.5 inches
    // Keep the same aspect ratio
    float w = 250, h = 350;
    Point2f destinationPoints[4] = {{0,0}, {w, 0}, {0, h}, {w, h}};

    Mat matrix, imgWarp;
    
    // Input the source Points (actual pixel coordinates) and teh destination points
    // (the points we want to transform it) and save it to the Mat matrix
    matrix = getPerspectiveTransform(sourcePoins, destinationPoints);
    
    // That will take the image, take the transformed matrix, and the image's size, and will save it to imgWarp
    warpPerspective(img, imgWarp, matrix, Point(w, h));
    denotatingPointsInImage(img, sourcePoins);
    
    imshow("Image Warp", imgWarp);
}

void denotatingPointsInImage(Mat img, Point2f sourcePoints[4]) {
    for (int i = 0; i < 4; i++) {
        circle(img, sourcePoints[i], 10, Scalar(0, 0, 255), FILLED);
    }
    imshow("Image", img);
}

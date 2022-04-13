// RESIZE AND CROP

#include "C3.hpp"

// Resizing by value
void resizeBtValue(Mat img) {
    Mat imgResize;
    // Size: 640 x 480 px
    resize(img, imgResize, Size(640, 480));
    imshow("Normal Image", img);
    imshow("Image Resize", imgResize);
}

void resizeByScale(Mat img) {
    Mat imgResize;
    // New size:  0.5x, 0.5y
    resize(img, imgResize, Size(), 0.5, 0.5);
    imshow("Normal Image", img);
    imshow("Image Resize", imgResize);
}

void cropImage(Mat img) {
    Mat imgCrop;
    // Rectangle data type
    // x, y, width, height
    // x and y is where it will start to crop it
    Rect roi(100, 100, 300, 250);
    imgCrop = img(roi);
}

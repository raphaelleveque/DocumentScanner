#include "C6.hpp"


// This function only works if I previously know the color values to search for
void extractColoredElement() {
    string path = "Resources/lambo.png";
    Mat img = imread(path);
    Mat imgHSV, mask;
    
    // We can use HSV to extract a colored object
    // In HSV, it's easier to represent
    cvtColor(img, imgHSV, COLOR_BGR2HSV);
    
    // h = hue; s = saturation; v = value
    // How to find these values?
    int hmin = 0, smin = 110, vmin = 153;
    int hmax = 19, smax = 240, vmax = 255;
    Scalar lower(hmin, smin, vmin);
    Scalar upper(hmax, smax, vmax);
    // inRange function to collect the color
    // inRange(img source, a range of colors to get (lower, upper limit), output image)
    inRange(imgHSV, lower, upper, mask);
    
    imshow("Image HSV", imgHSV);
    imshow("Image Mask", mask);
    imshow("Image", img);
    waitKey(0);
}

void noPreviousCoordinates() {
    string path = "Resources/lambo.png";
    Mat img = imread(path);
    Mat imgHSV, mask;
    cvtColor(img, imgHSV, COLOR_BGR2HSV);
    
    // The maximum value for hue is 179, whereas for the others is 255
    int hmin = 0, smin = 110, vmin = 153;
    int hmax = 19, smax = 240, vmax = 255;
    
    // This creates a new window called Trackbars
    namedWindow("Trackbars", (640, 200));
    
    // This creates a window that allows me to track in real time the Hue
    createTrackbar("Hue min", "Trackbars", &hmin, 179);
    createTrackbar("Hue max", "Trackbars", &hmax, 179);
    createTrackbar("Sat min", "Trackbars", &smin, 255);
    createTrackbar("Sat max", "Trackbars", &smax, 255);
    createTrackbar("Val min", "Trackbars", &vmin, 255);
    createTrackbar("val max", "Trackbars", &vmax, 255);

    
    while (true) {
        Scalar lower(hmin, smin, vmin);
        Scalar upper(hmax, smax, vmax);
        inRange(imgHSV, lower, upper, mask);
        
        imshow("Image HSV", imgHSV);
        imshow("Image Mask", mask);
        imshow("Image", img);
        waitKey(1);
    }
}

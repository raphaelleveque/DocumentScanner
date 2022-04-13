// Drawing shapes and text

#include "C4.hpp"

void drawAndText() {
    // Creating blank image
    // 512 x 512 , CV_8 (8 bits, 256 values), UC (unsigned 0 - 255), 3 (RGB)
    // Scalar is the color in RGB
    Mat img(512, 512, CV_8UC3, Scalar(255, 0, 0));

    // circle(where it will be saved, coordinates of the origin, size, color, thickness)
    // if you want it filled, just change thickness to FILLED
    circle(img, Point(256, 256), 155, Scalar(0, 0, 0), 5);
    
    // Points: upper left corner, lower right corner
    rectangle(img, Point(130, 226), Point(382, 286), Scalar(0, 0, 0), FILLED);
    
    // Creates a line
    line(img, Point(130, 296), Point(382, 296), Scalar(255, 255, 255), 2);
    
    // Put text in image
    // putText(img, text, where it starts, font, font scale, color, thickness)
    putText(img, "OpenCV course", Point(137, 262), FONT_HERSHEY_DUPLEX, 0.8, Scalar(0, 69, 255), 1);
    imshow("Circle", img);
    
    waitKey(0);
    
}

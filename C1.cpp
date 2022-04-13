// import Images, Videos and Webcam

#include "C1.hpp"

void readingImages(){
    string path = "Resources/test.png";

    // Mat is a Matrix datatype to handle images
    Mat img = imread(path);
    imshow("Image", img);
    waitKey(0);
}



void readingVideos(){
    string path = "Resources/test_video.mp4";
    VideoCapture cap(path);
    Mat img;
    
    while(true) {
        cap.read(img);
        imshow("Image", img);
        waitKey(1);
    }
}



void WebCam() {
    VideoCapture cap(0);
    Mat img;
    
    while(true) {
        cap.read(img);
        imshow("Image", img);
        waitKey(1);
    }
}

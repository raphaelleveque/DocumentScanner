// BASIC FUNCTIONS

#include "C2.hpp"

Mat readImage() {
    string path = "Resources/test.png";
    Mat img = imread(path);
    imshow("Image", img);
    return img;
}


Mat grayScale(Mat img) {
    Mat imgGray;
    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    imshow("Image Gray", imgGray);
    return imgGray;
}


Mat imageBlur(Mat img) {
    Mat imgBlur;
    // Size(x, x), and x must be odd
    GaussianBlur(img, imgBlur, Size(3, 3), 3, 0);
    imshow("Image Blur", imgBlur);
    return imgBlur;
}

// Canny is not perfect, there are some flaws because the canny line is too thin
// If we dilatate the canny image, we get a better edge detector
Mat imageCanny(Mat img) {
    Mat imgBlur = imageBlur(img);
    Mat imgCanny;
    Canny(imgBlur, imgCanny, 25, 75);
    imshow("Image Canny", imgCanny);
    return imgCanny;
}



// Dilation adds pixels to the boundaries of objects in an image,
// while erosion removes pixels on object boundaries
Mat imageDilatation(Mat img) {
    Mat imgCanny = imageCanny(img);
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    Mat imgDilatation;
    dilate(imgCanny, imgDilatation, kernel);
    imshow("Image Dilatation", imgDilatation);
    return imgDilatation;
} 


Mat imageErosion(Mat img) {
    Mat imgDilatation = imageDilatation(img);
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    Mat imgErosion;
    erode(imgDilatation, imgErosion, kernel);
    imshow("Image Erosion", imgErosion);
    return imgErosion;
}

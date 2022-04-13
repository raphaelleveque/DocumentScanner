// SHAPES AND CONTOUR DETECTION
#include "C7.hpp"

Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;

// getCountours(img to find the contours, img to draw on)
void getContours(Mat imgDil, Mat &img) {
    //findContours(InputArray image, OutputArrayOfArrays contours, OutputArray hierarchy, int mode, int method)
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;   // Vec4i means 4 integer values
    findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    
    // drawContours(img to draw, which contours to draw, how many to draw, what color, thickness)
    // -1 = all contours
    //drawContours(img, contours, -1, Scalar(255, 0, 255), 2);
    
    vector<vector<Point>> conPoly(contours.size());
    vector<Rect> boundRect(contours.size());   // This will store rectangle coordinates
    // In the image, there may be noises, or something other than the shape we want
    // We can remove them
    for (int i = 0; i < contours.size(); i++) {
        double area = contourArea(contours[i]);
        string objectType;
        
        if (area > 1000.0) {
            // Finding the perimeter 2P of the shape
            // The boolean value is to tell whether the shape is closed or not
            double peri = arcLength(contours[i], true);
            // Find how many vertices there are in the shape
            approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
            // In this case, I'm using 'i' because it will draw one shape by one, only if it's above 1000
            drawContours(img, contours, i, Scalar(255, 0, 255), 2);
            
            // boundingRect find the bounding rectangle around the rectangle
            boundRect[i] = boundingRect(conPoly[i]);
            
            // This will draw a rectangle where we found the vertices
            rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(), 5);
            
            // This will tell how many vertices there are in the shape
            int objCor = (int)conPoly[i].size();
            if (objCor == 3)
                objectType = "Triangle";
            else if (objCor == 4) {
                double aspRatio = boundRect[i].width / (double)boundRect[i].height;
                if (aspRatio > 0.98  && aspRatio < 1.02)
                    objectType = "Square";
                else
                    objectType = "Rectangle";
            }
            else if (objCor > 4)
                objectType = "Circle";
            
            putText(img, objectType, { boundRect[i].x, boundRect[i].y - 6}, FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 0), 1);
        }
    }
    
}


void C2Functions(Mat &img) {
    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    GaussianBlur(img, imgBlur, Size(3, 3), 3, 0);
    Canny(imgBlur, imgCanny, 25, 75);
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(imgCanny, imgDil, kernel);
    getContours(imgDil, img);
}

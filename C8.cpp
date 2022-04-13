// FACE DETECTION
#include "C8.hpp"

int main() {
    
    string path = "Resources/test.png";
    Mat img = imread(path);
    
    CascadeClassifier faceCascade;
    faceCascade.load("Resources/haarcascade_frontalface_default.xml");
    cout << "oi" << endl;
    if (faceCascade.empty())
        cout << "XML file not found" << endl;
    
    // To detect faces and store them we need to store the bounding boxes
    vector<Rect> faces;
    faceCascade.detectMultiScale(img, faces, 1.1, 10);
    
    // Iterating to all the faces and draw them one by one
    for (int i = 0; i < faces.size(); i++) {
        cout << "oioi" << endl;
        rectangle(img, faces[i].tl(), faces[i].br(), Scalar(255, 0, 255), 3);
    }
    
    imshow("Image", img);
    waitKey(0);
    
    return 0;
}

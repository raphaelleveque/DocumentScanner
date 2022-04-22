# Document Scanner with OpenCV
This project was created to learn OpenCV in C++

It is divided in two parts: [Learning](https://github.com/raphaelleveque/DocumentScanner/tree/main/Course) and [Practicing](https://github.com/raphaelleveque/DocumentScanner/tree/main/DocumentScanner)


## Learning
The learning section is pretty straightforward, the [Course](https://github.com/raphaelleveque/DocumentScanner/tree/main/Course) repository has lots of functions to manipulate images and webcam, divided into 8 parts


## Practicing
The practicing section has the [Document Scanner Project](https://github.com/raphaelleveque/DocumentScanner/tree/main/DocumentScanner), wich takes a document, crops the image and applies a transformation as if you were seeing it from above.


## How the Document Scanner Works
First, we need to add a path so the program can read an image from the computer. This was my original image: <br/>
![Original Image](https://github.com/raphaelleveque/DocumentScanner/blob/main/images/original_image.jpeg) <br/>

After that, the image will be preprocessed and there will be a Canny Edge Detector image to make it easier to crop later. <br/>
![Canny Image](https://github.com/raphaelleveque/DocumentScanner/blob/main/images/canny_image.png) <br/>

The third step is to get all contours points from the document, and in order to do that, I've implemented a logic to calculate the document's area between four points. <br/>
![Contours](https://github.com/raphaelleveque/DocumentScanner/blob/main/images/contours.png) <br/>
But that wasn't enough because the points' order wasn't good, I needed a different order. <br/>
![Reordering](https://github.com/raphaelleveque/DocumentScanner/blob/main/images/after_reorder.png) <br/>

After that, I just needed to crop the image so I can have a great 2D image from the Document. <br/>
![Final photo](https://github.com/raphaelleveque/DocumentScanner/blob/main/images/final_result.png) <br/>

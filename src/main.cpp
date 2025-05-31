
/** Inspired by OpenCV-Tutorial https://docs.opencv.org/4.x/db/deb/tutorial_display_image.html
 Edited by Merijam Gotzes
 13.03.2024, 12.04.2024
 Praktikum VideoProcessingStartCode
*/

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/features2d.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    const String window;
    //BEGIN: Prepare streaming from internal webcam
    //VideoCapture cap(0);
    //END: Prepare streaming from internal webcam

    //BEGIN: Prepare streaming from a specific video file
    //VideoCapture cap("../videos/Landscape.avi");
    VideoCapture cap("../videos/ColoredBlobs2.wm");
    //END: Prepare streaming from a specific video file

    // Print error message if the video file cannot be opened
    if (!cap.isOpened())
    {
        cout << "The video file or the camera could not be opened." << endl;
        return -1;
    }
    else
    {
        // Obtain fps and frame count by get() method and print
        int fps = (int) cap.get(CAP_PROP_FPS);
        cout << "Frames per second :" << fps << endl;

        // Obtain frame_count using opencv built in frame count reading method
        int frame_count = (int) cap.get(CAP_PROP_FRAME_COUNT);
        cout << "  Frame count :" << frame_count << endl;
    }

    Mat frameMat, grayImage;
    int i = 1;

    while (cap.read(frameMat))
    {
        i++;
        if ((i % 100)==0)
            cout << ".(" << i << ")" ;
        else
            cout << ".";

        Size_<int> kSize = Size_(7,7);
        GaussianBlur(frameMat, frameMat,kSize,0,0);

        cvtColor(frameMat, grayImage, COLOR_BGR2HSV);
        std::vector lower = {35, 25, 0};
        std::vector upper = {95,255,255};
        inRange(grayImage,lower, upper, grayImage);

        medianBlur(grayImage, grayImage,5);
        cvtColor(grayImage,grayImage,COLOR_GRAY2BGR); //Farbraum des zweiten Bildes ist BGR, muss konvertiert werden, wird sonst nicht angezeigt

        Ptr<SimpleBlobDetector> blobDetector = SimpleBlobDetector::create();
        blobDetector->read("C:/Users/User/Desktop/VideoProcessingStartCode/blobdetectorparams1.xml"); //Einlesen der params
        vector <KeyPoint> keypoints; //keypoints, die erkannt/detected werden
        blobDetector->detect(grayImage, keypoints);//Erkennung der Blobs, Punkte in keypoints vermerkt
        for(const KeyPoint& k: keypoints){ //for-each-loop: durch alle keypoints iterieren
            circle(frameMat,k.pt,30, cv::Scalar(0,0,0), 2); //Ein dünner, schwarzer Kreis um alle Keypoints im normalen Bild frameMat
        }


        Mat matResult(Size(frameMat.cols*2,frameMat.rows),frameMat.type(),Scalar::all(0));
        Mat processed = matResult(Rect(0,0,frameMat.cols, frameMat.rows));
        frameMat.copyTo(processed);
        processed = matResult(Rect(frameMat.cols,0,frameMat.cols, frameMat.rows));
        grayImage.copyTo(processed);

        imshow("Ein Farbvideo in ein Grauwertvideo umwandeln.", matResult);
        int key = waitKey(20); // Wait for a keystroke in the window

        // q, ESC, or close window with mouse will terminate the window
        if( key == 'q' || key == 27 || (getWindowProperty("Ein Farbvideo in ein Grauwertvideo umwandeln.", WND_PROP_VISIBLE) < 1) )
        {
            cap.release();
            destroyAllWindows();

            return 0;
        }

    }

    cap.release();
    destroyAllWindows();

    return 0;
}

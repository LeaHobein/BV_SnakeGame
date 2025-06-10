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
#include <windows.h>

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

    Mat frameMat, grayImage, edges;
    int i = 1;

    // Bildschirm Höhe und Breite herausfinden
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    while (cap.read(frameMat))
    {
        i++;
        if ((i % 100)==0)
            cout << ".(" << i << ")" ;
        else
            cout << ".";

        // Kopie erstellen für edge detection
        Mat frameCopy = frameMat.clone();
        
        // Blob detection pipeline
        cvtColor(frameMat, grayImage, COLOR_BGR2HSV);
        std::vector<int> lower = {35, 25, 0};
        std::vector<int> upper = {95, 255, 255};
        inRange(grayImage, lower, upper, grayImage);

        medianBlur(grayImage, grayImage, 5);
        
        // Blob detection auf schwarz-weiß Bild
        Ptr<SimpleBlobDetector> blobDetector = SimpleBlobDetector::create();
        blobDetector->read("..\\blobdetectorparams1.xml");
        vector<KeyPoint> keypoints;
        blobDetector->detect(grayImage, keypoints);
        
        // Kreise malen
        for(const KeyPoint& k: keypoints) {
            circle(frameMat, k.pt, 30, cv::Scalar(0,0,0), 2);
        }

        // Blob detection Ergebnis in RGB konvertieren (für die Darstellung)
        cvtColor(grayImage, grayImage, COLOR_GRAY2BGR);

        // Edge detection pipeline
        cvtColor(frameCopy, edges, COLOR_BGR2GRAY);
        blur(edges, edges, Size(3,3));
        Canny(edges, edges, 50, 150, 3);
        
        // Kopie des originalen Videos erstellen für ganz rechts
        Mat edgesWithBackground = frameCopy.clone();
        // edges in RGB konvertieren (für die Darstellung)
        cvtColor(edges, edges, COLOR_GRAY2BGR);

        Mat edgeMask;
        threshold(edges, edgeMask, 0, 255, THRESH_BINARY);
        // rote linien
        edgesWithBackground.setTo(Scalar(0, 0, 255), edgeMask);

        // Fenstergröße berechnen und Videos in Originalgröße anzeigen
        double scale = 0.8; // Use 80% of screen width
        int targetWidth = screenWidth * scale;
        int targetHeight = (frameMat.rows * targetWidth) / (frameMat.cols * 3);
        
        // sicherstellen, dass die Höhe nicht über den Bildschirmrand hinaus geht
        if (targetHeight > screenHeight * 0.8) {
            targetHeight = screenHeight * 0.8;
            targetWidth = (frameMat.cols * 3 * targetHeight) / frameMat.rows;
        }

        // Fenster erstellen mit den 3 Ergebnissen nebeneinander
        Mat matResult(Size(frameMat.cols * 3, frameMat.rows), frameMat.type(), Scalar::all(0));
        
        // Original mit Kreisen
        frameMat.copyTo(matResult(Rect(0, 0, frameMat.cols, frameMat.rows)));
        // Blob detection Ergebnis
        grayImage.copyTo(matResult(Rect(frameMat.cols, 0, frameMat.cols, frameMat.rows)));
        // Edge detection Ergebnis
        edgesWithBackground.copyTo(matResult(Rect(frameMat.cols * 2, 0, frameMat.cols, frameMat.rows)));

        // Ergebnis resizen damit es auf Bildschirm passt und videos in Orignalgröße angezeigt werden
        Mat resizedResult;
        resize(matResult, resizedResult, Size(targetWidth, targetHeight));

        imshow("Ein Farbvideo in ein Grauwertvideo umwandeln.", resizedResult);
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

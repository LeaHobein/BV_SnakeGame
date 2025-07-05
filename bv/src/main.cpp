/** Inspired by OpenCV-Tutorial https://docs.opencv.org/4.x/db/deb/tutorial_display_image.html
 Edited by Merijam Gotzes
 13.03.2024, 12.04.2024
 Praktikum VideoProcessingStartCode
*/

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>
#include <windows.h>
#include "blob_detection.hpp"
#include "line_detection.hpp"
#include "panel_composer.hpp"

using namespace std;
using namespace cv;

int main()
{
    // Open webcam (device 0)
    VideoCapture cap(0);
    //VideoCapture cap("../videos/Landscape.avi");
    //VideoCapture cap("../videos/ColoredBlobs2.wm");
    //VideoCapture cap("../videos/testgrid.mp4");
    if (!cap.isOpened()) {
        cout << "The video file or the camera could not be opened." << endl;
        return -1;
    } else {
        // Print video properties
        int fps = (int) cap.get(CAP_PROP_FPS);
        cout << "Frames per second :" << fps << endl;
        int frame_count = (int) cap.get(CAP_PROP_FRAME_COUNT);
        cout << "  Frame count :" << frame_count << endl;
    }

    // screen size herausfinden
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    Mat frameMat, grayImage, cannyAndHough;
    int i = 1;
    while (cap.read(frameMat))
    {
        i++;
        if ((i % 100)==0)
            cout << ".(" << i << ")" ;
        else
            cout << ".";

        // --- Blob Detection ---
        cv::Mat greenSquareResult;
        detectAndDrawBlobs(frameMat, grayImage);

        // --- Edge and Line Detection ---
        Mat frameCopy = frameMat.clone();
        detectAndDrawEdgesAndLines(frameCopy, grayImage, cannyAndHough);

        // --- Result Panels ---
        Mat matResult;
        composeResultPanels(frameMat, grayImage, cannyAndHough, matResult);

        // --- Resize for Display ---
        double scale = 0.8; // Use 80% of screen width
        int targetWidth = screenWidth * scale;
        int targetHeight = (frameMat.rows * targetWidth) / (frameMat.cols * 3);
        
        // sicherstellen, dass die Höhe nicht über den Bildschirmrand hinaus geht
        if (targetHeight > screenHeight * 0.8) {
            targetHeight = screenHeight * 0.8;
            targetWidth = (frameMat.cols * 3 * targetHeight) / frameMat.rows;
        }
        Mat resizedResult;
        resize(matResult, resizedResult, Size(targetWidth, targetHeight));

        // --- Show Result ---
        imshow("Ein Farbvideo in ein Grauwertvideo umwandeln.", resizedResult);
        int key = waitKey(20); // Wait for a keystroke in the window

        // q, ESC, window zumachen um das Fenster zu schließen
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

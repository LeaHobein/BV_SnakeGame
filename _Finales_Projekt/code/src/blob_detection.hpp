#ifndef BLOB_DETECTION_HPP
#define BLOB_DETECTION_HPP

#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include "square_detection.hpp"
#include <string>

// speichert blob-in-square info
struct BlobInSquare {
    std::string color;
    int squareIndex;
    cv::Point2f blobCenter;
};

void detectAndDrawBlobs(cv::Mat& frameMat, cv::Mat& grayImage) {
    cvtColor(frameMat, grayImage, cv::COLOR_BGR2HSV);
    std::vector<int> lower = {35, 25, 0};
    std::vector<int> upper = {95, 255, 255};
    inRange(grayImage, lower, upper, grayImage);
    medianBlur(grayImage, grayImage, 5);

    // Blob detection auf schwarz-weiß Bild
    cv::Ptr<cv::SimpleBlobDetector> blobDetector = cv::SimpleBlobDetector::create();
    blobDetector->read("..\\blobdetectorparams1.xml");
    std::vector<cv::KeyPoint> keypoints;
    blobDetector->detect(grayImage, keypoints);

    // Kreise malen
    for(const cv::KeyPoint& k: keypoints) {
        cv::circle(frameMat, k.pt, 30, cv::Scalar(0,0,0), 2);
    }

    //grüne Maske
    cv::Mat hsvImage;
    cvtColor(frameMat, hsvImage, cv::COLOR_BGR2HSV);
    std::vector<int> squareLower = {35, 50, 50};
    std::vector<int> squareUpper = {85, 255, 255};
    
    cv::Mat greenMask;
    inRange(hsvImage, squareLower, squareUpper, greenMask);
    
    //Maske säubern
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::morphologyEx(greenMask, greenMask, cv::MORPH_CLOSE, kernel);
    cv::morphologyEx(greenMask, greenMask, cv::MORPH_OPEN, kernel);
    
    //Contours finden
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(greenMask, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    //yellow blob detection
    std::vector<int> yellowLower = {20, 100, 100};
    std::vector<int> yellowUpper = {30, 255, 255};
    
    //gelbe Maske
    cv::Mat yellowMask;
    inRange(hsvImage, yellowLower, yellowUpper, yellowMask);
    medianBlur(yellowMask, yellowMask, 5);

    //Gelbe blobs finden
    std::vector<cv::KeyPoint> yellowKeypoints;
    blobDetector->detect(yellowMask, yellowKeypoints);

    //gelbe Kreise drumherum malen
    for(const cv::KeyPoint& k: yellowKeypoints) {
        cv::circle(frameMat, k.pt, 30, cv::Scalar(0,255,255), 2); // Yellow
    }

    //Blue blob detection
    std::vector<int> blueLower = {100, 50, 50};
    std::vector<int> blueUpper = {130, 255, 255};
    cv::Mat blueMask;
    inRange(hsvImage, blueLower, blueUpper, blueMask);
    medianBlur(blueMask, blueMask, 5);

    //blaue blobs finden
    std::vector<cv::KeyPoint> blueKeypoints;
    blobDetector->detect(blueMask, blueKeypoints);

    //blaue Kreise drumherum malen
    for(const cv::KeyPoint& k: blueKeypoints) {
        cv::circle(frameMat, k.pt, 30, cv::Scalar(255,0,0), 2); // blue
    }

    //Red blob detection
    cv::Mat redMask1, redMask2, redMask;
    inRange(hsvImage, cv::Scalar(0, 100, 100), cv::Scalar(10, 255, 255), redMask1);
    inRange(hsvImage, cv::Scalar(160, 100, 100), cv::Scalar(179, 255, 255), redMask2);
    cv::bitwise_or(redMask1, redMask2, redMask); //Masken mit bitwise or kombinieren
    medianBlur(redMask, redMask, 5);

    //rote Blobs finden
    std::vector<cv::KeyPoint> redKeypoints;
    blobDetector->detect(redMask, redKeypoints);

    //rote Kreise drumherum malen
    for(const cv::KeyPoint& k: redKeypoints) {
        cv::circle(frameMat, k.pt, 30, cv::Scalar(0,0,255), 2); // red
    }

    //gelbe Kästchen vom helper holen
    auto yellowSquares = findYellowSquares(grayImage);
    std::vector<BlobInSquare> blobsInSquares;

    //für jede Farbe checken, ob sie in einem der Kästchen sind
    auto checkBlobs = [&](const std::vector<cv::KeyPoint>& keypoints, const std::string& color) {
        for(const cv::KeyPoint& k: keypoints) {
            for(const auto& sq : yellowSquares) {
                double test = cv::pointPolygonTest(sq.contour, k.pt, false);
                if(test >= 0) {
                    blobsInSquares.push_back({color, sq.index, k.pt});
                }
            }
        }
    };
    checkBlobs(keypoints, "green");
    checkBlobs(yellowKeypoints, "yellow");
    checkBlobs(blueKeypoints, "blue");
    checkBlobs(redKeypoints, "red");

    //Text erscheint nur, wenn genau 49 (7x7) Kästchen gefunden wurden
    if (yellowSquares.size() == 49) {
        for(const auto& b : blobsInSquares) {
            std::string label = b.color + " in " + std::to_string(b.squareIndex);
            cv::Point textPos;
            for(const auto& sq : yellowSquares) {
                if(sq.index == b.squareIndex) {
                    textPos = sq.center;
                    break;
                }
            }
            textPos.y += 30;
            textPos.x = std::max(0, std::min(textPos.x, frameMat.cols - 1));
            textPos.y = std::max(0, std::min(textPos.y, frameMat.rows - 1));
            cv::putText(
                frameMat, label, textPos,
                cv::FONT_HERSHEY_SIMPLEX, 1.0,
                cv::Scalar(0,0,0), 3, cv::LINE_AA
            );
        }
    }
}

#endif // BLOB_DETECTION_HPP 
#ifndef BLOB_DETECTION_HPP
#define BLOB_DETECTION_HPP

// Blob detection helper for grid/feature detection
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>

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

    // Additional contour detection for green square corner detection
    // Create a separate mask for square detection with more restrictive green range
    cv::Mat hsvImage;
    cvtColor(frameMat, hsvImage, cv::COLOR_BGR2HSV);
    std::vector<int> squareLower = {35, 50, 50};   // More restrictive green range for squares
    std::vector<int> squareUpper = {85, 255, 255};
    
    cv::Mat greenMask;
    inRange(hsvImage, squareLower, squareUpper, greenMask);
    
    // Apply morphological operations to clean up the mask
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::morphologyEx(greenMask, greenMask, cv::MORPH_CLOSE, kernel);
    cv::morphologyEx(greenMask, greenMask, cv::MORPH_OPEN, kernel);
    
    // Find contours for square detection
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(greenMask, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    
    // Process each contour to find square-like shapes
    for (const auto& contour : contours) {
        // Approximate the contour to a polygon
        double epsilon = 0.02 * cv::arcLength(contour, true);
        std::vector<cv::Point> approx;
        cv::approxPolyDP(contour, approx, epsilon, true);
        
        // Check if it's a quadrilateral (4 corners)
        if (approx.size() == 4) {
            // Calculate area to filter out very small contours
            double area = cv::contourArea(approx);
            if (area > 1000) { // Minimum area threshold
                
                // Draw dots at the four corner points
                for (const auto& corner : approx) {
                    cv::circle(frameMat, corner, 10, cv::Scalar(255, 255, 255), 2); // White outline
                }
                
                // Draw the square outline in green
                cv::polylines(frameMat, std::vector<std::vector<cv::Point>>{approx}, true, cv::Scalar(0, 255, 0), 2);
            }
        }
    }

    // --- Additional yellow blob detection ---
    // Define yellow HSV range
    std::vector<int> yellowLower = {20, 100, 100};
    std::vector<int> yellowUpper = {30, 255, 255};
    
    // Create yellow mask
    cv::Mat yellowMask;
    inRange(hsvImage, yellowLower, yellowUpper, yellowMask);
    medianBlur(yellowMask, yellowMask, 5);

    // Detect yellow blobs
    std::vector<cv::KeyPoint> yellowKeypoints;
    blobDetector->detect(yellowMask, yellowKeypoints);

    // Draw yellow circles for detected yellow blobs
    for(const cv::KeyPoint& k: yellowKeypoints) {
        cv::circle(frameMat, k.pt, 30, cv::Scalar(0,255,255), 2); // Yellow color in BGR
    }

    // --- Blue blob detection ---
    std::vector<int> blueLower = {100, 50, 50};
    std::vector<int> blueUpper = {130, 255, 255};
    cv::Mat blueMask;
    inRange(hsvImage, blueLower, blueUpper, blueMask);
    medianBlur(blueMask, blueMask, 5);

    // Detect blue blobs
    std::vector<cv::KeyPoint> blueKeypoints;
    blobDetector->detect(blueMask, blueKeypoints);

    // Draw blue circles for detected blue blobs
    for(const cv::KeyPoint& k: blueKeypoints) {
        cv::circle(frameMat, k.pt, 30, cv::Scalar(255,0,0), 2); // blue color in BGR
    }

    // --- Red blob detection ---
    cv::Mat redMask1, redMask2, redMask;
    inRange(hsvImage, cv::Scalar(0, 100, 100), cv::Scalar(10, 255, 255), redMask1);
    inRange(hsvImage, cv::Scalar(160, 100, 100), cv::Scalar(179, 255, 255), redMask2);
    cv::bitwise_or(redMask1, redMask2, redMask); //Masken mit bitwise or kombinieren
    medianBlur(redMask, redMask, 5);

    // Detect red blobs
    std::vector<cv::KeyPoint> redKeypoints;
    blobDetector->detect(redMask, redKeypoints);

    // Draw red circles for detected red blobs
    for(const cv::KeyPoint& k: redKeypoints) {
        cv::circle(frameMat, k.pt, 30, cv::Scalar(0,0,255), 2); // red color in BGR
    }

    // Keep the green mask as grayscale for better line detection
    // The mask will be converted to BGR in the panel composer for display
}

#endif // BLOB_DETECTION_HPP 
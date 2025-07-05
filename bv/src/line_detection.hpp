#ifndef LINE_DETECTION_HPP
#define LINE_DETECTION_HPP

// Line and edge detection helpers for grid/feature detection
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>

void detectAndDrawEdgesAndLines(const cv::Mat& frameCopy, const cv::Mat& blobResult, cv::Mat& cannyAndHough) {
    cv::Mat edges;
    
    // Use the blob detection result (which contains green regions) for line detection
    // Convert blob result to grayscale if it's not already
    cv::Mat blobGray;
    if (blobResult.channels() == 3) {
        cv::cvtColor(blobResult, blobGray, cv::COLOR_BGR2GRAY);
    } else {
        blobGray = blobResult.clone();
    }
    
    // Apply blur to reduce noise in the blob regions
    cv::blur(blobGray, edges, cv::Size(3, 3));
    
    // Apply Canny edge detection on the green blob regions
    // Lowered Canny thresholds for more sensitivity on green regions
    cv::Canny(edges, edges, 50, 80, 3);

    // Morphological closing to connect broken lines within green regions
    cv::Mat morph;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::morphologyEx(edges, morph, cv::MORPH_CLOSE, kernel);

    // Prepare output image (black background)
    cannyAndHough = cv::Mat(frameCopy.size(), frameCopy.type(), cv::Scalar::all(0));

    // Draw Canny edges from green regions in red channel
    std::vector<cv::Mat> channels(3);
    cv::split(cannyAndHough, channels);
    channels[2] = edges; // Red channel shows edges from green blob regions
    cv::merge(channels, cannyAndHough);

    // Detect lines using Hough transform on the green blob regions
    std::vector<cv::Vec4i> linesP;
    // Adjusted parameters for detecting lines within green regions
    cv::HoughLinesP(morph, linesP, 1, CV_PI / 180, 50, 40, 25);
    
    // Filter for mostly horizontal and vertical lines with additional length constraints
    std::vector<cv::Vec4i> filteredLines;
    const double angleTolerance = 15.0; // Degrees tolerance for "straight enough"
    const int minLineLength = 25; // Minimum line length in pixels (reduced for green regions)
    const int maxLineLength = std::min(frameCopy.cols, frameCopy.rows) * 0.7; // Maximum line length
    
    for (const auto& l : linesP) {
        int x1 = l[0], y1 = l[1], x2 = l[2], y2 = l[3];
        
        // Calculate line length
        double length = std::sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
        
        // Skip lines that are too short or too long
        if (length < minLineLength || length > maxLineLength) {
            continue;
        }
        
        // Calculate the angle of the line
        double dx = x2 - x1;
        double dy = y2 - y1;
        double angle = std::atan2(std::abs(dy), std::abs(dx)) * 180.0 / CV_PI;
        
        // Check if line is mostly horizontal (angle close to 0 degrees)
        bool isHorizontal = angle <= angleTolerance;
        
        // Check if line is mostly vertical (angle close to 90 degrees)
        bool isVertical = angle >= (90.0 - angleTolerance);
        
        // Keep only horizontal and vertical lines
        if (isHorizontal || isVertical) {
            filteredLines.push_back(l);
        }
    }
    
    // Draw filtered Hough lines in green to emphasize they're detected from green regions
    for (const auto& l : filteredLines) {
        cv::line(cannyAndHough, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0,255,0), 3, cv::LINE_AA); // Green lines
    }

    // --- Detect filled black squares in the blob detection result and draw yellow outlines ---
    // Threshold for black (all channels low)
    cv::Mat blackMask;
    if (blobResult.channels() == 3) {
        cv::inRange(blobResult, cv::Scalar(0,0,0), cv::Scalar(40,40,40), blackMask); // adjust upper bound as needed
    } else {
        cv::inRange(blobResult, 0, 40, blackMask);
    }

    // Morphological closing to fill small holes in black regions
    cv::morphologyEx(blackMask, blackMask, cv::MORPH_CLOSE, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5,5)));

    // Find contours
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(blackMask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    for (const auto& contour : contours) {
        // Approximate contour to polygon
        std::vector<cv::Point> approx;
        cv::approxPolyDP(contour, approx, 0.04 * cv::arcLength(contour, true), true);

        // Check for quadrilateral (4 sides), convex, and area threshold
        if (approx.size() == 4 && cv::isContourConvex(approx)) {
            double area = cv::contourArea(approx);
            cv::Rect bound = cv::boundingRect(approx);
            double aspect = (double)bound.width / bound.height;
            // Area threshold and aspect ratio close to 1 (square)
            if (area > 400 && aspect > 0.8 && aspect < 1.2) {
                // Check if filled: area close to bounding rect area
                double fillRatio = area / (bound.width * bound.height);
                if (fillRatio > 0.7) {
                    // Draw yellow outline
                    cv::polylines(cannyAndHough, approx, true, cv::Scalar(0,255,255), 3, cv::LINE_AA);
                }
            }
        }
    }
}

#endif // LINE_DETECTION_HPP 
#ifndef LINE_DETECTION_HPP
#define LINE_DETECTION_HPP

// Line and edge detection helpers for grid/feature detection
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>

void detectAndDrawEdgesAndLines(const cv::Mat& frameCopy, cv::Mat& cannyAndHough) {
    cv::Mat edges;
    // Convert to grayscale and blur to reduce noise
    cv::cvtColor(frameCopy, edges, cv::COLOR_BGR2GRAY);
    cv::blur(edges, edges, cv::Size(3, 3));
    // Lowered Canny thresholds for more sensitivity
    cv::Canny(edges, edges, 80, 100, 3);

    // Morphological closing to connect broken lines
    cv::Mat morph;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::morphologyEx(edges, morph, cv::MORPH_CLOSE, kernel);

    // Prepare output image (black background)
    cannyAndHough = cv::Mat(frameCopy.size(), frameCopy.type(), cv::Scalar::all(0));

    // Draw Canny edges in red channel
    cv::Mat cannyMask;
    cv::Canny(frameCopy, cannyMask, 30, 100, 3); // Lowered thresholds
    std::vector<cv::Mat> channels(3);
    cv::split(cannyAndHough, channels);
    channels[2] = cannyMask; // Red channel
    cv::merge(channels, cannyAndHough);

    // Detect lines using Hough transform with stricter parameters
    std::vector<cv::Vec4i> linesP;
    // More strict parameters: higher threshold, shorter minLineLength, smaller maxLineGap
    cv::HoughLinesP(morph, linesP, 1, CV_PI / 180, 100, 90, 35);
    
    // Filter for mostly horizontal and vertical lines with additional length constraints
    std::vector<cv::Vec4i> filteredLines;
    const double angleTolerance = 15.0; // Degrees tolerance for "straight enough"
    const int minLineLength = 30; // Minimum line length in pixels
    const int maxLineLength = std::min(frameCopy.cols, frameCopy.rows) * 0.8; // Maximum line length
    
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
    
    // Draw filtered Hough lines in blue with exact endpoints
    for (const auto& l : filteredLines) {
        cv::line(cannyAndHough, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(255,0,0), 3, cv::LINE_AA); // Blue lines
    }
}

#endif // LINE_DETECTION_HPP 
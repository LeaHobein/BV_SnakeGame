#ifndef LINE_DETECTION_HPP
#define LINE_DETECTION_HPP

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>

void detectAndDrawEdgesAndLines(const cv::Mat& frameCopy, cv::Mat& cannyAndHough) {
    cv::Mat edges;
    cv::cvtColor(frameCopy, edges, cv::COLOR_BGR2GRAY);
    cv::blur(edges, edges, cv::Size(3, 3));
    cv::Canny(edges, edges, 80, 100, 3);

    cv::Mat morph;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::morphologyEx(edges, morph, cv::MORPH_CLOSE, kernel);

    cannyAndHough = cv::Mat(frameCopy.size(), frameCopy.type(), cv::Scalar::all(0));

    cv::Mat cannyMask;
    cv::Canny(frameCopy, cannyMask, 30, 100, 3);
    std::vector<cv::Mat> channels(3);
    cv::split(cannyAndHough, channels);
    channels[2] = cannyMask;
    cv::merge(channels, cannyAndHough);

    std::vector<cv::Vec4i> linesP;
    cv::HoughLinesP(morph, linesP, 1, CV_PI / 180, 100, 90, 35);

    std::vector<cv::Vec4i> filteredLines;
    const double angleTolerance = 15.0;
    const int minLineLength = 30;
    const int maxLineLength = std::min(frameCopy.cols, frameCopy.rows) * 0.8;
    
    for (const auto& l : linesP) {
        int x1 = l[0], y1 = l[1], x2 = l[2], y2 = l[3];

        double length = std::sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));

        if (length < minLineLength || length > maxLineLength) {
            continue;
        }

        double dx = x2 - x1;
        double dy = y2 - y1;
        double angle = std::atan2(std::abs(dy), std::abs(dx)) * 180.0 / CV_PI;

        bool isHorizontal = angle <= angleTolerance;

        bool isVertical = angle >= (90.0 - angleTolerance);

        if (isHorizontal || isVertical) {
            filteredLines.push_back(l);
        }
    }

    for (const auto& l : filteredLines) {
        cv::line(cannyAndHough, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(255,0,0), 3, cv::LINE_AA); // Blue lines
    }
}

#endif // LINE_DETECTION_HPP 
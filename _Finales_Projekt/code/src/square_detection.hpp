#ifndef SQUARE_DETECTION_HPP
#define SQUARE_DETECTION_HPP

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <string>

// Helper struct für yellow square info
struct YellowSquareInfo {
    std::vector<cv::Point> contour;
    cv::Point center;
    int index;
};

// Helper Funktion um gelbe Kästchen zu finden und zu sortieren
inline std::vector<YellowSquareInfo> findYellowSquares(const cv::Mat& blobResult) {
    std::vector<YellowSquareInfo> result;
    cv::Mat blackMask;
    if (blobResult.channels() == 3) {
        cv::inRange(blobResult, cv::Scalar(0,0,0), cv::Scalar(40,40,40), blackMask);
    } else {
        cv::inRange(blobResult, 0, 40, blackMask);
    }
    cv::morphologyEx(blackMask, blackMask, cv::MORPH_CLOSE, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5,5)));
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(blackMask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    struct SquareRaw {
        std::vector<cv::Point> approx;
        cv::Point center;
    };

    std::vector<SquareRaw> squares;
    for (const auto& contour : contours) {
        std::vector<cv::Point> approx;
        cv::approxPolyDP(contour, approx, 0.04 * cv::arcLength(contour, true), true);
        if (approx.size() == 4 && cv::isContourConvex(approx)) {
            double area = cv::contourArea(approx);
            cv::Rect bound = cv::boundingRect(approx);
            double aspect = (double)bound.width / bound.height;
            if (area > 400 && aspect > 0.8 && aspect < 1.2) {
                double fillRatio = area / (bound.width * bound.height);
                if (fillRatio > 0.7) {
                    cv::Point center(bound.x + bound.width/2, bound.y + bound.height/2);
                    squares.push_back({approx, center});
                }
            }
        }
    }
    std::sort(squares.begin(), squares.end(), [](const SquareRaw& a, const SquareRaw& b) {
        int rowTolerance = 20;
        if (std::abs(a.center.y - b.center.y) < rowTolerance) {
            return a.center.x < b.center.x;
        }
        return a.center.y < b.center.y;
    });
    for (size_t i = 0; i < squares.size(); ++i) {
        result.push_back({squares[i].approx, squares[i].center, static_cast<int>(i)});
    }
    return result;
}

void detectAndDrawEdgesAndLines(const cv::Mat& frameCopy, const cv::Mat& blobResult, cv::Mat& cannyAndHough) {
    cv::Mat edges;
    
    // Blob detection result wird benutzt (enthält grüne Regionen)
    cv::Mat blobGray;
    if (blobResult.channels() == 3) {
        cv::cvtColor(blobResult, blobGray, cv::COLOR_BGR2GRAY);
    } else {
        blobGray = blobResult.clone();
    }
    
    // weichzeichnen um Störungen zu reduzieren
    cv::blur(blobGray, edges, cv::Size(3, 3));
    
    // Canny edge detection
    cv::Canny(edges, edges, 50, 80, 3);

    // Morphological closing um abgetrennte Linien wieder zusammenzuführen
    cv::Mat morph;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::morphologyEx(edges, morph, cv::MORPH_CLOSE, kernel);

    // output image vorbereiten (black background)
    cannyAndHough = cv::Mat(frameCopy.size(), frameCopy.type(), cv::Scalar::all(0));

    //canny Kanten in rot malen
    std::vector<cv::Mat> channels(3);
    cv::split(cannyAndHough, channels);
    channels[2] = edges; // Red channel shows edges from green blob regions
    cv::merge(channels, cannyAndHough);

    // Hough Linienerkennung
    std::vector<cv::Vec4i> linesP;
    cv::HoughLinesP(morph, linesP, 1, CV_PI / 180, 50, 40, 25);

    //schwarze Kästchen suchen und gelbe Quadrate an die jeweiligen Stellen malen
    auto yellowSquares = findYellowSquares(blobResult);
    for (const auto& sq : yellowSquares) {
        cv::polylines(cannyAndHough, sq.contour, true, cv::Scalar(0,255,255), 3, cv::LINE_AA);
        cv::putText(
            cannyAndHough,
            std::to_string(sq.index),
            sq.center,
            cv::FONT_HERSHEY_SIMPLEX,
            0.5,
            cv::Scalar(255, 255, 255),
            2,
            cv::LINE_AA
        );
    }
}

#endif // SQUARE_DETECTION_HPP
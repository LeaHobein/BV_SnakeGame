#ifndef PANEL_COMPOSER_HPP
#define PANEL_COMPOSER_HPP

// Helper for composing result panels for display
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

void composeResultPanels(const cv::Mat& frameMat, const cv::Mat& grayImage, const cv::Mat& cannyAndHough, cv::Mat& matResult) {
    matResult = cv::Mat(cv::Size(frameMat.cols * 3, frameMat.rows), frameMat.type(), cv::Scalar::all(0));
    // Original with blobs
    frameMat.copyTo(matResult(cv::Rect(0, 0, frameMat.cols, frameMat.rows)));
    // Blob detection result
    grayImage.copyTo(matResult(cv::Rect(frameMat.cols, 0, frameMat.cols, frameMat.rows)));
    // Edge/line detection result
    cannyAndHough.copyTo(matResult(cv::Rect(frameMat.cols * 2, 0, frameMat.cols, frameMat.rows)));
}

#endif // PANEL_COMPOSER_HPP 
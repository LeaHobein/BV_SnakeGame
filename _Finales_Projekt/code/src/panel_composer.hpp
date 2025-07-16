#ifndef PANEL_COMPOSER_HPP
#define PANEL_COMPOSER_HPP

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

void composeResultPanels(const cv::Mat& frameMat, const cv::Mat& grayImage, const cv::Mat& cannyAndHough, cv::Mat& matResult) {
    matResult = cv::Mat(cv::Size(frameMat.cols * 3, frameMat.rows), frameMat.type(), cv::Scalar::all(0));
    // Original mit blobs
    frameMat.copyTo(matResult(cv::Rect(0, 0, frameMat.cols, frameMat.rows)));
    
    // Blob detection ergebnis
    cv::Mat blobDisplay;
    if (grayImage.channels() == 1) {
        cv::cvtColor(grayImage, blobDisplay, cv::COLOR_GRAY2BGR);
    } else {
        blobDisplay = grayImage.clone();
    }
    blobDisplay.copyTo(matResult(cv::Rect(frameMat.cols, 0, frameMat.cols, frameMat.rows)));
    
    // Edge/line detection ergebnis
    cannyAndHough.copyTo(matResult(cv::Rect(frameMat.cols * 2, 0, frameMat.cols, frameMat.rows)));
}

#endif // PANEL_COMPOSER_HPP 
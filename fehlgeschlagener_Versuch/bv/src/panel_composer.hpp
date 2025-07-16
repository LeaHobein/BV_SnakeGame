#ifndef PANEL_COMPOSER_HPP
#define PANEL_COMPOSER_HPP

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

void composeResultPanels(const cv::Mat& frameMat, const cv::Mat& grayImage, const cv::Mat& cannyAndHough, cv::Mat& matResult) {
    matResult = cv::Mat(cv::Size(frameMat.cols * 3, frameMat.rows), frameMat.type(), cv::Scalar::all(0));

    frameMat.copyTo(matResult(cv::Rect(0, 0, frameMat.cols, frameMat.rows)));

    grayImage.copyTo(matResult(cv::Rect(frameMat.cols, 0, frameMat.cols, frameMat.rows)));

    cannyAndHough.copyTo(matResult(cv::Rect(frameMat.cols * 2, 0, frameMat.cols, frameMat.rows)));
}

#endif // PANEL_COMPOSER_HPP 
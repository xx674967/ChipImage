#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
extern "C"
{
    enum QualityType
    {
        FOCUS,
        BRIGHTNESS
    };

    enum SearchStrategyType
    {
        BISECTION,
        SMARTSCAN
    };
    typedef int (*CaptureImage)(char *, int &, int);

    /**
     * @brief Search target from source image and return the location of the matched target image.
     * @param image 		source image data buffer encoded with Base64
     * @param imageSize		buffer size
     * @param type          focus quality or brightness quality. Default value is focus quality.
     * @return matched quality if successful. otherwise return non zero if failed.
     */
    __declspec(dllexport) float ImageQuality(char *image, int imageSize, QualityType type = QualityType::FOCUS);

    /**
     * @brief calculate the quality on specified focus value
     * @param minPosition               the minimum value of focus/brightness
     * @param maxPosition               the maximum value of focus/brightness
     * @param step                      the step for next position
     * @param captureImage              the function to capture the image
     * @param startPosition             the start position to search. Default value is -1 that means no speacified by user.
     * @param type                      Quality metric for focus or brightness
     * @param searchStrategy            the search strategy specified by user. default is REFOUCS strategy.
     * @return return the optimal focus or brightness position if successful, otherwise -1 will return.
     */
    __declspec(dllexport) int AutoAdjust(int minPosition,
                                         int maxPosition,
                                         int step,
                                         CaptureImage captureImage,
                                         int startPosition = -1,
                                         QualityType type = QualityType::FOCUS,
                                         SearchStrategyType strategy = SearchStrategyType::SMARTSCAN);

    __declspec(dllexport) float QueryQuality(int position, CaptureImage captureImage, QualityType type = QualityType::FOCUS);
    __declspec(dllexport) float FocusQuality(cv::Mat &image);
    __declspec(dllexport) float BrightQuality(cv::Mat &image);

    // Optimal position Search strategy
    /**
     * @brief Bisection search strategy to look for the optimum quality within the availiable position range
     * @param start                     the minimum position of focus/brightness search
     * @param end                       the maximum position of focus/brightness search
     * @param userStep                  the step for next position
     * @param captureImage              the function to capture the image
     * @param currentPosition           the start position to search. Default value is -1 that means no speacified by user.
     * @param type                      Quality metric for focus or brightness
     * @return return the optimal focus or brightness position if successful, otherwise -1 will return.
     */
    int BisectionSearch(int start, int end, int userStep, CaptureImage captureImage, int currentPosition = -1, QualityType type = QualityType::FOCUS);

    /**
     * @brief Refocus search strategy to look for the optimum quality within the availiable position range
     * @param start                     the minimum position of focus/brightness search
     * @param end                       the maximum position of focus/brightness search
     * @param userStep                  the step for next position
     * @param captureImage              the function to capture the image
     * @param currentPosition           the start position to search. Default value is -1 that means no speacified by user.
     * @param type                      Quality metric for focus or brightness
     * @return return the optimal focus or brightness position if successful, otherwise -1 will return.
     */
    int RefocusSearch(int start, int end, int userStep, CaptureImage captureImage, int currentPosition = -1, QualityType type = QualityType::FOCUS);

    float StatSharpnessGradient(cv::Mat &image);
    float StatSharpnessTenengrad(cv::Mat &image, const int threshold = 500);
    float StatSharpnessLaplacian(cv::Mat &image);
    float StatSharpnessVariance(cv::Mat &img);

    float StatBrightnessMean(cv::Mat &image);
    float StatBrightnessRMS(cv::Mat &img);
    float StatBrightnessFormula(cv::Mat &image);
    float StatBrightnessRMSFormula(cv::Mat &image);
}
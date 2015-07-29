#ifndef BARCODE_LOCATOR_H
#define BARCODE_LOCATOR_H

#include <opencv2/opencv.hpp>

using namespace std;
class Barcode_Locator
{
public:
    Barcode_Locator();
    cv::Mat GetBarLoc(cv::Mat img_input );

private:
    cv::Mat img , img_gray , img_smooth , img_thres;
    cv::Rect Crop(cv::Mat thres_img ,  cv::Point MaxPoint );
};

#endif // BARCODE_LOCATOR_H

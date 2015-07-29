#include <QCoreApplication>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
#include <barcode_locator.h>

using namespace std;
string type2str(int type);
cv::Rect Crop(cv::Mat thres_img , cv::Point MaxPoint );
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Barcode_Locator D;
    //input = cv::imread("07.jpg");

    cv::VideoCapture *capture = new cv::VideoCapture(0);
    cv::Mat input;
    //*capture >> input;

    while(1){
       capture->read(input);
       cv::resize(input , input , cv::Size(640,480));

       cv::Mat crop =  D.GetBarLoc(input);
       if(crop.data){
           cv::imshow("A",crop);
       }
       cv::imshow("L",input);
       cv::waitKey(30);
    }




    return a.exec();
}


string type2str(int type) {
  string r;

  uchar depth = type & CV_MAT_DEPTH_MASK;
  uchar chans = 1 + (type >> CV_CN_SHIFT);

  switch ( depth ) {
    case CV_8U:  r = "8U"; break;
    case CV_8S:  r = "8S"; break;
    case CV_16U: r = "16U"; break;
    case CV_16S: r = "16S"; break;
    case CV_32S: r = "32S"; break;
    case CV_32F: r = "32F"; break;
    case CV_64F: r = "64F"; break;
    default:     r = "User"; break;
  }

  r += "C";
  r += (chans+'0');

  return r;
}


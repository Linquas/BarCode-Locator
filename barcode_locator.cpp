#include "barcode_locator.h"

Barcode_Locator::Barcode_Locator()
{

}

cv::Mat Barcode_Locator::GetBarLoc(cv::Mat img_input){
    this->img = img_input;

    cv::Mat grad_x , grad_y;
    cv::Mat abs_grad_x , abs_grad_y;

    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;

//---------------------------------Gradient Calculation------------------------------------
    cv::GaussianBlur( this->img, this->img, cv::Size(3,3), 0, 0, cv::BORDER_DEFAULT );
    cv::cvtColor(this->img,this->img_gray,CV_BGR2GRAY);

    /// Gradient X
    cv::Sobel( this->img_gray, grad_x, ddepth, 1, 0, 3, scale, delta, cv::BORDER_DEFAULT );
    /// Gradient Y
    cv::Sobel( this->img_gray, grad_y, ddepth, 0, 1, 3, scale, delta, cv::BORDER_DEFAULT );

    cv::convertScaleAbs(grad_x , abs_grad_x);
    cv::convertScaleAbs(grad_y , abs_grad_y);

    //cv::imshow("grad_x",grad_x);
    //cv::imshow("grad_y",grad_y);
    //cv::imshow("abs_x",abs_grad_x);
    //cv::imshow("abs_y",abs_grad_y);

//--------------------------------Gradient difference between x and y-------------------
    cv::Mat grad_diff;
    grad_diff = cv::abs(abs_grad_x) - cv::abs(abs_grad_y);

    cv::imshow("diff",grad_diff);
    //cv::waitKey(0);

    cv::blur(grad_diff,this->img_smooth,cv::Size(31,31),cv::Point(-1,-1));//region normalization
    cv::imshow("smooth",this->img_smooth);

    //find the location of the max value
    double minval, maxval;
    cv::Point minloc, maxloc;
    cv::minMaxLoc(this->img_smooth, &minval, &maxval, &minloc, &maxloc);

    cout << "Max value : " << maxval << endl;

    cv::Mat Result;

    if(maxval > 135.0){
        // thresholding by OTSU method
        cv::Mat thres;
        cv::threshold(this->img_smooth,thres,0,255,CV_THRESH_BINARY | CV_THRESH_OTSU);
        cv::imshow("thres",thres);


        cv::Point MaxPoint;
        MaxPoint.x = maxloc.x;
        MaxPoint.y = maxloc.y;
        cv::Rect A = Crop( thres ,  MaxPoint );

        cv::rectangle(this->img , A , cv::Scalar(255,0,0) );
        cv::imshow("REs",this->img);
        Result = this->img_gray(A);
    }
    return Result;
}

cv::Rect Barcode_Locator::Crop(cv::Mat thres_img, cv::Point MaxPoint){
    int x = MaxPoint.x;
    int y = MaxPoint.y;
    cv::Rect Location;

    int Left_loc = -1 , Right_loc =-1, Up_loc=-1 , Down_loc =-1;


    for( int i = x ; (int)thres_img.ptr<uchar>(y)[i] != 0  ; i --){
        Left_loc = i;
    }
    for( int i = x ; thres_img.ptr<uchar>(y)[i] != 0  ; i ++){
        Right_loc = i;
    }
    for( int i = y ; thres_img.ptr<uchar>(i)[x] != 0  ; i ++){
        Down_loc = i;
    }
    for( int i = y ; thres_img.ptr<uchar>(i)[x] != 0  ; i --){
        Up_loc = i;
    }

    Location.x = Left_loc;
    Location.y = Up_loc;
    Location.width = Right_loc - Left_loc;
    Location.height = Down_loc - Up_loc  ;

    return Location;
}

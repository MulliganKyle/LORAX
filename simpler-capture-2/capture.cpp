/*
 *
 *  Example by Sam Siewert 
 *
 */
#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

#define HRES 320 
#define VRES 240


int main( int argc, char** argv )
{
    VideoCapture cap(0);
    if(!cap.isOpened())
        return -1;
    Mat frame;
    namedWindow("frame",1);

    cap.set(CAP_PROP_FRAME_HEIGHT, HRES);
    cap.set(CAP_PROP_FRAME_WIDTH, VRES);

    while(1)
    {
        cap >> frame;
     
        imshow("frame", frame);
        if(waitKey(30) >= 0) break;
    }   
}

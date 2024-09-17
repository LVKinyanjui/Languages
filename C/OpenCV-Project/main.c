#include <stdio.h>
#include <opencv2/videoio/videoio_c.h>

int main()
{
    // More info
    // https://docs.opencv.org/3.4/df/d47/videoio__c_8h.html
    CvCapture* webcam = cvCreateCameraCapture(0);
    return 0;
}

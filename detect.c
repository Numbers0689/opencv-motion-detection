#include<opencv/cv.h>
#include<opencv/highgui.h>
#include<stdlib.h>
#include<stdio.h>

int main(int argc, char** argv) {
    CvCapture* capture = cvCaptureFromCAM(0);
    if (!capture) {
        printf("Error: Could not initialize camera capture.\n");
        return -1;
    }

    IplImage* frame = cvQueryFrame(capture);
    if (!frame) {
        printf("Error: Could not grab a frame from the camera.\n");
        return -1;
    }

    IplImage* prev_frame = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 1);
    IplImage* gray_frame = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 1);
    IplImage* flow = cvCreateImage(cvGetSize(frame), IPL_DEPTH_32F, 2);
    cvNamedWindow("Motion Feed", 1);

    cvCvtColor(frame, prev_frame, CV_BGR2GRAY);

    int frame_count = 0;

    while (1) {
        frame = cvQueryFrame(capture);
        if (!frame) {
            break;
        }

        cvCvtColor(frame, gray_frame, CV_BGR2GRAY);
        cvCalcOpticalFlowFarneback(prev_frame, gray_frame, flow, 0.5, 3, 15, 3, 5, 1.2, 0);

        double sum_magnitude = 0.0;
        for (int y = 0; y < flow->height; y++) {
            for (int x = 0; x < flow->width; x++) {
                CvPoint2D32f flow_at_point = ((CvPoint2D32f*)flow->imageData)[y * flow->width + x];
                sum_magnitude += sqrt(flow_at_point.x * flow_at_point.x + flow_at_point.y * flow_at_point.y);
            }
        }

        double avg_magnitude = sum_magnitude / (flow->width * flow->height);
        if (avg_magnitude > 5.0) { 
            char filename[256];
            sprintf(filename, "Thief_%04d.jpg", frame_count);
            cvSaveImage(filename, frame, 0);
            cvShowImage("Motion Feed", frame);
            printf("Motion detected. Saved %s\n", filename);
            frame_count++;
        }
        cvCopy(gray_frame, prev_frame, NULL);
        if (cvWaitKey(30) == 27) {
            break;
        }
    }

    cvReleaseCapture(&capture);
    cvReleaseImage(&prev_frame);
    cvReleaseImage(&gray_frame);
    cvReleaseImage(&flow);
    cvDestroyAllWindows();

    return 0;
}

//Napisz program, który będzie wyłapywał 2 największe obiekty koloru czerwonego
// i jak zostaną ułożone w jednej poziomej linii (z jakimś marginesem) to między nimi zostaną narysowane 3 kreski

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// Write a program that will find the 2 largest red objects and if they are placed in one horizontal line (with some margin) then between them 3 lines will be drawn

int main(int argc, char** argv)
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera
        flip(frame, frame, 1);
        //find two biggest red objects on frame and connect them with 3 lines
        Mat hsv;
        cvtColor(frame, hsv, COLOR_BGR2HSV);
        Mat mask;
        inRange(hsv, Scalar(0, 100, 100), Scalar(10, 255, 255), mask);
        Mat mask2;
        inRange(hsv, Scalar(160, 100, 100), Scalar(179, 255, 255), mask2);
        mask = mask + mask2;
        Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
        morphologyEx(mask, mask, MORPH_OPEN, kernel);
        morphologyEx(mask, mask, MORPH_CLOSE, kernel);
        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;
        findContours(mask, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
        vector<vector<Point> > contours_poly(contours.size());
        vector<Rect> boundRect(contours.size());
        vector<Point2f>center(contours.size());
        vector<float>radius(contours.size());
        for (int i = 0; i < contours.size(); i++)
        {
            approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
            boundRect[i] = boundingRect(Mat(contours_poly[i]));
            minEnclosingCircle((Mat)contours_poly[i], center[i], radius[i]);
        }
        //if cant find any still try to find one
        if (contours.size() == 0 || contours.size() == 1)
        {
            continue;
        }
        vector<float> areas(contours.size());
        for (int i = 0; i < contours.size(); i++)
        {
            areas[i] = contourArea(contours[i]);
        }
        vector<float> areas2 = areas;
        sort(areas2.begin(), areas2.end());
        vector<int> indexes;
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < areas.size(); j++)
            {
                if (areas2[areas2.size() - 1 - i] == areas[j])
                {
                    indexes.push_back(j);
                    break;
                }
            }
        }
        if (indexes.size() == 2)
        {
            if (abs(center[indexes[0]].y - center[indexes[1]].y) < 50)
            {
                line(frame, Point(center[indexes[0]].x, center[indexes[0]].y), Point(center[indexes[1]].x, center[indexes[1]].y), Scalar(0, 0, 255), 3);
                line(frame, Point(center[indexes[0]].x, center[indexes[0]].y + 10), Point(center[indexes[1]].x, center[indexes[1]].y + 10), Scalar(0, 0, 255), 3);
                line(frame, Point(center[indexes[0]].x, center[indexes[0]].y - 10), Point(center[indexes[1]].x, center[indexes[1]].y - 10), Scalar(0, 0, 255), 3);
            }
        }




        imshow("frame", frame);
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}




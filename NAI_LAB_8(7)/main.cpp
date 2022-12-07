//Przygotuj projekt wykorzystujący bibliotekę OpenCV
//
//Niech program który jest w Twoim repozytorium będzie wyświetlał odbicie lustrzane tego co widzi kamerka.
// Jeśli nie działa okno, to niech zamiast okna, wynik pojawi się w serii plików png.
//
//Niech też program się zakończy w momencie wciśnięcia klawisza ESC.

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;



int main()
{
    VideoCapture cap(0);
    if (!cap.isOpened())
    {
        cout << "Cannot open the video cam" << endl;
        return -1;
    }

    double dWidth = cap.get(CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
    double dHeight = cap.get(CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

    cout << "Resolution of the video : " << dWidth << " x " << dHeight << endl;

    namedWindow("MyVideo", WINDOW_AUTOSIZE); //create a window called "MyVideo"

    while (true)
    {//mirror screen
        Mat frame;
        bool bSuccess = cap.read(frame); // read a new frame from video

        if (!bSuccess) //if not success, break loop
        {
            cout << "Cannot read a frame from video stream" << endl;
            break;
        }

        flip(frame, frame, 1);
        imshow("MyVideo", frame); //show the frame in "MyVideo" window

        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
        {
            cout << "esc key is pressed by user" << endl;
            break;
        }

    }
    return 0;
}


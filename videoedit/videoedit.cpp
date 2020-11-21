#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


int main() {
    string filename;
    cout << "What video do you want to edit: ";
    cin >> filename;
    VideoCapture cap(filename);

    if (!cap.isOpened()) {
        cout << "Error when opening video stream or file" << endl;
        return -1;
    }

    while (cap.isOpened()) {
        Mat frame;
        cap >> frame;

        if (frame.empty()) {
            break;
        }

        imshow("Frame", frame);

        char c = (char)waitKey(25);
        if (c == 27) {
            break;
        }
    }

    cap.release();
    destroyAllWindows();
}
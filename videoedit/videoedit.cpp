#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;


string getVideoFilename() {
    /// <summary>
    /// Get the filename of the video to edit
    /// </summary>
    /// <returns></returns>
    string filename;
    cout << "What video do you want to edit: ";
    cin >> filename;

    return filename;
}


int getOutVideoLength() {
    /// <summary>
    /// Get the length the output video should have
    /// </summary>
    /// <returns></returns>
    int length;
    cout << "How long should the output video be (in seconds): ";
    cin >> length;

    return length;
}


int main() {
    // Get the filename of the video to edit
    string filename = getVideoFilename();

    // Get the length that the output video should be
    int length = getOutVideoLength();
    

    // Open the video to edit
    VideoCapture cap(filename);

    // If there was an error opening the video, show an error message
    if (!cap.isOpened()) {
        cout << "Error when opening video stream or file" << endl;
        return -1;
    }

    // Iterate over each frame
    while (cap.isOpened()) {
        Mat frame;
        cap >> frame;

        if (frame.empty()) {
            break;
        }


        // Show the frame
        imshow("Frame", frame);


        // Wait for the press of the 'esc' button for 25ms
        char c = (char)waitKey(25);
        if (c == 27) {
            break;
        }
    }

    // Finally close the cap and close the window
    cap.release();
    destroyAllWindows();
}
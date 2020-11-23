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


time_t getTime() {
    auto time = chrono::system_clock::now();
    time_t now = chrono::system_clock::to_time_t(time);

    return now;
}


vector<int> BGRtoRGB(Vec3b arr) {
    /// <summary>
    /// Convert an vector of a pixel to an vector int
    /// </summary>
    /// <param name="arr"> The pixel array </param>
    /// <returns> A new array from BGR to RGB </returns>
    return { arr[2], arr[1], arr[0] };
}


vector<int> getFrameArray(Mat frame) {
    int red = 0, green = 0, blue = 0;

    for (int i = 0; i < frame.rows; i++) {
        for (int j = 0; j < frame.cols; j++) {
            Vec3b bgrPixel = frame.at<Vec3b>(i, j);
            vector<int> color = BGRtoRGB(bgrPixel);

            return color;
        }
    }
}


void runLoop(VideoCapture cap) {
    // If there was an error opening the video, show an error message
    if (!cap.isOpened()) {
        cout << endl;
        cout << "Error when opening video stream or file" << endl << endl;
        return;
    }

    int counter = 1;

    // Iterate over each frame
    while (cap.isOpened()) {
        Mat frame;
        Mat frame2;

        cap.read(frame);
        cap.read(frame2);

        if (frame.empty()) {
            break;
        }
        
        vector<int> frameArr = getFrameArray(frame);
        vector<int> frame2Arr = getFrameArray(frame2);
        
        cout << counter << ") [" << frameArr[0] << ", " << frameArr[1] << ", " << frameArr[2] << "]" << endl;
        cout << counter << ") [" << frame2Arr[0] << ", " << frame2Arr[1] << ", " << frame2Arr[2] << "]" << endl;

        // TODO Get the difference of each frame

        counter++;


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


int main() {
    // Get the filename of the video to edit
    string filename = getVideoFilename();

    // Get the length that the output video should be
    // int length = getOutVideoLength();
    
    // Open the video to edit
    VideoCapture cap(filename);


    time_t startTime = getTime();

    runLoop(cap);

    time_t deltaTime = getTime() - startTime;

    cout << "Elapsed Time: " << deltaTime << "s" << endl;
    
}
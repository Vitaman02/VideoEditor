#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;


void print2DVec(vector<vector<int>> arr, bool newline=false) {
    cout << "[";
    for (int i = 0; i < arr.size(); i++) {
        cout << "[";
        for (int j = 0; j < arr[i].size() - 1; j++) {
            cout << arr[i][j] << ", ";
        }

        int index = arr[i].size() - 1;
        if (i == arr.size() - 1) {
            cout << arr[i][index] << "]";
        } else {
            cout << arr[i][index] << "], ";
        }
    }
    cout << "]";
    if (newline) {
        cout << endl;
    }
}

void print3DVec(vector<vector<vector<int>>> arr) {
    cout << "[";
    int index = 0;
    for (int i = 0; i < arr.size()-1; i++) {
        print2DVec(arr[i], false);
        cout << ", ";
        index++;
    }

    index++;
    print2DVec(arr[index], false);
    cout << "]" << endl;
}

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


vector<vector<vector<int>>> getFrameArray(Mat frame) {
    /// <summary>
    /// Reads each channel of each pixel of each row and 
    /// creates an array of those rows from the frame
    /// </summary>
    /// <param name="frame"> The frame to create the array from </param>
    /// <returns> A new 3D array of the frame data </returns>

    vector<vector<vector<int>>> frameData;
    
    for (int i = 0; i < frame.rows; i++) {
        vector<vector<int>> row;
        for (int j = 0; j < frame.cols; j++) {
            Vec3b bgrPixel = frame.at<Vec3b>(i, j);
            vector<int> color = BGRtoRGB(bgrPixel);
            
            row.push_back(color);
        }

        frameData.push_back(move(row));
    }
    return frameData;
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
        // cap.read(frame2);

        if (frame.empty()) {
            break;
        }
        
        vector<vector<vector<int>>> frameArr = getFrameArray(frame);
        // vector<vector<vector<int>>> frame2Arr = getFrameArray(frame2);

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

    VideoCapture cap(filename);

    time_t startTime = getTime();

    cout << "Started" << endl;
    runLoop(cap);

    time_t deltaTime = getTime() - startTime;

    cout << "Elapsed Time: " << deltaTime << "s" << endl;
    
}
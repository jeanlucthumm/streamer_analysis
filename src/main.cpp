#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>

#include <boost/filesystem.hpp>

#include <iostream>
#include "../Prompter.h"

using namespace cv;
using namespace std;
using namespace boost::filesystem;


void mouse_callback(int event, int x, int y, int flag, void *param) {
    if (event == EVENT_MOUSEMOVE) {
        cout << "(" << x << "," << y << ")" << endl;
    }
}

void findCircle() {
    string name("data/a-s.jpg");
    Mat image;
    image = imread(name.c_str());

    if (image.empty()) {
        cout << "Could not open image file" << endl;
        return;
    }


    Mat gray;
    cvtColor(image, gray, COLOR_BGR2GRAY);


    GaussianBlur(gray, gray, Size(9, 9), 2, 2);

    vector<Vec3f> circles;

    HoughCircles(gray, circles, HOUGH_GRADIENT, 1, gray.rows / 8, 200, 50, 0, 0);

    for (auto &vec : circles) {
        Point center{cvRound(vec[0]), cvRound(vec[1])};
        int radius = cvRound(vec[2]);
        circle(image, center, 3, Scalar(0, 255, 0), -1);
        circle(image, center, radius, Scalar(0, 0, 255), 3);
    }

    namedWindow("example");
    imshow("example", image);

    cout << circles.size() << endl;
    for (auto &vec : circles) {
        cout << cvRound(vec[2]);
        cout << vec << "| ";
    }
    cout << endl;

    waitKey();

/*
 * 250, 50 works for modeled images
 * 120, 50 works with observed images
 */

    return;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    path data_path{argv[1]};

    // validate directory
    try {
        if (!exists(data_path) || !is_directory(data_path)) {
            cout << "invalid data path: " << data_path << endl;
            return EXIT_FAILURE;
        }
    } catch (filesystem_error& error) {
        cerr << error.what() << endl;
        return EXIT_FAILURE;
    }

    directory_iterator begin{data_path}, end;
    vector<directory_entry> entries{begin, end};

    Prompter prompter;
    for (auto &entry : entries) {
        cout << entry.path() << endl;
        prompter.prompt(entry.path());
    }
}
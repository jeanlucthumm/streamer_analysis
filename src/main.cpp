#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>

#include <iostream>

using namespace cv;
using namespace std;

void mouse_callback(int event, int x, int y, int flag, void *param) {
    if (event == EVENT_MOUSEMOVE) {
        cout << "(" << x << "," << y << ")" << endl;
    }
}

/*
 * 250, 50 works for modeled images
 * 120, 50 works with observed images
 */

int main() {
    string name("data/a-s.jpg");
    Mat image;
    image = imread(name.c_str());

    if (image.empty()) {
        cout << "Could not open image file" << endl;
        return -1;
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

    return 0;
}
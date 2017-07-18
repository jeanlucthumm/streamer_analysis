//
// Created by Jean-Luc Thumm on 7/18/17.
//

#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <opencv/cv.hpp>
#include "Prompter.h"

using namespace std;
using namespace cv;

void mouse_callback(int event, int x, int y, int flag, void *param) {
    Prompter *prompter = (Prompter *) param;
    ImageData &data = prompter->current_image_data;

    if (event == EVENT_MOUSEMOVE) {
        Point mouse_point{x, y};
        Mat matrix = data.matrix.clone(); // if bigger pictures, this is a huge bottleneck
        line(matrix, data.center, mouse_point, Scalar{255, 0, 0}, 1, LINE_AA);
        imshow(data.window_title, matrix);
    }
}

void Prompter::prompt(const boost::filesystem::path &image_path) {
    Mat image = imread(image_path.string());

    if (image.empty()) {
        cerr << "could not open image file: " << image_path.string() << endl;
        return;
    }

    Point center = calculate_center(image, false);
    if (center.x < 0) {
        cerr << "could not find any circles in image: " << image_path.string() << endl;
        return;
    }
    circle(image, center, 3, Scalar(0, 255, 0), -1); // display dot at center

    current_image_data.path = image_path.string();
    current_image_data.matrix = image;
    current_image_data.center = center;
    current_image_data.window_title = "Prompt";

    namedWindow(current_image_data.window_title);
    setMouseCallback(current_image_data.window_title, mouse_callback, this);
    imshow(current_image_data.window_title, image);

    waitKey(0);
}

const std::map<std::string, std::vector<double>> &Prompter::get_table() {
    return table;
}

cv::Point Prompter::calculate_center(cv::Mat &image, bool is_modeled) {
    Mat gray;
    cvtColor(image, gray, COLOR_BGR2GRAY);

    GaussianBlur(gray, gray, Size(15, 15), 2, 2); // reduces noise

    vector<Vec3f> circles;

    HoughCircles(gray, circles, HOUGH_GRADIENT, 1, gray.rows / 8,
                 120, 50, 0, 0);

    if (circles.size() == 0) {
        return Point{-1, -1}; // impossible point
    }

    Vec3f &circle = circles[0]; // good detection should only return one
    return Point{cvRound(circle[0]), cvRound(circle[1])};
}


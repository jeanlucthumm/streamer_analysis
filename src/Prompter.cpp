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

void show_with_lines(ImageData &data, Point mouse_point) {
    Mat matrix = data.matrix.clone(); // if bigger pictures, this is a huge bottleneck
    line(matrix, data.center, mouse_point, Scalar{255, 0, 0}, 1, LINE_AA);

    for (auto &point : data.streamer_clicks) {
        line(matrix, data.center, point, Scalar{244, 137, 244}, 1, LINE_AA);
    }

    imshow(data.window_title, matrix);
}

void mouse_callback(int event, int x, int y, int flag, void *param) {
    Prompter *prompter = (Prompter *) param;
    ImageData &data = prompter->current_image_data;

    if (event == EVENT_MOUSEMOVE) {
        Point mouse_point{x, y};
        show_with_lines(data, mouse_point);
    } else if (event == EVENT_LBUTTONUP) {
        Point mouse_point{x, y};
        data.streamer_clicks.push_back(mouse_point);
        show_with_lines(data, mouse_point);
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

    current_image_data.image_path = image_path;
    current_image_data.matrix = image;
    current_image_data.center = center;
    current_image_data.window_title = "Prompt";
    current_image_data.streamer_clicks.clear();

    namedWindow(current_image_data.window_title);
    setMouseCallback(current_image_data.window_title, mouse_callback, this);
    imshow(current_image_data.window_title, image);

    while ((char) waitKey(0) != ' ') {} // wait for user to add a few lines

    // record all angles
    for (auto &point : current_image_data.streamer_clicks) {
        double angle = calculate_angle(point, current_image_data.center);
        table[image_path.filename().string()].push_back(angle);
    }
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

double Prompter::calculate_angle(cv::Point point, cv::Point center) {
    double deltaX = point.x - center.x; // keep in mind openCV has 0,0 at top left
    double deltaY = center.y - point.y;
    double arc = abs(atan(deltaY / deltaX));

    if (deltaX > 0 && deltaY > 0) {
        return M_PI - arc;
    }
    if (deltaX > 0 && deltaY < 0) {
        return M_PI + arc;
    }
    if (deltaX < 0 && deltaY > 0) {
        return arc;
    }
    if (deltaX < 0 && deltaY < 0) {
        return 2 * M_PI - arc;
    }
    if (deltaX == 0 && deltaY > 0) {
        return M_PI / 2;
    }
    if (deltaX == 0 && deltaY < 0) {
        return 3 * M_PI / 2;
    }
    return -1; // origin was clicked
}


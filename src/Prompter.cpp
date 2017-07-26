//
// Created by Jean-Luc Thumm on 7/18/17.
//

#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <opencv/cv.hpp>
#include "Prompter.h"
#include "processing.h"

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
    ImageData &data = *(ImageData *) param;

    if (event == EVENT_MOUSEMOVE) {
        Point mouse_point{x, y};
        show_with_lines(data, mouse_point);
    } else if (event == EVENT_LBUTTONUP) {
        Point mouse_point{x, y};
        data.streamer_clicks.push_back(mouse_point);
        show_with_lines(data, mouse_point);
    }
}

ImageData Prompter::prompt(const boost::filesystem::path &image_path) {
    Mat image = imread(image_path.string());

    if (image.empty()) {
        throw image_error::def(image_path.string());
    }

    Point center = calculate_center(image, false);
    if (center.x < 0) {
        throw processing_error::center(image_path.string());
    }

    circle(image, center, 3, Scalar(0, 255, 0), -1); // display dot at center

    ImageData data;
    data.image_path = image_path;
    data.matrix = image;
    data.center = center;
    data.window_title = "Prompt";

    namedWindow(data.window_title);
    setMouseCallback(data.window_title, mouse_callback, &data);
    imshow(data.window_title, image);

    while ((char) waitKey(0) != ' ') {} // wait for user to add a few lines

    return data;

    // record all angles
//    for (auto &point : current_image_data.streamer_clicks) {
//        double angle = calculate_angle(point, current_image_data.center);
//        table[image_path.filename().string()].push_back(angle);
//    }
}

std::pair<ImageData, ImageData>
Prompter::prompt_double(const boost::filesystem::path &image1_path,
                        const boost::filesystem::path &image2_path) {
    Mat image1 = imread(image1_path.string());
    Mat image2 = imread(image2_path.string());

    if (image1.empty()) {
        throw image_error::def(image1_path.string());
    }
    if (image2.empty()) {
        throw image_error::def(image2_path.string());
    }

    bool isSimulated1 = processing::isSimulated(image1_path);
    bool isSimulated2 = processing::isSimulated(image2_path);

    Point center1 = calculate_center(image1, isSimulated1);
    Point center2 = calculate_center(image2, isSimulated2);

    if (center1.x < 0) {
        throw processing_error::center(image1_path.string());
    }
    if (center2.x < 0) {
        throw processing_error::center(image2_path.string());
    }

    circle(image1, center1, 3, Scalar(0, 255, 0), -1); // display centers
    circle(image2, center2, 3, Scalar(0, 255, 0), -1);

    ImageData data1, data2;

    data1.image_path = image1_path;
    data1.matrix = image1;
    data1.center = center1;
    data1.window_title = (isSimulated1) ? "Simulated" : "Observed";

    data2.image_path = image2_path;
    data2.matrix = image2;
    data2.center = center2;
    data2.window_title = (isSimulated2) ? "Simulated" : "Observed";

    namedWindow(data1.window_title);
    namedWindow(data2.window_title);
    setMouseCallback(data1.window_title, mouse_callback, &data1);
    setMouseCallback(data2.window_title, mouse_callback, &data2);
    imshow(data1.window_title, data1.matrix);
    imshow(data2.window_title, data2.matrix);

    while((char) waitKey(0) != ' ') {} // wait for user to add a few lines

    return make_pair(data1, data2);
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

//
// Created by Jean-Luc Thumm on 7/18/17.
//

#ifndef STEREO_READER_PROMPTER_H
#define STEREO_READER_PROMPTER_H


#include <map>
#include <boost/filesystem/path.hpp>
#include <opencv2/core/types.hpp>
#include "ImageData.h"

class Prompter {
public:
    void prompt(const boost::filesystem::path &image_path);

    const std::map<std::string, std::vector<double>> &get_table();

    Prompter() : table{} {}

private:
    cv::Point calculate_center(cv::Mat &image, bool is_modeled);

    double calculate_angle(cv::Point point, cv::Point center);

    friend void mouse_callback(int event, int x, int y, int flag, void *param);

    std::map<std::string, std::vector<double>> table;

    ImageData current_image_data;
};


#endif //STEREO_READER_PROMPTER_H

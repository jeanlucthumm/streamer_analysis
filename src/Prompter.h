//
// Created by Jean-Luc Thumm on 7/18/17.
//

#ifndef STEREO_READER_PROMPTER_H
#define STEREO_READER_PROMPTER_H


#include <map>
#include <boost/filesystem/path.hpp>
#include <opencv2/core/types.hpp>

class Prompter {
public:
    void prompt(const boost::filesystem::path &image_path);

    const std::map<std::string, std::vector<double>> &get_table();

    Prompter() : table{} {}

private:
    cv::Point calculate_center(cv::Mat &image, bool is_modeled);

    friend void mouse_callback(int event, int x, int y, int flag, void *param);

    std::map<std::string, std::vector<double>> table;
};


#endif //STEREO_READER_PROMPTER_H

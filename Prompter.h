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
    void prompt(boost::filesystem::path &image_path);

    const std::map<std::string, std::vector> &get_table();

    Prompter() : table{} {}

private:
    cv::Point calculate_center(cv::Mat &image);

    std::map<std::string, std::vector> table;
};


#endif //STEREO_READER_PROMPTER_H

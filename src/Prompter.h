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
    /**
     * Prompts user with a pair of images closer inspection. The order of clicks on
     * each image determines which streamers are correlated, i.e. first click
     * on image A is correlated to first click on image B. Clicks can be made all at
     * once for each image, or by rotating through all the images.
     * @param image1_path path to first image
     * @param image2_path path to second image
     * @return a pair of data where the first entry corresponds to image1_path, and second
     * to image2_path
     */
    std::pair<ImageData, ImageData>
    prompt_double(const boost::filesystem::path &image1_path,
                  const boost::filesystem::path &image2_path);

    const std::map<std::string, std::vector<double>> &get_table();

    Prompter() : table{} {}

private:
    cv::Point calculate_center(cv::Mat &image, bool is_modeled);

    friend void mouse_callback(int event, int x, int y, int flag, void *param);

    std::map<std::string, std::vector<double>> table;

    ImageData current_image;

    std::pair<ImageData, ImageData> current_image_pair;
};

class image_error : public std::runtime_error {
public:
    static image_error def(const std::string &name) {
        return image_error("could not open/find image: " + name);
    }

    image_error(std::string message) : runtime_error(message) {}
};

class processing_error : public std::runtime_error {
public:
    static processing_error def(const std::string &name) {
        return processing_error{"could not process image: " + name};
    }

    static processing_error center(const std::string &name) {
        return processing_error{"could not find center of image: " + name};
    }

    processing_error(std::string message) : runtime_error(message) {}
};


#endif //STEREO_READER_PROMPTER_H

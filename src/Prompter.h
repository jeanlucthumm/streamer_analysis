//
// Created by Jean-Luc Thumm on 7/18/17.
//

#ifndef STEREO_READER_PROMPTER_H
#define STEREO_READER_PROMPTER_H


#include <map>
#include <boost/filesystem/path.hpp>
#include <boost/optional.hpp>
#include <opencv2/core/types.hpp>
#include "ImageData.h"

class Prompter {
public:
    void prompt(const boost::filesystem::path &image_path);

    /**
     * Prompt with a pair of images to allow use to see correlated streamers
     * @param image1_path path to the first image
     * @param image2_path path to the second image
     * @return an optional pair of ImageData, where correlated streamer clicks occupy the same
     * index in the ImageData.streamer_clicks array, or boost::none if error occured
     */
    boost::optional<std::pair<ImageData, ImageData>>
    prompt_double(const boost::filesystem::path &image1_path,
                  const boost::filesystem::path &image2_path);

    const std::map<std::string, std::vector<double>> &get_table();

    Prompter() : table{} {}

private:
    cv::Point calculate_center(cv::Mat &image, bool is_modeled);

    double calculate_angle(cv::Point point, cv::Point center);

    friend void mouse_callback(int event, int x, int y, int flag, void *param);

    std::map<std::string, std::vector<double>> table;

    ImageData current_image_data;
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
        return processing_error{"coudl not find center of image: " + name};
    }

    processing_error(std::string message) : runtime_error(message) {}
};


#endif //STEREO_READER_PROMPTER_H

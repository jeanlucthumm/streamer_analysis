//
// Created by Jean-Luc Thumm on 7/26/17.
//

#ifndef STEREO_READER_PAIRLISTTEST_H
#define STEREO_READER_PAIRLISTTEST_H

#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <iostream>
#include "../src/PairList.h"

using namespace std;

TEST(PairList, construct) {
    vector<string> good_path_strings {
            "data/a-s.jpg",
            "data/a-o.jpg",
            "data/hello-o.jpg",
            "data/there-s.jpg",
            "data/hello-s.jpg",
            "data/there-o.jpg"
    };

    vector<boost::filesystem::path> good_paths;
    for (string &s : good_path_strings) {
        good_paths.emplace_back(s);
    }

    PairList pair_list{good_paths};
}

#endif //STEREO_READER_PAIRLISTTEST_H

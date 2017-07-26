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
#include "../src/processing.h"

using namespace std;

TEST(PairList, construct) {
    vector<string> path_strings {
            "data/a-s.jpg",
            "data/a-o.jpg",
            "data/hello-o.jpg",
            "data/there-s.jpg",
            "data/hello-s.jpg",
            "data/there-o.jpg"
    };

    vector<boost::filesystem::path> paths;
    for (string &s : path_strings) {
        paths.emplace_back(s);
    }

    PairList pair_list{paths};
    for (auto &entry : pair_list) {
        EXPECT_EQ(entry.first, processing::get_pair(entry.second));
    }

    paths.emplace_back("what");
    paths[0] = boost::filesystem::path{"data/b-s"};

    PairList pair_list_bad{paths};
}

#endif //STEREO_READER_PAIRLISTTEST_H

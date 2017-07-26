//
// Created by Jean-Luc Thumm on 7/25/17.
//

#ifndef STEREO_READER_PROCESSINGTEST_H
#define STEREO_READER_PROCESSINGTEST_H

#include <gtest/gtest.h>
#include "../src/processing.h"

TEST(processing, get_prefix) {
    // Good cases
    EXPECT_EQ(processing::get_prefix("a-s.jpg"), "a");
    EXPECT_EQ(processing::get_prefix("sdf-o.jpg"), "sdf");
    EXPECT_EQ(processing::get_prefix("hello_333-o.jpg"), "hello_333");
    EXPECT_EQ(processing::get_prefix("data/jean/hello_333-o.jpg"), "hello_333");

    ASSERT_THROW(processing::get_prefix("aa"), std::runtime_error);
    ASSERT_THROW(processing::get_prefix("example.jpg"), std::runtime_error);
}

#endif //STEREO_READER_PROCESSINGTEST_H

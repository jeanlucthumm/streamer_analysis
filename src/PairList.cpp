//
// Created by Jean-Luc Thumm on 7/26/17.
//

#include "PairList.h"
#include <algorithm>
#include <iostream>

using namespace std;

PairList::PairList(std::vector<boost::filesystem::path> path_list) {
    sort(path_list.begin(), path_list.end(), comparator);
}

std::vector<std::pair<boost::filesystem::path, boost::filesystem::path>>::iterator
PairList::begin() {
    return pair_list.begin();
}

std::vector<std::pair<boost::filesystem::path, boost::filesystem::path>>::iterator PairList::end() {
    return pair_list.end();
}

bool PairList::comparator(const boost::filesystem::path &a, const boost::filesystem::path &b) {
    return a.string() < b.string();
}

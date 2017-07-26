//
// Created by Jean-Luc Thumm on 7/26/17.
//

#include "PairList.h"
#include "processing.h"
#include <algorithm>
#include <iostream>
#include <unordered_set>

using namespace std;
using namespace processing;
using boost::filesystem::path;

PairList::PairList(const std::vector<boost::filesystem::path> &path_list) {
    vector<path> paths{path_list.begin(), path_list.end()};
    sort(paths.begin(), paths.end());

    auto itr = paths.begin();
    while (itr + 1 < paths.end()) {
        if (get_pair(*itr) == *(itr + 1)) {
            pair_list.push_back(make_pair(*itr, *(itr + 1)));
            itr += 2;
        } else {
            cerr << "could not find pair path for: " << itr->string() << endl;
            itr++;
        }
    }

    // check for left over path
    if (itr != paths.end()) {
        cerr << "could not find pair path for: " << itr->string() << endl;
    }
}

std::vector<std::pair<boost::filesystem::path, boost::filesystem::path>>::iterator
PairList::begin() {
    return pair_list.begin();
}

std::vector<std::pair<boost::filesystem::path, boost::filesystem::path>>::iterator PairList::end() {
    return pair_list.end();
}

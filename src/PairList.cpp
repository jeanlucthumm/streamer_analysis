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
using boost::filesystem::directory_entry;

PairList::PairList(const std::vector<boost::filesystem::path> path_list) {
    populate_list(path_list);
}

PairList::PairList(const std::vector<boost::filesystem::directory_entry> &dir_list) {
    vector<path> path_list;
    for (auto &dir : dir_list) {
        path_list.push_back(dir.path());
    }
    populate_list(path_list);
}

std::vector<std::pair<boost::filesystem::path, boost::filesystem::path>>::iterator
PairList::begin() {
    return pair_list.begin();
}

std::vector<std::pair<boost::filesystem::path, boost::filesystem::path>>::iterator PairList::end() {
    return pair_list.end();
}

void PairList::populate_list(const std::vector<boost::filesystem::path> &path_list) {
    sort(path_list.begin(), path_list.end());

    auto itr = path_list.begin();
    while (itr + 1 < path_list.end()) {
        if (get_pair(*itr) == *(itr + 1)) {
            pair_list.push_back(make_pair(*itr, *(itr + 1)));
            itr += 2;
        } else {
            cerr << "could not find pair path for: " << itr->string() << endl;
            itr++;
        }
    }

    // check for left over path
    if (itr != path_list.end()) {
        cerr << "could not find pair path for: " << itr->string() << endl;
    }
}


//
// Created by Jean-Luc Thumm on 7/26/17.
//

#ifndef STEREO_READER_PAIRLIST_H
#define STEREO_READER_PAIRLIST_H

#include <vector>
#include <boost/filesystem.hpp>

class PairList {
public:
    PairList(const std::vector<boost::filesystem::path> path_list);

    PairList(const std::vector<boost::filesystem::directory_entry> &dir_list);

    std::vector<std::pair<boost::filesystem::path, boost::filesystem::path>>::iterator
    begin();

    std::vector<std::pair<boost::filesystem::path, boost::filesystem::path>>::iterator
    end();

private:
    std::vector<std::pair<boost::filesystem::path, boost::filesystem::path>> pair_list;

    void populate_list(std::vector<boost::filesystem::path> &path_list);
};


#endif //STEREO_READER_PAIRLIST_H

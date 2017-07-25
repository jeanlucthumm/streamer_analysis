//
// Created by Jean-Luc Thumm on 7/20/17.
//

#ifndef STEREO_READER_NAMEPROCESSOR_H
#define STEREO_READER_NAMEPROCESSOR_H

#include <boost/filesystem/path.hpp>

#define OBS "-o"
#define SIM "-s"

class NameInterpreter {
public:
    static boost::filesystem::path get_pair(boost::filesystem::path name);

    static bool isObserved(const boost::filesystem::path &name);

    static bool isSimulated(const boost::filesystem::path &name);

private:
    static void print_err_msg(const std::string &name);
};


#endif //STEREO_READER_NAMEPROCESSOR_H

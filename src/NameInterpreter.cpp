//
// Created by Jean-Luc Thumm on 7/20/17.
//

#include "NameInterpreter.h"
#include <vector>
#include <iostream>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost::filesystem;

boost::filesystem::path processing::get_pair(boost::filesystem::path name) {
    if (isObserved(name)) {
        string name_str = name.string();
        boost::replace_last(name_str, OBS, SIM);
        return path{name_str};
    } else if (isSimulated(name)) {
        string name_str = name.string();
        boost::replace_last(name_str, SIM, OBS);
        return path{name_str};
    } else {
        cerr << "could not find pair for image: " + name.string() << endl;
        return "";
    }
}

bool processing::isObserved(const boost::filesystem::path &name) {
    return boost::contains(name.stem().string(), OBS);
}

bool processing::isSimulated(const boost::filesystem::path &name) {
    return boost::contains(name.stem().string(), SIM);
}


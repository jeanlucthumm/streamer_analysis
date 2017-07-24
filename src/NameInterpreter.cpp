//
// Created by Jean-Luc Thumm on 7/20/17.
//

#include "NameInterpreter.h"
#include <vector>
#include <iostream>
#include <boost/algorithm/string.hpp>

using namespace std;

std::string NameInterpreter::get_pair(std::string name) {
    if (isSimulated(name)) {
        boost::replace_last(name, "-s", "-o");
    } else if (isObserved(name)) {
        boost::replace_last(name, "-o", "-s");
    } else {
        print_err_msg(name);
        return ""; // TODO figure out a better way to report error
    }
    return name;
}

void NameInterpreter::print_err_msg(std::string &name) {
    cerr << "could not get pair for name: " << name << endl;
}

bool NameInterpreter::isObserved(const std::string &name) {
    return boost::contains(name, "-o");
}

bool NameInterpreter::isSimulated(const std::string &name) {
    return boost::contains(name, "-s");
}

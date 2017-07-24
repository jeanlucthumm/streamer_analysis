//
// Created by Jean-Luc Thumm on 7/20/17.
//

#ifndef STEREO_READER_NAMEPROCESSOR_H
#define STEREO_READER_NAMEPROCESSOR_H


#include <string>

class NameInterpreter {
public:
    static std::string get_pair(std::string name);

private:
    static void print_err_msg(std::string &name);
};


#endif //STEREO_READER_NAMEPROCESSOR_H

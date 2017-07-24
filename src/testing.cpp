//
// Created by Jean-Luc Thumm on 7/24/17.
//
#include <iostream>
#include "NameProcessor.h"

using namespace std;

int main(int argc, char **argv) {
    cout << NameProcessor::get_pair("a-s.jpg") << endl;
    cout << NameProcessor::get_pair("data/asf_333-o.jpg") << endl;
    cout << NameProcessor::get_pair("data/asf_333-p.jpg") << endl;

    string test = "b-s.jpg";
    cout << NameProcessor::get_pair(test) << endl;
    cout << test << endl;
}


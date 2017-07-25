//
// Created by Jean-Luc Thumm on 7/24/17.
//
#include <iostream>
#include "NameInterpreter.h"

using namespace std;
using namespace boost::filesystem;
using namespace processing;

void test_get_pair() {
    cout << processing::get_pair(path{"a-s.jpg"}) << endl;
    cout << processing::get_pair(path{"data/asf_333-o.jpg"}) << endl;
    cout << processing::get_pair(path{"data/asf_333-p.jpg"}) << endl;

    string test = "b-s.jpg";
    cout << processing::get_pair(test) << endl;
    cout << test << endl;
}

void test_get_prefix() {
    cout << get_prefix(path{"a-s.jpg"}) << endl;
    cout << get_prefix(path{"data/asdf_22-o.jpg"}) << endl;

    try {
        get_prefix(path{"asdf"});
    } catch (runtime_error &error) {
        cerr << error.what() << endl;
    }
}

int main(int argc, char **argv) {
    test_get_prefix();
}


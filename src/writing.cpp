//
// Created by Jean-Luc Thumm on 7/27/17.
//

#include "writing.h"
#include <map>

using namespace std;

void writing::write_angle_diff(std::ofstream &out, const std::vector<Correlation> &data) {
    out << "prefix,simulated angle,observed angle,diff,..." << endl;

    // sort correlations by prefix
    map<string, vector<Correlation>> table;
    for (auto &correlation : data) {
        table[correlation.prefix].push_back(correlation);
    }

    for (auto &entry : table) {
        out << entry.first;
        for (auto &correlation : entry.second) {
            out << "," << correlation.s_angle << "," << correlation.o_angle;
            out << "," << correlation.diff();
        }
        out << endl;
    }
}

void writing::write_angle(std::ofstream &out, const std::vector<Correlation> &data) {
    out << "prefix,simulated angle,observed angle,..." << endl;

    map<string, vector<Correlation>> table;
    for (auto &correlation : data) {
        table[correlation.prefix].push_back(correlation);
    }

    for (auto &entry : table) {
        out << entry.first; // prefix
        for (auto &correlation : entry.second) {
            out << "," << correlation.s_angle << "," << correlation.o_angle;
        }
        out << endl;
    }
}

void writing::write_diff(std::ofstream &out, const std::vector<Correlation> &data) {
    out << "prefix,diff,..." << endl;

    map<string, vector<Correlation>> table;
    for (auto &correlation : data) {
        table[correlation.prefix].push_back(correlation);
    }

    for (auto &entry : table) {
        out << entry.first;
        for (auto &correlation : entry.second) {
            out << "," << correlation.diff();
        }
        out << endl;
    }
}

#include <boost/filesystem.hpp>
#include <iostream>
#include "Prompter.h"

using namespace std;
using namespace boost::filesystem;

int main(int argc, char **argv) {
    if (argc != 3) {
        cout << "USAGE: stereo-reader data_dir csv_output_file" << endl;
        return EXIT_FAILURE;
    }

    path data_path{argv[1]};

    // validate directory
    try {
        if (!exists(data_path) || !is_directory(data_path)) {
            cout << "invalid data path: " << data_path << endl;
            return EXIT_FAILURE;
        }
    } catch (filesystem_error &error) {
        cerr << error.what() << endl;
        return EXIT_FAILURE;
    }

    std::ofstream file{argv[2]};
    if (!file.is_open()) {
        cout << "could not create output file" << endl;
        return EXIT_FAILURE;
    }

    directory_iterator begin{data_path}, end;
    vector<directory_entry> entries{begin, end};
    random_shuffle(entries.begin(), entries.end()); // randomize to eliminate bias

    Prompter prompter;
    for (auto &entry : entries) {
        try {
            prompter.prompt(entry.path());
        } catch (runtime_error &error) {
            cerr << error.what() << endl;
        }
    }

    // write csv file
    file << "file name,angle1,angle2,..." << endl;

    auto &table = prompter.get_table();
    for (auto &entry : table) {
        file << entry.first;
        for (double angle : entry.second) {
            file << "," << angle;
        }
        file << endl;
    }

    file.close();

    return EXIT_SUCCESS;
}
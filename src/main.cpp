#include <boost/filesystem.hpp>
#include <iostream>
#include "Prompter.h"
#include "processing.h"
#include "PairList.h"

using namespace std;
using namespace boost::filesystem;

static void print_data_pair(pair<ImageData, ImageData> &entry) {
    vector<double> angles1, angles2;
    for (auto &point : entry.first.streamer_clicks) {
        angles1.push_back(processing::compute_angle(point, entry.first.center));
    }
    for (auto &point : entry.second.streamer_clicks) {
        angles2.push_back(processing::compute_angle(point, entry.second.center));
    }

    cout << "First angles: ";
    for (double angle : angles1) {
        cout << angle << " ";
    }
    cout << endl;
    cout << "Second angles: ";
    for (double angle: angles2) {
        cout << angle << " ";
    }
    cout << endl;
}

vector<directory_entry> get_entries(string name) {
    path data_path{name};

    // validate directory
    if (!exists(data_path) || !is_directory(data_path)) {
        throw runtime_error("invalid data path: " + data_path.string());
    }

    directory_iterator begin{data_path}, end;
    return vector<directory_entry>{begin, end};
}

int main(int argc, char **argv) {
    if (argc != 3) {
        cout << "USAGE: stereo-reader data_dir csv_output_file" << endl;
        return EXIT_FAILURE;
    }

    // get file list
    vector<directory_entry> entries;
    try {
        entries = get_entries(argv[1]);
    } catch (runtime_error &error) {
        cerr << error.what() << endl;
        return EXIT_FAILURE;
    }
    PairList pair_list{entries}; // extract pairs

    // open output file
    std::ofstream file{argv[2]};
    if (!file.is_open()) {
        cerr << "could not create output file" << endl;
        return EXIT_FAILURE;
    }

    Prompter prompter;
    vector<pair<ImageData, ImageData>> image_pairs;
    for (auto &pair : pair_list) {
        try {
            while (true) {
                auto result = prompter.prompt_double(pair.first, pair.second);
                if (processing::validate_image_pair(result.first, result.second)) {
                    image_pairs.push_back(result);
                    break;
                }
                cerr << "Invalid streamer pairs. Did you click the same amount of times in each "
                        "picture?" << endl;
            }
        } catch (runtime_error &error) {
            cerr << error.what() << endl;
        }
    }

    // get correlations by processing image pairs
    try {
        vector<Correlation> correlations = processing::compute_correlations(image_pairs);
    } catch (runtime_error &error) {
        cerr << error.what() << endl;
        return EXIT_FAILURE;
    }

    return 0;

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
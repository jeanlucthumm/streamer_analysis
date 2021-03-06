#include <boost/filesystem.hpp>
#include <iostream>
#include "Prompter.h"
#include "processing.h"
#include "writing.h"
#include "PairList.h"

#define USAGE "streamer_analysis [-d data_dir | -v] -f "

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

static bool prompt_operation(string data_dir, string output_file) {
    // get file list
    vector<directory_entry> entries;
    try {
        entries = get_entries(data_dir);
    } catch (runtime_error &error) {
        cerr << error.what() << endl;
        return false;
    }
    PairList pair_list{entries}; // extract pairs

    // open output files
    path base_path{output_file};


    path angle_diff_path = processing::add_suffix(base_path, "_angle_diff");
    path angle_path = processing::add_suffix(base_path, "_angle");
    path diff_path = processing::add_suffix(base_path, "_diff");

    std::ofstream angle_diff_file{angle_diff_path.string()};
    std::ofstream angle_file{angle_path.string()};
    std::ofstream diff_file{diff_path.string()};

    if (!angle_diff_file.is_open() || !angle_file.is_open() || !diff_file.is_open()) {
        cerr << "Could not open output files" << endl;
        return false;
    }

    // prompt user
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
    vector<Correlation> correlations;
    try {
        correlations = processing::compute_correlations(image_pairs);
    } catch (runtime_error &error) {
        cerr << error.what() << endl;
        return false;
    }

    // write to files
    writing::write_angle_diff(angle_diff_file, correlations);
    writing::write_angle(angle_file, correlations);
    writing::write_diff(diff_file, correlations);

    return true;
}

int main(int argc, char **argv) {
    if (argc == 3) {
        string data_dir = argv[1];
        string output_path = argv[2];
        bool retval = prompt_operation(data_dir, output_path);
        return (retval) ? EXIT_SUCCESS : EXIT_FAILURE;
    } else {
        cout << USAGE << endl;
        return EXIT_FAILURE;
    }
}
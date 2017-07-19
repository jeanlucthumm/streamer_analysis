import utils
import csv
import sys

USAGE = 'USAGE: interpret_results file.csv'

table = {}





def main(argv):
    if len(argv) != 2:
        print(USAGE)
        return

    path = argv[1]
    with open(path, newline='') as file:
        file.readline()  # ignore header
        reader = csv.reader(file, delimiter=',')
        for row in reader:
            if len(row) < 1:
                print('malformed row:', row)
                continue
            parts = utils.get_name_data(row[0])
            if parts is None:
                print('could not process file name:', row[0])
                continue
            utils.populate_table(table, parts, row[1:])
    for k, data_point in table.items():
        print(k, utils.get_streamer_delta(data_point, 0.5))


if __name__ == '__main__':
    main(sys.argv)

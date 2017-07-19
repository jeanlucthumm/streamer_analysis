import utils
import csv
import sys

USAGE = """USAGE: process_correlation angles_file out_file thresh
    angles_file: csv file containing streamer angles for indiv images
    out_file: where to write correlation deltas in csv format
    thresh: all deltas are under this value are considered a correlation"""

table = {}


def main(argv):
    if len(argv) != 4:
        print(USAGE)
        return

    try:
        thresh = float(argv[3])
    except ValueError:
        print('could not process threshold:', argv[3])
        return

    with open(argv[1], newline='') as file:
        print('Reading file', file.name, '...')
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

    with open(argv[2], 'w') as out:
        print('Writing results to', out.name, '...')
        out.write('prefix,diff1,diff2,...\n')
        for k, data_point in table.items():
            out.write(k)
            for diff in utils.get_streamer_delta(data_point, thresh):
                out.write(',' + str(diff))
            out.write('\n')


if __name__ == '__main__':
    main(sys.argv)

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
                continue
            parts = utils.get_name_data(row[0])
            if parts is None:
                print('could not process file name:', row[0])
                continue
            print(parts, row)


if __name__ == '__main__':
    main(sys.argv)

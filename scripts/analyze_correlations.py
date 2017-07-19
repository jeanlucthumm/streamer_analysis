import csv
import sys


def main(argv):
    if len(argv) != 2:
        return

    with open(argv[1], newline='') as file:
        print('Reading file', file.name, '...')
        file.readline()  # ignore header
        reader = csv.reader(file, delimiter=',')
        for row in reader:
            if len(row) == 0:
                print('malformed row:', row)
                continue
            print(row)


if __name__ == '__main__':
    main(sys.argv)

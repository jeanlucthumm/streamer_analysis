import csv
import sys
import utils


def average(reader):
    total = 0
    count = 0
    for row in reader:
        if len(row) == 0:
            print('malformed row', row)
            continue

        for delta in row[1:]:
            try:
                total += float(delta)
                count += 1
            except ValueError:
                print('could not process delta:', delta, 'for prefix:', row[0])

    if count == 0:
        print('no delta values found in input file')
        return

    return round(total / float(count), utils.ROUND_ERR)


def main(argv):
    if len(argv) != 2:
        return

    with open(argv[1], newline='') as file:
        print('Reading file', file.name, '...')
        file.readline()  # ignore header
        reader = csv.reader(file, delimiter=',')
        print('Average delta:', average(reader))
        file.seek(0, 0)


if __name__ == '__main__':
    main(sys.argv)

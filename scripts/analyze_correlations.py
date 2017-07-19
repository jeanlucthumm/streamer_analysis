import csv
import sys
import numpy as np

USAGE = """\
USAGE: analyze_correlations input [output]
    input: csv file containing correlation delta for each prefix
    output: optional output file to output stats to"""


def get_data(reader):
    result = []
    for row in reader:
        if len(row) == 0:
            print('malformed row', row)
            continue

        for delta in row[1:]:
            try:
                result.append(float(delta))
            except ValueError:
                print('could not process delta:', delta, 'for prefix:', row[0])
    return result


def main(argv):
    if len(argv) < 2 or len(argv) > 3:
        print(USAGE)
        return

    with open(argv[1], newline='') as file:
        file.readline()  # ignore header
        reader = csv.reader(file, delimiter=',')
        data = get_data(reader)
        file.seek(0, 0)

    arr = np.array(data)
    mean = np.mean(arr)
    median = np.median(arr)
    std = np.std(arr)

    print('Mean:', mean)
    print('Median:', median)
    print('Std:', std)

    if len(argv) == 3:
        with open(argv[2], 'w') as out:
            out.write("Mean: " + str(mean) + '\n')
            out.write("Median: " + str(median) + '\n')
            out.write("Std: " + str(std) + '\n')


if __name__ == '__main__':
    main(sys.argv)

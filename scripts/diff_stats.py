import csv
import sys
import numpy as np

USAGE = """USAGE: diff_stats input [output]
    input: csv file with suffix "_diff" containing angle diffs
    output: optional output file ot output stats to"""


def main(argv):
    if len(argv) < 2 or len(argv) > 3:
        print(USAGE)
        return

    data = []
    with open(argv[1], newline='') as file:
        file.readline()  # ignore header
        reader = csv.reader(file, delimiter=',')
        for row in reader:
            for diff in row[1:]:
                data.append(float(diff))

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

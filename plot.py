#! /bin/python3

from cProfile import label
import matplotlib.pyplot as plt


def load_data(filename: str) -> dict[dict]:
    data = dict()
    with open(filename, 'r') as file:
        for line in file.readlines():
            row = line.split(',')
            if row[0] not in data.keys():
                record = {
                    'l': [],
                    'n': [],
                    'time': []
                }
                data[row[0]] = record
            data[row[0]]['n'] += [int(row[2]) * int(row[2]) * int(row[1])]
            data[row[0]]['time'] += [int(row[3]) + int(row[4])]
    return data


def plot_data(method: str, data: dict[dict]):
    plt.legend()
    plt.scatter(data[method]['n'], data[method]['time'], label=method)


data = load_data('log')

plt.yscale('log')
plt.xscale('log')
plt.xlabel('n*n*l')
plt.ylabel('time (ns)')

plot_data('0', data)
plot_data('1', data)
plot_data('2', data)

plt.legend()
plt.show()

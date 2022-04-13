#! /usr/bin/python3

import csv

path = "./.tmp/test.csv"
csv_file = open(path, newline='')
reader = csv.reader(csv_file)

header = next(reader)

data = []
#  data = [row for row in reader]
for row in reader:
    int1 = int(row[0])
    float1 = float(row[1])
    data.append([int1, float1])

print(header)
print(data[0])

new_csv = "./.tmp/new.csv"
new_file = open(new_csv, "w")
witer = csv.writer(new_file)
witer.writerow(['Date', 'Return'])

for i in range(100):
    witer.writerow([i, i ** 2])
